#include "OLED_UI_Driver.h"

static uint8_t dwt_ready = 0;
static uint8_t encoder_enabled = 1;

static void dwt_init_once(void)
{
	if (dwt_ready) {
		return;
	}

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	dwt_ready = 1;
}

void Timer_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim4);
}

void Key_Init(void)
{
}

void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	encoder_enabled = 1;
}


/**
 * @brief 锟斤拷锟斤拷锟斤拷使锟杰猴拷锟斤拷
 * @param 锟斤拷
 * @return 锟斤拷
 */
void Encoder_Enable(void)
{
	encoder_enabled = 1;
	__HAL_TIM_ENABLE(&htim2);
}

/**
 * @brief 锟斤拷锟斤拷锟斤拷失锟杰猴拷锟斤拷
 * @param 锟斤拷
 * @return 锟斤拷
 */
void Encoder_Disable(void)
{
	encoder_enabled = 0;
	__HAL_TIM_DISABLE(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
}

/**
 * @brief 锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷值锟斤拷锟侥憋拷频锟斤拷锟诫）
 * 
 * @details 锟矫猴拷锟斤拷通锟斤拷锟斤拷取锟斤拷时锟斤拷TIM1锟侥硷拷锟斤拷值锟斤拷锟皆憋拷锟斤拷锟斤拷锟脚号斤拷锟斤拷锟侥憋拷频锟斤拷锟诫处锟斤拷锟斤拷
 *          使锟矫撅拷态锟斤拷锟斤拷锟桔伙拷锟斤拷锟斤拷锟斤拷锟斤拷通锟斤拷锟斤拷锟斤拷锟斤拷取模锟斤拷锟斤拷去锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷郑锟�?
 *          确锟斤拷锟斤拷锟截撅拷确锟斤拷锟斤拷锟斤拷值锟斤拷锟斤拷要锟斤拷锟节碉拷锟斤拷锟斤拷啤锟轿伙拷眉锟斤拷锟接︼拷贸锟斤拷锟斤拷锟�?
 * 
 * @note   锟斤拷锟斤拷锟节诧拷锟斤拷锟皆讹拷锟斤拷锟姐定时锟斤拷锟斤拷锟斤拷值锟斤拷确锟斤拷锟铰次讹拷取锟斤拷准确锟斤拷
 * 
 * @return int16_t 锟斤拷锟截斤拷锟斤拷锟侥憋拷锟斤拷锟斤拷锟斤拷锟斤拷值
 */
int16_t Encoder_Get(void)
{
	static int32_t encoderAccumulator = 0;

	if (!encoder_enabled) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		return 0;
	}

	int16_t temp = (int16_t)__HAL_TIM_GET_COUNTER(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0);

	encoderAccumulator += temp;
	int16_t result = (int16_t)(encoderAccumulator / 4);
	encoderAccumulator %= 4;
	return result;
}



/**
  * @brief  微锟诫级锟斤拷时
  * @param  xus 锟斤拷时时锟斤拷锟斤拷锟斤拷围锟斤拷0~233015
  * @retval 锟斤拷
  */
void Delay_us(uint32_t xus)
{
	dwt_init_once();

	uint32_t start = DWT->CYCCNT;
	uint32_t cycles = (HAL_RCC_GetHCLKFreq() / 1000000U) * xus;
	while ((DWT->CYCCNT - start) < cycles) {
	}
}

/**
  * @brief  锟斤拷锟诫级锟斤拷时
  * @param  xms 锟斤拷时时锟斤拷锟斤拷锟斤拷围锟斤拷0~4294967295
  * @retval 锟斤拷
  */
void Delay_ms(uint32_t xms)
{
	HAL_Delay(xms);
}
 
/**
  * @brief  锟诫级锟斤拷时
  * @param  xs 锟斤拷时时锟斤拷锟斤拷锟斤拷围锟斤拷0~4294967295
  * @retval 锟斤拷
  */
void Delay_s(uint32_t xs)
{
	while (xs--) {
		HAL_Delay(1000);
	}
} 


