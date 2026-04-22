#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "i2c.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef OLED_WIDTH
#define OLED_WIDTH (128)
#endif

#ifndef OLED_HEIGHT
#define OLED_HEIGHT (64)
#endif

//	oled��ʼ������
void OLED_Init(void);
// ������ɫģʽ
void OLED_SetColorMode(bool colormode);
//	oledȫ��ˢ�º���
void OLED_Update(void);
//	oled�ֲ�ˢ�º���
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);


// OLED �������Ⱥ���
void OLED_Brightness(int16_t Brightness);

#ifdef __cplusplus
}
#endif

#endif









