#ifndef __OLED_UI_DRIVER_H
#define __OLED_UI_DRIVER_H
 #ifdef __cplusplus
extern "C" {
 #endif

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"

//��ȡȷ�ϣ�ȡ�����ϣ��°���״̬�ĺ���(��Q��Ϊʲôʹ�ú궨������Ǻ�����A����Ϊ�����������Ч�ʣ����ٴ�������?)
#define Key_GetEnterStatus()    ((uint8_t)HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin))
#define Key_GetBackStatus()     ((uint8_t)HAL_GPIO_ReadPin(Key2_GPIO_Port, Key2_Pin))
#define Key_GetUpStatus()       (1)
#define Key_GetDownStatus()     (1)


//��ʱ���жϳ�ʼ������
void Timer_Init(void);

//������ʼ������
void Key_Init(void);

//��������ʼ������
void Encoder_Init(void);

// ������ʹ�ܺ���
void Encoder_Enable(void);

//������ʧ�ܺ���
void Encoder_Disable(void);

//��ȡ������������ֵ
int16_t Encoder_Get();

//��ʱ����
void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#ifdef __cplusplus
}
#endif

#endif
