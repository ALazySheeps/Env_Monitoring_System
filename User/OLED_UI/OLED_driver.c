#include "OLED_driver.h"

uint8_t OLED_DisplayBuf[OLED_HEIGHT / 8][OLED_WIDTH];

static bool OLED_ColorMode = true;

static void oled_write_cmd(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 100);
}

static void oled_write_data(const uint8_t *data, uint16_t len)
{
	if (OLED_ColorMode) {
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, len, 100);
		return;
	}

	uint8_t tmp[128];
	while (len) {
		uint16_t chunk = (len > sizeof(tmp)) ? (uint16_t)sizeof(tmp) : len;
		for (uint16_t i = 0; i < chunk; i++) {
			tmp[i] = (uint8_t)~data[i];
		}
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, tmp, chunk, 100);
		data += chunk;
		len -= chunk;
	}
}

static void oled_set_cursor(uint8_t page, uint8_t x)
{
	oled_write_cmd((uint8_t)(0xB0 | page));
	oled_write_cmd((uint8_t)(0x10 | ((x & 0xF0) >> 4)));
	oled_write_cmd((uint8_t)(0x00 | (x & 0x0F)));
}

void OLED_SetColorMode(bool colormode)
{
	OLED_ColorMode = colormode;
}

void OLED_Init(void)
{
	HAL_Delay(200);

	static const uint8_t init_cmds[] = {
		0xAE, 0xD5, 0xF0, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC8, 0xDA,
		0x12, 0x81, 0xDF, 0xD9, 0xF1, 0xDB, 0x30, 0xA4, 0xA6, 0x8D, 0x14,
		0xAF
	};

	for (uint32_t i = 0; i < sizeof(init_cmds); i++) {
		oled_write_cmd(init_cmds[i]);
	}

	memset(OLED_DisplayBuf, 0, sizeof(OLED_DisplayBuf));
	OLED_Update();
}
/**
  * ��    ������OLED�Դ�������µ�OLED��Ļ
  * ��    ������
  * �� �� ֵ����
  * ˵    �������е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
  *           ������OLED_Update������OLED_UpdateArea����
  *           �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  *           �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Update(void)
{
	for (uint8_t page = 0; page < (OLED_HEIGHT / 8); page++) {
		oled_set_cursor(page, 0);
		oled_write_data(OLED_DisplayBuf[page], OLED_WIDTH);
	}
}

/**
  * ��    ����OLED��������
  * ��    ����Brightness ��0-255����ͬ��ʾоƬЧ�����ܲ���ͬ��
  * �� �� ֵ����
  * ˵    ������Ҫ���ù�����߹�С��
  */
void OLED_Brightness(int16_t Brightness){
	if(Brightness>255){
		Brightness=255;
	}
	if(Brightness<0){
		Brightness=0;
	}
	oled_write_cmd(0x81);
	oled_write_cmd((uint8_t)Brightness);
}
/**
  * ��    ������OLED�Դ����鲿�ָ��µ�OLED��Ļ
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����Width ָ������Ŀ��ȣ���Χ��0~OLED_WIDTH
  * ��    ����Height ָ������ĸ߶ȣ���Χ��0~OLED_HEIGHT
  * �� �� ֵ����
  * ˵    �����˺��������ٸ��²���ָ��������
  *           �����������Y��ֻ��������ҳ����ͬһҳ��ʣ�ಿ�ֻ����һ�����
  * ˵    �������е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
  *           ������OLED_Update������OLED_UpdateArea����
  *           �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  *           �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	if (X > (OLED_WIDTH - 1)) {
		return;
	}
	if (Y > (OLED_HEIGHT - 1)) {
		return;
	}
	if ((uint16_t)X + Width > OLED_WIDTH) {
		Width = (uint8_t)(OLED_WIDTH - X);
	}
	if ((uint16_t)Y + Height > OLED_HEIGHT) {
		Height = (uint8_t)(OLED_HEIGHT - Y);
	}

	uint8_t page_start = (uint8_t)(Y / 8);
	uint8_t page_end = (uint8_t)((Y + Height - 1) / 8);
	for (uint8_t page = page_start; page <= page_end; page++) {
		oled_set_cursor(page, X);
		oled_write_data(&OLED_DisplayBuf[page][X], Width);
	}
}







