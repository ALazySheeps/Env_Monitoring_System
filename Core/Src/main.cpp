/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "stm32f1xx_hal_adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Sensor.hpp"
#ifdef __cplusplus
extern "C" {
#endif

// #include "OLED_UI.h"
#include "OLED_UI_MenuData.h"
#include <sys/types.h>

#ifdef __cplusplus
}
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define SensorCount 6
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
float measuredRefVoltage = 3.3f;
#ifdef __cplusplus
extern "C" {
#endif
float sensor_data[SensorCount+1];
#ifdef __cplusplus
}
#endif
Sensors sensors(SensorCount); // 假设有6个传感器
// 外部传感器
LightSensor lightSensor1((uint8_t*)"lightSensor1", 0);
LightSensor lightSensor2((uint8_t*)"lightSensor2", 1);
TemperatureSensor tempSensor((uint8_t*)"tempSensor", 2);
VrefSensor vrefSensor((uint8_t*)"vrefSensor", 3);

GrayscaleSensor grayscaleSensor((uint8_t*)"grayscaleSensor", 6);

// 内部传感器
InternalTemperatureSensor internalTempSensor((uint8_t*)"InternalTemp", 4);
RefintSensor refintSensor((uint8_t*)"refintSensor", 5);


char title[] = "Env Sensor:";
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static volatile uint8_t uart_report_pending = 0;
static uint16_t tim4_20ms_counter = 0;
static volatile uint8_t uart_tx_busy = 0;
static uint8_t uart_tx_buf[256];
static uint16_t uart_tx_len = 0;

static const char *uart_sensor_names[SensorCount + 1] = {
    "Light1",
    "Light2",
    "Temp",
    "Vref",
    "IntTemp",
    "RefInt",
    "Gray",
};

static char *append_cstr(char *dst, const char *src)
{
  while (*src) {
    *dst++ = *src++;
  }
  return dst;
}

static char *append_u32_dec(char *dst, uint32_t v)
{
  char tmp[10];
  uint8_t n = 0;
  do {
    tmp[n++] = (char)('0' + (v % 10U));
    v /= 10U;
  } while (v && n < sizeof(tmp));

  while (n--) {
    *dst++ = tmp[n];
  }
  return dst;
}

static char *append_value_2dp(char *dst, float v)
{
  int32_t v100 = (int32_t)(v * 100.0f);
  char sign = '+';
  if (v100 < 0) {
    sign = '-';
    v100 = -v100;
  }

  uint32_t int_part = (uint32_t)(v100 / 100);
  uint32_t frac_part = (uint32_t)(v100 % 100);

  *dst++ = sign;
  dst = append_u32_dec(dst, int_part);
  *dst++ = '.';
  *dst++ = (char)('0' + (frac_part / 10U));
  *dst++ = (char)('0' + (frac_part % 10U));
  return dst;
}

static uint8_t uart_send_sensor_report_dma(void)
{
  if (uart_tx_busy) {
    return 0;
  }

  char *p = (char *)uart_tx_buf;

  p = append_cstr(p, title);
  *p++ = '\r';
  *p++ = '\n';
  for (uint8_t i = 0; i < (SensorCount + 1); i++) {
    p = append_cstr(p, uart_sensor_names[i]);
    *p++ = ':';
    *p++ = ' ';
    p = append_value_2dp(p, sensor_data[i]);
    *p++ = '\r';
    *p++ = '\n';
  }
  *p++ = '\r';
  *p++ = '\n';

  uart_tx_len = (uint16_t)(p - (char *)uart_tx_buf);
  uart_tx_busy = 1;
  if (HAL_UART_Transmit_DMA(&huart1, uart_tx_buf, uart_tx_len) != HAL_OK) {
    uart_tx_busy = 0;
    uart_tx_len = 0;
    return 0;
  }

  return 1;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  // ========== 【ADC 校准 开始】 ==========
  HAL_ADC_Stop(&hadc1);               // 先停止 ADC（防止正在运行）
  HAL_ADCEx_Calibration_Start(&hadc1); // 执行校准
  // ========== 【ADC 校准 结束】 ==========

  sensors.addSensor(0, &lightSensor1);
  sensors.addSensor(1, &lightSensor2);
  sensors.addSensor(2, &tempSensor);
  sensors.addSensor(3, &vrefSensor);
  sensors.addSensor(4, &internalTempSensor);
  sensors.addSensor(5, &refintSensor);


  //HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sensors.getAdcBuf(), SensorCount);
  // 启动 DMA（单次模式）
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sensors.getAdcBuf(), SensorCount);

  // 启动定时器 100ms 触发
  HAL_TIM_Base_Start(&htim3);

  // 启动 ADC 硬件触发
  HAL_ADC_Start(&hadc1);
  HAL_ADCEx_InjectedStart_IT(&hadc1);

  OLED_UI_Init(&MainMenuPage);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    OLED_UI_MainLoop();
    
    if (uart_report_pending) {
      if (uart_send_sensor_report_dma()) {
        uart_report_pending = 0;
      }
    }

    /* USER CODE END WHILE */
       
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    OLED_UI_InterruptHandler();

    if (!uart_report_pending && !uart_tx_busy) {
      tim4_20ms_counter++;
      if (tim4_20ms_counter >= 100U) {
        tim4_20ms_counter = 0;
        uart_report_pending = 1;
      }
    }
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1) {
    uart_tx_busy = 0;
  }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1) {
    uart_tx_busy = 0;
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
      // 规则组转换完成
      if (hadc->State & HAL_ADC_STATE_REG_EOC)
      {
        // 在这里处理 ADC 转换完成后的数据
        sensors.update();
        for (int i = 0; i < SensorCount; i++) {
            sensor_data[i] = sensors.getSensor(i); 
        }
        __HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_EOC); // 手动清 EOC
      }
    }
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        // 注入组转换完成
        grayscaleSensor.setRawData(HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1));
        sensor_data[6] = grayscaleSensor.getData();
        
        __HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_JEOC); // 手动清 EOC
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
