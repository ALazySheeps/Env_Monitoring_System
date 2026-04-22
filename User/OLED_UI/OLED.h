#ifndef __OLED_H
#define __OLED_H

// ����Ƿ���C++������
#ifdef __cplusplus
extern "C" {
#endif

#include "OLED_Driver.h"			//oled�ײ�����ͷ�ļ�
#ifndef OLED_ENABLE_CHINESE
#define OLED_ENABLE_CHINESE (0)
#endif
#include "OLED_Fonts.h"				//oled�����ͷ�ļ�
#include "stdbool.h"


//ʹ�ú궨��ķ�ʽȷ��oled�ĺ�����������������
#define OLED_WIDTH						(128)					
#define OLED_HEIGHT 					(64)
/*����ַ�����ȡֵ*/
/*�˲���ֵ���������жϣ��������ڼ�������ַ�ƫ�ƣ�Ĭ��ֵΪ�������ؿ���*/
#define OLED_10X20_HALF				(10)
#define OLED_8X16_HALF				(8)
#define OLED_7X12_HALF				(7)				
#define OLED_6X8_HALF 			    (6)

/*ȫ�Ǵ�С����ȡֵ*/
#define OLED_8X8_FULL					(8)
#define OLED_12X12_FULL				    (12)
#define OLED_16X16_FULL			        (16)
#define OLED_20X20_FULL			        (20)

/*IsFilled������ֵ*/
#define OLED_UNFILLED			        (0)
#define OLED_FILLED				        (1)

/**�����ַ�����󳤶ȵĺ꣬���ڸ�ʽ������ַ���*/
#define  MAX_STRING_LENGTH 128


//�����Ļ
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, int16_t Width, int16_t Height);
//��Ļ��ɫ
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, int16_t Width, int16_t Height);
//����λͼ
void OLED_ShowImage(int16_t X, int16_t Y, uint16_t Width, uint16_t Height, const uint8_t *Image);
//��ʾASCII�ַ�������
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
//��ʾ��Ӣ���ַ���
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowMixString(int16_t X, int16_t Y, char *String, uint8_t ChineseFontSize, uint8_t ASCIIFontSize);
void OLED_ShowChinese(int16_t X, int16_t Y, char *Chinese, uint8_t FontSize);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);
void OLED_PrintfMix(int16_t X, int16_t Y, uint8_t ChineseFontSize,uint8_t ASCIIFontSize,const char *format, ...);

//Areaϵ����ʾ��������������Ϊ����Ļʹ���ɰ��ڵ������������ڳ�һ��X2��Y2��AreaWidth��AreaHeight��͸������ͼƬ�������������������ʾ
void OLED_ShowImageArea(int16_t X_Pic, int16_t Y_Pic, int16_t PictureWidth, int16_t PictureHeight, int16_t X_Area, int16_t Y_Area, int16_t AreaWidth, int16_t AreaHeight, const uint8_t *Image);
void OLED_ShowCharArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowStringArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowChineseArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char *Chinese, uint8_t FontSize);
void OLED_PrintfArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y,uint8_t FontSize, char *format, ...);
void OLED_ShowMixStringArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight,int16_t X, int16_t Y, char *String, uint8_t ChineseFontSize,uint8_t ASCIIFontSize);
void OLED_PrintfMixArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight,int16_t X, int16_t Y, uint8_t ChineseFontSize,uint8_t ASCIIFontSize, char *format, ...);

//���ƺ��������ƻ�����ui
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, int16_t Width, int16_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, int16_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, int16_t A, int16_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, int16_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);
void OLED_DrawRoundedRectangle(int16_t X, int16_t Y, int16_t Width, int16_t Height, int16_t Radius, uint8_t IsFilled);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif

