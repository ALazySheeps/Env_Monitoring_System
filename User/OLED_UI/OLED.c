/*
 * ���ͷ�ļ���oled��� [������] ʵ���ļ�����ֲ��ʱ����Ҫ��������ļ�������
 * �ڴ��ļ����У�������bվup��Э�Ƽ��ĺ������ڴ˳�ֿ��л��
*/
#include "OLED.h"
/**
  * ����OLED�Դ����飬�������Ѿ���OLED_Driver.c�ж���
  * ���е���ʾ��������ֻ�ǶԴ��Դ�������ж�д
  * ������OLED_Update������OLED_UpdateArea����
  * �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  */
extern uint8_t OLED_DisplayBuf[OLED_HEIGHT/8][OLED_WIDTH];


/*********************���ߺ�����********************/
/**
  * ��    �����η�����
  * ��    ����X ����
  * ��    ����Y ָ��
  * �� �� ֵ������X��Y�η�
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//���Ĭ��Ϊ1
	while (Y --)			//�۳�Y��
	{
		Result *= X;		//ÿ�ΰ�X�۳˵������
	}
	return Result;
}

/**
  * ��    �����ж�ָ�����Ƿ���ָ��������ڲ�
  * ��    ����nvert ����εĶ�����
  * ��    ����vertx verty ��������ζ����x��y���������
  * ��    ����testx testy ���Ե��X��y����
  * �� �� ֵ��ָ�����Ƿ���ָ��������ڲ���1�����ڲ���0�������ڲ�
  */
uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
{
	int16_t i = 0, j = 0;
	uint8_t c = 0;
	/*���㷨��W. Randolph Franklin���*/
	/*�ο����ӣ�https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
	for (i = 0, j = nvert - 1; i < nvert; j = i++)
	{
		if (((verty[i] > testy) != (verty[j] > testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
		{
			c = !c;
		}
	}
	return c;
}
/*
 * �������ȴ�С����
 * ������
 * �ĸ�����ֵ
 * ����ֵ���ĸ�����ֵ���е����ֵ
*/

int16_t max(int16_t a, int16_t b, int16_t c, int16_t d) {
    int16_t max_val = a; // ����a������

    if (b > max_val) {
        max_val = b; // ���b���ڵ�ǰ���ֵ����������ֵΪb
    }
    if (c > max_val) {
        max_val = c; // ���c���ڵ�ǰ���ֵ����������ֵΪc
    }
    if (d > max_val) {
        max_val = d; // ���d���ڵ�ǰ���ֵ����������ֵΪd
    }

    return max_val; // �������ֵ
}

/*
 * ����������ֵ����
 * ������
 * num
 * ����ֵ��num�ľ���ֵ
*/

float numabs(float num){
	if(num>0)
		return num;
	if(num<0)
		return -num;
	return 0;
}



/**
  * ��    �����ж�ָ�����Ƿ���ָ���Ƕ��ڲ�
  * ��    ����X Y ָ���������
  * ��    ����StartAngle EndAngle ��ʼ�ǶȺ���ֹ�Ƕȣ���Χ��-180~180
  *           ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
  * �� �� ֵ��ָ�����Ƿ���ָ���Ƕ��ڲ���1�����ڲ���0�������ڲ�
  */
uint8_t OLED_IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
{
	int16_t PointAngle;
	PointAngle = atan2(Y, X) / 3.14 * 180;	//����ָ����Ļ��ȣ���ת��Ϊ�Ƕȱ�ʾ
	if (StartAngle < EndAngle)	//��ʼ�Ƕ�С����ֹ�Ƕȵ����
	{
		/*���ָ���Ƕ�����ʼ��ֹ�Ƕ�֮�䣬���ж�ָ������ָ���Ƕ�*/
		if (PointAngle >= StartAngle && PointAngle <= EndAngle)
		{
			return 1;
		}
	}
	else			//��ʼ�Ƕȴ�������ֹ�Ƕȵ����
	{
		/*���ָ���Ƕȴ�����ʼ�ǶȻ���С����ֹ�Ƕȣ����ж�ָ������ָ���Ƕ�*/
		if (PointAngle >= StartAngle || PointAngle <= EndAngle)
		{
			return 1;
		}
	}
	return 0;		//�������������������ж��ж�ָ���㲻��ָ���Ƕ�
}

/*********************���ߺ�����********************/

/*********************���ܺ�����*********************/
/**
  * ��    ������OLED�Դ�����ȫ������
  * ��    ������
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Clear(void)
{
	int16_t i, j;
	for (j = 0; j < OLED_HEIGHT/8; j ++)				//����8ҳ
	{
		for (i = 0; i < OLED_WIDTH; i ++)			//����OLED_WIDTH��
		{
			OLED_DisplayBuf[j][i] = 0x00;	//���Դ���������ȫ������
		}
	}
}
/**
  * ��    ������OLED�Դ����鲿������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����Width ָ������Ŀ��ȣ���Χ��0~OLED_WIDTH
  * ��    ����Height ָ������ĸ߶ȣ���Χ��0~OLED_HEIGHT
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
 
  void OLED_ClearArea(int16_t X, int16_t Y, int16_t Width, int16_t Height)
  {
	  int16_t x_start, y_start, x_end, y_end;
	  int16_t i, j;
  
	  if (Width <= 0 || Height <= 0) return;
  
	  // ����X�������ʼ�ͽ���λ��
	  x_start = (X < 0) ? 0 : X;
	  x_end = X + Width;
	  if (x_end > OLED_WIDTH) x_end = OLED_WIDTH;
	  if (x_start >= x_end) return;
  
	  // ����Y�������ʼ�ͽ���λ��
	  y_start = (Y < 0) ? 0 : Y;
	  y_end = Y + Height;
	  if (y_end > OLED_HEIGHT) y_end = OLED_HEIGHT;
	  if (y_start >= y_end) return;
  
	  // ����Width��HeightΪʵ����Ҫ���������
	  Width = x_end - x_start;
	  Height = y_end - y_start;
  
	  for (j = y_start; j < y_end; j++) {
		  for (i = x_start; i < x_end; i++) {
			  OLED_DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8));
		  }
	  }
  }



/**
  * ��    ������OLED�Դ�����ȫ��ȡ��
  * ��    ������
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Reverse(void)
{
	uint8_t i, j;
	for (j = 0; j < OLED_HEIGHT/8; j ++)				//����ҳ
	{
		for (i = 0; i < OLED_WIDTH; i ++)			//����OLED_WIDTH��
		{
			OLED_DisplayBuf[j][i] ^= 0xFF;	//���Դ���������ȫ��ȡ��
		}
	}
}



/**
  * ��    ������OLED�Դ����鲿��ȡ��
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT
  * ��    ����Width ָ������Ŀ��ȣ���Χ������~OLED_WIDTH
  * ��    ����Height ָ������ĸ߶ȣ���Χ������~OLED_HEIGHT
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ReverseArea(int16_t X, int16_t Y, int16_t Width, int16_t Height)
{
	int16_t i, j, x, y;
	if(Width <= 0 || Height <= 0) {return; }
	/*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
	if (X > OLED_WIDTH-1) {return;}
	if (Y > OLED_HEIGHT-1) {return;}
	if (X + Width > OLED_WIDTH) {Width = OLED_WIDTH - X;}
	if (Y + Height > OLED_HEIGHT) {Height = OLED_HEIGHT - Y;}
	if (X + Width < 0) {return;}
	if (Y + Height < 0) {return;}
	if (X < 0) { x = 0;} else { x = X;}
	if (Y < 0) { y = 0;} else { y = Y;}
	
	for (j = y; j < Y + Height; j ++)		//����ָ��ҳ
	{
		for (i = x; i < X + Width; i ++)	//����ָ����
		{
			OLED_DisplayBuf[j / 8][i] ^= 0x01 << (j % 8);	//���Դ�����ָ������ȡ��
		}
	}
}
/**
  * ��    ����OLED��ʾͼ�� BY BILIBILI��nm������ xy�����Ϊ��
  * ��    ����X ָ��ͼ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * ��    ����Y ָ��ͼ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * ��    ����Width ָ��ͼ��Ŀ��ȣ���Χ������
  * ��    ����Height ָ��ͼ��ĸ߶ȣ���Χ������
  * ��    ����Image ָ��Ҫ��ʾ��ͼ��
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowImage(int16_t X, int16_t Y, uint16_t Width, uint16_t Height, const uint8_t *Image)
{
      uint8_t i, j;
    
    /* ������飬��ָ֤��ͼ�񲻻ᳬ����Ļ��Χ */
    if (Width == 0 || Height == 0) {
        return; // ������Ȼ�߶�Ϊ0��ֱ�ӷ���
    }
    
    if (X > OLED_WIDTH-1) {
        return; // X �����ұ߽磬ֱ�ӷ���
    }
    if (Y > OLED_HEIGHT-1) {
        return; // Y �����±߽磬ֱ�ӷ���
    }
    
    /* ��ͼ������������� */
    uint8_t startX = (X < 0) ? 0 : X; // ����ʵ����ʼ��ʾλ�õ� X ����
    uint8_t startY = (Y < 0) ? 0 : Y; // ����ʵ����ʼ��ʾλ�õ� Y ����
    uint8_t endX = (X + Width - 1 > OLED_WIDTH-1) ? OLED_WIDTH-1 : X + Width - 1; // ����ʵ�ʽ�����ʾλ�õ� X ����
    uint8_t endY = (Y + Height - 1 > OLED_HEIGHT-1) ? OLED_HEIGHT-1 : Y + Height - 1; // ����ʵ�ʽ�����ʾλ�õ� Y ����
    
    OLED_ClearArea(startX, startY, endX - startX + 1, endY - startY + 1);
    
    /* ����ָ��ͼ���漰�����ҳ */
    for (j = 0; j < (Height - 1) / 8 + 1; j++)
    {
        /* ����ָ��ͼ���漰������� */
        for (i = 0; i < Width; i++)
        {
            int16_t currX = X + i;
            int16_t currY = Y + j * 8;
            
            /* �����߽磬��������ʾ */
            if (currX < 0 || currX > OLED_WIDTH-1 ||currY < 0 || currY > OLED_HEIGHT-1) {
                continue;
            }
			/* ��ʾͼ���ڵ�ǰҳ������ */
			OLED_DisplayBuf[currY / 8][currX] |= Image[j * Width + i] << (currY % 8);
			/* ��ǰҳ��һҳ */
			if (currY + 8 <= OLED_HEIGHT-1) {
				OLED_DisplayBuf[currY / 8 + 1][currX] |= Image[j * Width + i] >> (8 - currY % 8);
			}
        }
    }
	if(Y<0){
		for (i = 0; i < Width; i++)
        {
            int16_t currX = X + i;
			if (currX < 0 || currX > OLED_WIDTH-1) {
                continue;
            }
			OLED_DisplayBuf[0][currX] |= Image[ -Y/8*Width+i] >> -Y%8;
		}
	}
}
/**
  * ��    ����OLED��ʾһ���ַ�
  * ��    ����X ָ���ַ����Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���ַ����Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Char ָ��Ҫ��ʾ���ַ�����Χ��ASCII��ɼ��ַ�
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16_HALF		��8���أ���16����
  *                 OLED_6X8_HALF		��6���أ���8����
  *                  OLED_7X12_HALF		��7���أ���12����
  *                 OLED_10X20_HALF		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize)
{
	(void)FontSize;
	OLED_ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
}

/**
  * ��    ����OLED��ʾ���֣�ʮ���ƣ���������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Number ָ��Ҫ��ʾ�����֣���Χ������~4294967295
  * ��    ����Length ָ�����ֵĳ��ȣ���Χ������~10
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; i < Length; i++)		//�������ֵ�ÿһλ
	{
		/*����OLED_ShowChar������������ʾÿ������*/
		/*Number / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
		/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
		OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	}
}

/**
  * ��    ����OLED��ʾ�з������֣�ʮ���ƣ�������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Number ָ��Ҫ��ʾ�����֣���Χ��-2147483648~2147483647
  * ��    ����Length ָ�����ֵĳ��ȣ���Χ������~10
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	uint32_t Number1;
	
	if (Number >= 0)						//���ִ��ڵ���0
	{
		OLED_ShowChar(X, Y, '+', FontSize);	//��ʾ+��
		Number1 = Number;					//Number1ֱ�ӵ���Number
	}
	else									//����С��0
	{
		OLED_ShowChar(X, Y, '-', FontSize);	//��ʾ-��
		Number1 = -Number;					//Number1����Numberȡ��
	}
	
	for (i = 0; i < Length; i++)			//�������ֵ�ÿһλ
	{
		/*����OLED_ShowChar������������ʾÿ������*/
		/*Number1 / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
		/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
		OLED_ShowChar(X + (i + 1) * FontSize, Y, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	}
}

/**
  * ��    ����OLED��ʾʮ���������֣�ʮ�����ƣ���������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Number ָ��Ҫ��ʾ�����֣���Χ��0x00000000~0xFFFFFFFF
  * ��    ����Length ָ�����ֵĳ��ȣ���Χ������~8
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)		//�������ֵ�ÿһλ
	{
		/*��ʮ��������ȡ���ֵ�ÿһλ*/
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		
		if (SingleNumber < 10)			//��������С��10
		{
			/*����OLED_ShowChar��������ʾ������*/
			/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
			OLED_ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
		}
		else							//�������ִ���10
		{
			/*����OLED_ShowChar��������ʾ������*/
			/*+ 'A' �ɽ�����ת��Ϊ��A��ʼ��ʮ�������ַ�*/
			OLED_ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
		}
	}
}



/**
  * ��    ����OLED��ʾ���������֣������ƣ���������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Number ָ��Ҫ��ʾ�����֣���Χ��0x00000000~0xFFFFFFFF
  * ��    ����Length ָ�����ֵĳ��ȣ���Χ������~16
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; i < Length; i++)		//�������ֵ�ÿһλ
	{
		/*����OLED_ShowChar������������ʾÿ������*/
		/*Number / OLED_Pow(2, Length - i - 1) % 2 ���Զ�������ȡ���ֵ�ÿһλ*/
		/*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
		OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(2, Length - i - 1) % 2 + '0', FontSize);
	}
}

/**
  * ��    ����OLED��ʾ�������֣�ʮ���ƣ�С����
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ������~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ������~OLED_HEIGHT-1
  * ��    ����Number ָ��Ҫ��ʾ�����֣���Χ��-4294967295.0~4294967295.0
  * ��    ����IntLength ָ�����ֵ�����λ���ȣ���Χ��0~10
  * ��    ����FraLength ָ�����ֵ�С��λ���ȣ���Χ��0~9��С����������������ʾ
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
	uint32_t PowNum, IntNum, FraNum;
	
	if (Number >= 0)						//���ִ��ڵ���0
	{
		OLED_ShowChar(X, Y, '+', FontSize);	//��ʾ+��
	}
	else									//����С��0
	{
		OLED_ShowChar(X, Y, '-', FontSize);	//��ʾ-��
		Number = -Number;					//Numberȡ��
	}
	
	/*��ȡ�������ֺ�С������*/
	IntNum = Number;						//ֱ�Ӹ�ֵ�����ͱ�������ȡ����
	Number -= IntNum;						//��Number��������������ֹ֮��С���˵�����ʱ����������ɴ���
	PowNum = OLED_Pow(10, FraLength);		//����ָ��С����λ����ȷ������
	FraNum = round(Number * PowNum);		//��С���˵�������ͬʱ�������룬������ʾ���
	IntNum += FraNum / PowNum;				//��������������˽�λ������Ҫ�ټӸ�����
	
	/*��ʾ��������*/
	OLED_ShowNum(X + FontSize, Y, IntNum, IntLength, FontSize);
	
	/*��ʾС����*/
	OLED_ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);
	
	/*��ʾС������*/
	OLED_ShowNum(X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
}



/**
  * ��    ����OLED��ʾ�ַ���
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����String ָ��Ҫ��ʾ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				 OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)		//�����ַ�����ÿ���ַ�
	{
		/*����OLED_ShowChar������������ʾÿ���ַ�*/
		OLED_ShowChar(X + i * FontSize, Y, String[i], FontSize);
		
	}
}



/**
  * ��    ����OLED��ʾ���ִ�
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����Chinese ָ��Ҫ��ʾ�ĺ��ִ�����Χ������ȫ��Ϊ���ֻ���ȫ���ַ�����Ҫ�����κΰ���ַ�
  *           ��ʾ�ĺ�����Ҫ��OLED_Data.c���OLED_CF16x16���鶨��
  *           δ�ҵ�ָ������ʱ������ʾĬ��ͼ�Σ�һ�������ڲ�һ���ʺţ�
  * ��    ����FontSize ָ���������ִ�С��OLED_8X8_FULL,OLED_12X12_FULL,OLED_16X16_FULL,OLED_20X20_FULL
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowChinese(int16_t X, int16_t Y, char *Chinese, uint8_t FontSize)
{
#if OLED_ENABLE_CHINESE
    uint8_t pChinese = 0;
    uint8_t pIndex;
    uint8_t i;
    char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
    
    for (i = 0; Chinese[i] != '\0'; i ++)    // �������ִ�
    {
        SingleChinese[pChinese] = Chinese[i];    // ��ȡ���ִ����ݵ�������������
        pChinese ++;                            // �ƴ�����
        
        if (pChinese >= OLED_CHN_CHAR_WIDTH)    // ��ȡ����һ�������ĺ���
        {
            pChinese = 0;    // �ƴι���
            
			const void* fontArray;
			if (FontSize == OLED_8X8_FULL) {
					fontArray = (const void*) OLED_CF8x8;
			}else
			if (FontSize == OLED_12X12_FULL) {
					fontArray = (const void*) OLED_CF12x12;
			}else
			if (FontSize == OLED_16X16_FULL) {
					fontArray = (const void*) OLED_CF16x16;
			}else
			if (FontSize == OLED_20X20_FULL) {
				fontArray = (const void*) OLED_CF20x20;
			}
 	
			if(FontSize==OLED_8X8_FULL){
				for (pIndex = 0; strcmp(((const ChineseCell8x8_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
				{
					if (strcmp(((const ChineseCell8x8_t*)fontArray)[pIndex].Index, SingleChinese) == 0)
					{
						break;
					}
				}
				OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_8X8_FULL, Y, OLED_8X8_FULL, OLED_8X8_FULL, ((const ChineseCell8x8_t*)fontArray)[pIndex].Data);
			}else
			if(FontSize==OLED_12X12_FULL){
				for (pIndex = 0; strcmp(((const ChineseCell12x12_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
				{
					if (strcmp(((const ChineseCell12x12_t*)fontArray)[pIndex].Index, SingleChinese) == 0)
					{
						break;
					}
				}
				OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_12X12_FULL, Y, OLED_12X12_FULL, OLED_12X12_FULL, ((const ChineseCell12x12_t*)fontArray)[pIndex].Data);
			}else
			if(FontSize==OLED_16X16_FULL){
				for (pIndex = 0; strcmp(((const ChineseCell16x16_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
				{
					if (strcmp(((const ChineseCell16x16_t*)fontArray)[pIndex].Index, SingleChinese) == 0)
					{
						break;
					}
				}
				OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_16X16_FULL, Y, OLED_16X16_FULL, OLED_16X16_FULL, ((const ChineseCell16x16_t*)fontArray)[pIndex].Data);
			}else
			if(FontSize==OLED_20X20_FULL){
				for (pIndex = 0; strcmp(((const ChineseCell20x20_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
				{
					if (strcmp(((const ChineseCell20x20_t*)fontArray)[pIndex].Index, SingleChinese) == 0)
					{
						break;
					}
				}
				OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_20X20_FULL, Y, OLED_20X20_FULL, OLED_20X20_FULL, ((const ChineseCell20x20_t*)fontArray)[pIndex].Data);
			}
        }
    }
#else
	(void)X;
	(void)Y;
	(void)Chinese;
	(void)FontSize;
#endif
}

/**
  * ��    ����OLEDʹ��printf������ӡ��ʽ���ַ���
  * ��    ����X ָ����ʽ���ַ������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ����ʽ���ַ������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *                 OLED_6X8		��6���أ���8����
  * 				OLED_7X12		��7���أ���12����
  *                 OLED_10X20		��10���أ���20����
  * ��    ����format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
  * ��    ����... ��ʽ���ַ��������б�
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...)
{
	char String[MAX_STRING_LENGTH];						//�����ַ�����
	va_list arg;							//����ɱ�����б��������͵ı���arg
	va_start(arg, format);					//��format��ʼ�����ղ����б���arg����
	vsprintf(String, format, arg);			//ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б����ַ�������
	va_end(arg);							//��������arg
	OLED_ShowString(X, Y, String, FontSize);//OLED��ʾ�ַ����飨�ַ�����
}



/**
  * @brief OLED��ʾ����ַ�����������ASCII��
  * @param X ָ�����ִ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ�����ִ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param String ָ��Ҫ��ʾ�Ļ���ַ�������Χ��ȫ���ַ������ַ�������
  *        ��ʾ�ĺ�����Ҫ��OLED_Data.c���OLED_CF16x16��OLED_CF12x12���鶨��
  *        δ�ҵ�ָ������ʱ������ʾĬ��ͼ�Σ�һ�������ڲ�һ���ʺţ�
  * @param ChineseFontSize ָ���������ִ�С��OLED_8X8_FULL,OLED_12X12_FULL,OLED_16X16_FULL,OLED_20X20_FULL
  * @param ASCIIFontSize  ָ��ASCII���ִ�С,OLED_6X8_HALF,OLED_7X12_HALF,OLED_8X16_HALF,OLED_10X20_HALF
  * @return ��
  */
void OLED_ShowMixString(int16_t X, int16_t Y, char *String, uint8_t ChineseFontSize, uint8_t ASCIIFontSize) 
{
    while (*String != '\0') {
        if (*String & 0x80) { // �ж��Ƿ��������ַ� (���λΪ1��ʾ�����ַ�)
#if OLED_ENABLE_CHINESE
			char Chinese[OLED_CHN_CHAR_WIDTH+1];
			for (uint8_t i=0;i<OLED_CHN_CHAR_WIDTH;i++){
				Chinese[i] = *(String+i);
			}
			Chinese[OLED_CHN_CHAR_WIDTH] = '\0';
			OLED_ShowChinese(X, Y, Chinese, ChineseFontSize);
			X += ChineseFontSize;  // �����ַ�����
			String += OLED_CHN_CHAR_WIDTH;  // ������ǰ�������ֽڵ������ַ�
#else
			(void)ChineseFontSize;
			OLED_ShowChar(X, Y, '?', ASCIIFontSize);
			X += ASCIIFontSize;
			String++;
#endif
        } else {
            // �����ASCII�ַ�
            OLED_ShowChar(X, Y, *String, ASCIIFontSize);
            X += ASCIIFontSize; // ASCII�ַ�����
            String++; // ָ����һ���ַ�
        }
    }
}

/**
  * ��    ����OLEDʹ��printf������ӡ��ʽ���ַ���,��������Ӣ�Ļ��ӵ��ַ������˺�����bilibili@��nm������ ����
  * ��    ����X ָ�����ִ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * ��    ����Y ָ�����ִ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * ��    ����ChineseFontSize ָ�����������С��OLED_8X8_FULL,OLED_12X12_FULL,OLED_16X16_FULL,OLED_20X20_FULL
  * ��    ����ASCIIFontSize ָ��ASCII�����С,OLED_6X8_HALF,OLED_7X12_HALF,OLED_8X16_HALF,OLED_10X20_HALF
  * ��    ����format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
  * ��    ����... ��ʽ���ַ��������б�
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */

void OLED_PrintfMix(int16_t X, int16_t Y, uint8_t ChineseFontSize,uint8_t ASCIIFontSize,const char *format, ...)
{
	char String[MAX_STRING_LENGTH];						//�����ַ�����
	va_list arg;							//����ɱ�����б��������͵ı���arg
	va_start(arg, format);					//��format��ʼ�����ղ����б���arg����
	vsprintf(String, format, arg);			//ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б����ַ�������
	va_end(arg);							//��������arg
	OLED_ShowMixString( X, Y, String, ChineseFontSize,ASCIIFontSize);//OLED��ʾ�ַ����飨�ַ�����
}





/**
  * @brief ��ָ����������ʾͼƬ
  * @param X_Pic ͼƬ���Ͻǵĺ�����
  * @param Y_Pic ͼƬ���Ͻǵ�������
  * @param PictureWidth ͼƬ����
  * @param PictureHeight ͼƬ�߶�
  * @param X_Area ��ʾ��������Ͻǵĺ�����
  * @param Y_Area ��ʾ��������Ͻǵ�������
  * @param AreaWidth ��ʾ����Ŀ���
  * @param AreaHeight ��ʾ����ĸ߶�
  * @param Image ͼƬȡģ����
  * @note �˺���������Ҫ�������Խ�һ��ͼƬ��ʾ��ָ���������ڣ�ʵ�ָ��ӵ���ʾЧ����ΪOLED_UI����๦���ṩ������
  * @retval ��
  */
 void OLED_ShowImageArea(int16_t X_Pic, int16_t Y_Pic, int16_t PictureWidth, int16_t PictureHeight, int16_t X_Area, int16_t Y_Area, int16_t AreaWidth, int16_t AreaHeight, const uint8_t *Image)
 {
	 if (PictureWidth == 0 || PictureHeight == 0 || AreaWidth == 0 || AreaHeight == 0 || X_Pic > OLED_WIDTH-1 || X_Area > OLED_WIDTH-1 || Y_Pic > OLED_HEIGHT-1 || Y_Area > OLED_HEIGHT-1) {return; }
		 int16_t startX = (X_Pic < X_Area) ? X_Area : X_Pic;
	 int16_t endX = ((X_Area + AreaWidth - 1) < (X_Pic + PictureWidth - 1)) ? (X_Area + AreaWidth - 1) : (X_Pic + PictureWidth - 1);
	 int16_t startY = (Y_Pic < Y_Area) ? Y_Area : Y_Pic;
	 int16_t endY = ((Y_Area + AreaHeight - 1) < (Y_Pic + PictureHeight - 1)) ? (Y_Area + AreaHeight - 1) : (Y_Pic + PictureHeight - 1);
	 endX = (endX > OLED_WIDTH-1) ? OLED_WIDTH-1 : endX;
	 endY = (endY > OLED_HEIGHT-1) ? OLED_HEIGHT-1 : endY;
		 if(startX > endX || startY > endY){return;}
		 //OLED_ClearArea(startX, startY, endX - startX + 1, endY - startY + 1);
		 for (uint8_t j = 0; j <= (PictureHeight - 1) / 8; j++) {
		 for (uint8_t i = 0; i < PictureWidth; i++) {
			 uint8_t currX = X_Pic + i;
			 if (currX < startX || currX > endX) {continue;};
			 for (uint8_t bit = 0; bit < 8; bit++) {
				 uint8_t currY = Y_Pic + j * 8 + bit;
				 if (currY < startY || currY > endY) {continue;};
				 uint8_t page = currY / 8;
				 uint8_t bit_pos = currY % 8;
				 uint8_t data = Image[j * PictureWidth + i];
				 if (data & (1 << bit)) {OLED_DisplayBuf[page][currX] |= (1 << bit_pos); }
			 }
		 }
	 }
 }



/**
  * @brief ��ָ����Χ����ʾһ���ַ�
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param Char ָ��Ҫ��ʾ���ַ�����Χ��ASCII��ɼ��ַ�
  * @param FontSize ָ�������С,OLED_6X8_HALF,OLED_7X12_HALF,OLED_8X16_HALF,OLED_10X20_HALF
  * @retval ��
  */
void OLED_ShowCharArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char Char, uint8_t FontSize)
{
	(void)FontSize;
	OLED_ShowImageArea(X, Y, 6, 8, RangeX, RangeY, RangeWidth, RangeHeight, OLED_F6x8[Char - ' ']);
}
/**
  * @brief ��ָ����Χ����ʾ�ַ�����ָ����������ʾ�ַ���
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param String ָ��Ҫ��ʾ���ַ�������Χ��ASCII��ɼ��ַ�
  * @param FontSize ָ�������С,OLED_6X8_HALF,OLED_7X12_HALF,OLED_8X16_HALF,OLED_10X20_HALF
  * @retval ��
  */

void OLED_ShowStringArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char *String, uint8_t FontSize)
{
	/*�����п�����ʾ�������ַ���������uint16_t*/
	uint16_t i;
	for (i = 0; String[i] != '\0'; i++)		//�����ַ�����ÿ���ַ�
	{
		/*����OLED_ShowCharArea������������ʾÿ���ַ�*/
		OLED_ShowCharArea(RangeX,RangeY,RangeWidth,RangeHeight,X + i * FontSize,Y, String[i],FontSize);
	}
}
/**
  * @brief ��ָ������Χ��OLED��ʾ���ִ�
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param Chinese ָ��Ҫ��ʾ�ĺ��ִ�����Χ������ȫ��Ϊ���ֻ���ȫ���ַ�����Ҫ�����κΰ���ַ�
  *           ��ʾ�ĺ�����Ҫ��OLED_Data.c���OLED_CF16x16��OLED_CF12x12���鶨��
  *           δ�ҵ�ָ������ʱ������ʾĬ��ͼ�Σ�һ�������ڲ�һ���ʺţ�
  * @param FontSize ָ���������ִ�С����OLED_8X8_FULL,OLED_12X12_FULL,OLED_16X16_FULL,OLED_20X20_FULL
  * @retval ��
  */


void OLED_ShowChineseArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y, char *Chinese, uint8_t FontSize)
{
#if OLED_ENABLE_CHINESE
    uint8_t pChinese = 0;
    uint8_t pIndex;
    uint8_t i;
    char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
    for (i = 0; Chinese[i] != '\0'; i ++)    // �������ִ�
    {
        SingleChinese[pChinese] = Chinese[i];    // ��ȡ���ִ����ݵ�������������
        pChinese ++;                            // �ƴ�����
        
        if (pChinese >= OLED_CHN_CHAR_WIDTH)    // ��ȡ����һ�������ĺ���
        {
            pChinese = 0;    // �ƴι���
            const void* fontArray;
				if (FontSize == OLED_8X8_FULL) {
					fontArray = (const void*) OLED_CF8x8;
				}
				else if (FontSize == OLED_12X12_FULL) {
					fontArray = (const void*) OLED_CF12x12;
				}
				else if (FontSize == OLED_16X16_FULL) {
					fontArray = (const void*) OLED_CF16x16;
				}
				else if (FontSize == OLED_20X20_FULL) {
					fontArray = (const void*) OLED_CF20x20;
				}

				if(FontSize==OLED_8X8_FULL){
					for (pIndex = 0; strcmp(((const ChineseCell8x8_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
					{
						if (strcmp(((const ChineseCell8x8_t*)fontArray)[pIndex].Index, SingleChinese) == 0){break;}
					}
					OLED_ShowImageArea(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_8X8_FULL, Y, OLED_8X8_FULL, OLED_8X8_FULL, RangeX, RangeY, RangeWidth, RangeHeight, ((const ChineseCell8x8_t*)fontArray)[pIndex].Data);
				}else
				if(FontSize==OLED_12X12_FULL){
					for (pIndex = 0; strcmp(((const ChineseCell12x12_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
					{
						if (strcmp(((const ChineseCell12x12_t*)fontArray)[pIndex].Index, SingleChinese) == 0){break;}
					}
					OLED_ShowImageArea(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_12X12_FULL, Y, OLED_12X12_FULL, OLED_12X12_FULL, RangeX, RangeY, RangeWidth, RangeHeight, ((const ChineseCell12x12_t*)fontArray)[pIndex].Data);
				}else
				if(FontSize==OLED_16X16_FULL){
					for (pIndex = 0; strcmp(((const ChineseCell16x16_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
					{
						if (strcmp(((const ChineseCell16x16_t*)fontArray)[pIndex].Index, SingleChinese) == 0){break;}
					}
					OLED_ShowImageArea(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_16X16_FULL, Y, OLED_16X16_FULL, OLED_16X16_FULL, RangeX, RangeY, RangeWidth, RangeHeight,((const ChineseCell16x16_t*)fontArray)[pIndex].Data);
				}else
				if(FontSize==OLED_20X20_FULL){
					for (pIndex = 0; strcmp(((const ChineseCell20x20_t*)fontArray)[pIndex].Index, "") != 0; pIndex ++)
					{
						if (strcmp(((const ChineseCell20x20_t*)fontArray)[pIndex].Index, SingleChinese) == 0){break;}
					}
					OLED_ShowImageArea(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * OLED_20X20_FULL, Y, OLED_20X20_FULL, OLED_20X20_FULL, RangeX, RangeY, RangeWidth, RangeHeight,((const ChineseCell20x20_t*)fontArray)[pIndex].Data);
				}
			}
		}
#else
	(void)RangeX;
	(void)RangeY;
	(void)RangeWidth;
	(void)RangeHeight;
	(void)X;
	(void)Y;
	(void)Chinese;
	(void)FontSize;
#endif
}




/**
  * @brief ��ָ������Χ��OLED��ʾ���ִ�
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param Chinese ָ��Ҫ��ʾ�ĺ��ִ�����Χ������ȫ��Ϊ���ֻ���ȫ���ַ�����Ҫ�����κΰ���ַ�
  * @param format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
  * @param ... ��ʽ���ַ��������б�
  * @param FontSize ָ�������С
  *           ��Χ��OLED_8X16		��8���أ���16����
  *    							OLED_7X12		��7���أ���12����
  *                 OLED_6X8		��6���أ���8����
  * @retval ��
  */
 

void OLED_PrintfArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight, int16_t X, int16_t Y,uint8_t FontSize, char *format, ...)
{
	//�����п�����ʾ�������ַ���������128
	char String[MAX_STRING_LENGTH];						//�����ַ�����
	va_list arg;							//����ɱ�����б��������͵ı���arg
	va_start(arg, format);					//��format��ʼ�����ղ����б���arg����
	vsprintf(String, format, arg);			//ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б����ַ�������
	va_end(arg);							//��������arg
	OLED_ShowStringArea(RangeX, RangeY, RangeWidth, RangeHeight, X, Y, String, FontSize);//OLED��ʾ�ַ����飨�ַ�����
	
}


/**
  * @brief ��ָ������Χ��OLED��ʾ����ַ�����������ASCII��
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param String ָ��Ҫ��ʾ�Ļ���ַ�������Χ��ȫ���ַ������ַ�������
  *           ��ʾ�ĺ�����Ҫ��OLED_Data.c���OLED_CF16x16��OLED_CF12x12���鶨��
  *           δ�ҵ�ָ������ʱ������ʾĬ��ͼ�Σ�һ�������ڲ�һ���ʺţ�
  * @param ChineseFontSize ָ���������ִ�С��OLED_12X12��OLED_16X16��OLED_8X8
  * @param ASCIIFontSize  ָ��ASCII���ִ�С,OLED_6X8��OLED_7X12��OLED_8X16
  * @retval ��
  */

void OLED_ShowMixStringArea(int16_t RangeX, int16_t RangeY, int16_t RangeWidth, int16_t RangeHeight, int16_t X, int16_t Y, char *String, uint8_t ChineseFontSize, uint8_t ASCIIFontSize)
{
  	while (*String != '\0') {
		  if (*String & 0x80) { // �ж������ַ������λΪ1��
#if OLED_ENABLE_CHINESE
			char Chinese[OLED_CHN_CHAR_WIDTH + 1]; // ���ݱ��볤�ȶ�̬��������
			for (uint8_t i = 0; i < OLED_CHN_CHAR_WIDTH; i++) {
			  	Chinese[i] = *(String + i); // ���������ַ�����
			}
			Chinese[OLED_CHN_CHAR_WIDTH] = '\0'; // �����ַ���������
			OLED_ShowChineseArea(RangeX, RangeY, RangeWidth, RangeHeight, X, Y, Chinese, ChineseFontSize);
			X += ChineseFontSize; // ����X����
			String += OLED_CHN_CHAR_WIDTH; // �����Ѵ����������ַ�
#else
			(void)ChineseFontSize;
			OLED_ShowCharArea(RangeX, RangeY, RangeWidth, RangeHeight, X, Y, '?', ASCIIFontSize);
			X += ASCIIFontSize;
			String++;
#endif
		} else { // ASCII�ַ�����
			OLED_ShowCharArea(RangeX, RangeY, RangeWidth, RangeHeight, X, Y, *String, ASCIIFontSize);
			X += ASCIIFontSize; // ����X����
			String++; // ������һ���ַ�
		}
	}
}


/**
  * @brief OLEDʹ��printf������ָ�������ڴ�ӡ��ʽ���ַ������˺�����bilibili@��nm������ ����
  * @param RangeX ָ���ַ�������ʾ��Χ�����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param RangeY ָ���ַ�������ʾ��Χ�����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param RangeWidth ָ����Χ����
  * @param RangeHeight ָ����Χ�߶�
  * @param X ָ���ַ����Ͻǵĺ����꣬��Χ����ֵ~OLED_WIDTH-1
  * @param Y ָ���ַ����Ͻǵ������꣬��Χ����ֵ~OLED_HEIGHT-1
  * @param ChineseFontSize ָ�����������С,OLED_8X8_FULL,OLED_12X12_FULL,OLED_16X16_FULL,OLED_20X20_FULL
  * @param ASCIIFontSize ָ��ASCII�����С,OLED_6X8_HALF,OLED_7X12_HALF,OLED_8X16_HALF,OLED_10X20_HALF
			format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
  * @param ... ��ʽ���ַ��������б�
  * @return ��
  */

void OLED_PrintfMixArea(int16_t RangeX,int16_t RangeY,int16_t RangeWidth,int16_t RangeHeight,int16_t X, int16_t Y, uint8_t ChineseFontSize,uint8_t ASCIIFontSize, char *format, ...)
{
	//�����п�����ʾ�������ַ���������128
	char String[MAX_STRING_LENGTH];						//�����ַ�����
	va_list arg;							//����ɱ�����б��������͵ı���arg
	va_start(arg, format);					//��format��ʼ�����ղ����б���arg����
	vsprintf(String, format, arg);			//ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б����ַ�������
	va_end(arg);							//��������arg
	OLED_ShowMixStringArea(RangeX,RangeY,RangeWidth,RangeHeight,X, Y, String, ChineseFontSize,ASCIIFontSize);//OLED��ʾ�ַ����飨�ַ�����
}





/**
  * ��    ����OLED��ָ��λ�û�һ����
  * ��    ����X ָ����ĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ����������꣬��Χ��0~OLED_HEIGHT-1
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawPoint(int16_t X, int16_t Y)
{
	/*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
	if(X < 0 || Y < 0 || X > OLED_WIDTH-1 || Y > OLED_HEIGHT-1) {return;}
	
	/*���Դ�����ָ��λ�õ�һ��Bit������1*/
	OLED_DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
}

/**
  * ��    ����OLED��ȡָ��λ�õ��ֵ
  * ��    ����X ָ����ĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ����������꣬��Χ��0~OLED_HEIGHT-1
  * �� �� ֵ��ָ��λ�õ��Ƿ��ڵ���״̬��1��������0��Ϩ��
  */
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y)
{
	/*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
	if (X > OLED_WIDTH-1) {return 0;}
	if (Y > OLED_HEIGHT-1) {return 0;}
	
	/*�ж�ָ��λ�õ�����*/
	if (OLED_DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
	{
		return 1;	//Ϊ1������1
	}
	return 0;		//���򣬷���0
}



/**
  * ��    ����OLED����
  * ��    ����X0 ָ��һ���˵�ĺ����꣬��Χ��0~127
  * ��    ����Y0 ָ��һ���˵�������꣬��Χ��0~63
  * ��    ����X1 ָ����һ���˵�ĺ����꣬��Χ��0~127
  * ��    ����Y1 ָ����һ���˵�������꣬��Χ��0~63
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1)
{
	int16_t x, y, dx, dy, d, incrE, incrNE, temp;
	int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
	uint8_t yflag = 0, xyflag = 0;
	
	if (y0 == y1)		//���ߵ�������
	{
		/*0�ŵ�X�������1�ŵ�X���꣬�򽻻�����X����*/
		if (x0 > x1) {temp = x0; x0 = x1; x1 = temp;}
		
		/*����X����*/
		for (x = x0; x <= x1; x ++)
		{
			OLED_DrawPoint(x, y0);	//���λ���
		}
	}
	else if (x0 == x1)	//���ߵ�������
	{
		/*0�ŵ�Y�������1�ŵ�Y���꣬�򽻻�����Y����*/
		if (y0 > y1) {temp = y0; y0 = y1; y1 = temp;}
		
		/*����Y����*/
		for (y = y0; y <= y1; y ++)
		{
			OLED_DrawPoint(x0, y);	//���λ���
		}
	}
	else				//б��
	{
		/*ʹ��Bresenham�㷨��ֱ�ߣ����Ա����ʱ�ĸ������㣬Ч�ʸ���*/
		/*�ο��ĵ���https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
		/*�ο��̳̣�https://www.bilibili.com/video/BV1364y1d7Lo*/
		
		if (x0 > x1)	//0�ŵ�X�������1�ŵ�X����
		{
			/*������������*/
			/*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ���������������ޱ�Ϊ��һ��������*/
			temp = x0; x0 = x1; x1 = temp;
			temp = y0; y0 = y1; y1 = temp;
		}
		
		if (y0 > y1)	//0�ŵ�Y�������1�ŵ�Y����
		{
			/*��Y����ȡ��*/
			/*ȡ����Ӱ�컭�ߣ����ǻ��߷����ɵ�һ�������ޱ�Ϊ��һ����*/
			y0 = -y0;
			y1 = -y1;
			
			/*�ñ�־λyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
			yflag = 1;
		}
		
		if (y1 - y0 > x1 - x0)	//����б�ʴ���1
		{
			/*��X������Y���껥��*/
			/*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ����0~90�ȷ�Χ��Ϊ��һ����0~45�ȷ�Χ*/
			temp = x0; x0 = y0; y0 = temp;
			temp = x1; x1 = y1; y1 = temp;
			
			/*�ñ�־λxyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
			xyflag = 1;
		}
		
		/*����ΪBresenham�㷨��ֱ��*/
		/*�㷨Ҫ�󣬻��߷������Ϊ��һ����0~45�ȷ�Χ*/
		dx = x1 - x0;
		dy = y1 - y0;
		incrE = 2 * dy;
		incrNE = 2 * (dy - dx);
		d = 2 * dy - dx;
		x = x0;
		y = y0;
		
		/*����ʼ�㣬ͬʱ�жϱ�־λ�������껻����*/
		if (yflag && xyflag){OLED_DrawPoint(y, -x);}
		else if (yflag)		{OLED_DrawPoint(x, -y);}
		else if (xyflag)	{OLED_DrawPoint(y, x);}
		else				{OLED_DrawPoint(x, y);}
		
		while (x < x1)		//����X���ÿ����
		{
			x ++;
			if (d < 0)		//��һ�����ڵ�ǰ�㶫��
			{
				d += incrE;
			}
			else			//��һ�����ڵ�ǰ�㶫����
			{
				y ++;
				d += incrNE;
			}
			
			/*��ÿһ���㣬ͬʱ�жϱ�־λ�������껻����*/
			if (yflag && xyflag){OLED_DrawPoint(y, -x);}
			else if (yflag)		{OLED_DrawPoint(x, -y);}
			else if (xyflag)	{OLED_DrawPoint(y, x);}
			else				{OLED_DrawPoint(x, y);}
		}	
	}
}

/**
  * ��    ����OLED����
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~127
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~63
  * ��    ����Width ָ�����εĿ��ȣ���Χ��0~128
  * ��    ����Height ָ�����εĸ߶ȣ���Χ��0~64
  * ��    ����IsFilled ָ�������Ƿ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º������˺����������ģ�����ʱ��Ч�ʸ���
  */
void OLED_DrawRectangle(int16_t X, int16_t Y, int16_t Width, int16_t Height, uint8_t IsFilled)
{
    if (Width == 0 || Height == 0) { return; } // ���Ȼ�߶�Ϊ0��������

    int16_t X_start = X;
    int16_t X_end = X + Width - 1;
    int16_t Y_start = Y;
    int16_t Y_end = Y + Height - 1;

    // ������������Ļ��Χ��
    if (X_start < 0) X_start = 0;
    if (X_end >= OLED_WIDTH) X_end = OLED_WIDTH - 1;
    if (Y_start < 0) Y_start = 0;
    if (Y_end >= OLED_HEIGHT) Y_end = OLED_HEIGHT - 1;

    // ������Ч���Ⱥ͸߶�
    int16_t validWidth = X_end - X_start + 1;
    int16_t validHeight = Y_end - Y_start + 1;
    if (validWidth <= 0 || validHeight <= 0) { return; }

    
    // ������ʼ�ͽ���ҳ
    int16_t start_page = Y_start / 8;
    int16_t end_page = Y_end / 8;

    // ����ÿҳ������
    uint8_t start_mask = 0xFF << (Y_start % 8);
    uint8_t end_mask = 0xFF >> (7 - (Y_end % 8));

    
		if(IsFilled){
			// ����ÿһ�У�Ӧ������
			for (int16_t x = X_start; x <= X_end; x++) {
					for (int16_t page = start_page; page <= end_page; page++) {
							uint8_t mask = 0xFF;
							if (page == start_page) mask &= start_mask;
							if (page == end_page) mask &= end_mask;
							if (page >= 0 && page < OLED_HEIGHT / 8) { // ȷ��ҳ����Ч
									OLED_DisplayBuf[page][x] |= mask;
							}
					}
			}
		}else{
			// ���ƾ��α߿�
        for (int16_t i = X; i <= X + Width - 1; i++) {
            OLED_DrawPoint(i, Y);
            OLED_DrawPoint(i, Y + Height - 1);
        }
        for (int16_t i = Y; i <= Y + Height - 1; i++) {
            OLED_DrawPoint(X, i);
            OLED_DrawPoint(X + Width - 1, i);
        }
		}
		
		
   
}
/**
  * ��    ����OLED������
  * ��    ����X0 ָ����һ���˵�ĺ����꣬��Χ��0~127
  * ��    ����Y0 ָ����һ���˵�������꣬��Χ��0~63
  * ��    ����X1 ָ���ڶ����˵�ĺ����꣬��Χ��0~127
  * ��    ����Y1 ָ���ڶ����˵�������꣬��Χ��0~63
  * ��    ����X2 ָ���������˵�ĺ����꣬��Χ��0~127
  * ��    ����Y2 ָ���������˵�������꣬��Χ��0~63
  * ��    ����IsFilled ָ���������Ƿ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled)
{
	int16_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
	int16_t i, j;
	int16_t vx[] = {X0, X1, X2};
	int16_t vy[] = {Y0, Y1, Y2};
	
	if (!IsFilled)			//ָ�������β����
	{
		/*���û��ߺ���������������ֱ������*/
		OLED_DrawLine(X0, Y0, X1, Y1);
		OLED_DrawLine(X0, Y0, X2, Y2);
		OLED_DrawLine(X1, Y1, X2, Y2);
	}
	else					//ָ�����������
	{
		/*�ҵ���������С��X��Y����*/
		if (X1 < minx) {minx = X1;}
		if (X2 < minx) {minx = X2;}
		if (Y1 < miny) {miny = Y1;}
		if (Y2 < miny) {miny = Y2;}
		
		/*�ҵ�����������X��Y����*/
		if (X1 > maxx) {maxx = X1;}
		if (X2 > maxx) {maxx = X2;}
		if (Y1 > maxy) {maxy = Y1;}
		if (Y2 > maxy) {maxy = Y2;}
		
		/*��С�������֮��ľ���Ϊ������Ҫ��������*/
		/*���������������еĵ�*/
		/*����X����*/
		for (i = minx; i <= maxx; i ++)
		{
			/*����Y����*/
			for (j = miny; j <= maxy; j ++)
			{
				/*����OLED_pnpoly���ж�ָ�����Ƿ���ָ��������֮��*/
				/*����ڣ��򻭵㣬������ڣ���������*/
				if (OLED_pnpoly(3, vx, vy, i, j)) {OLED_DrawPoint(i, j);}
			}
		}
	}
}

/**
  * ��    ����OLED��Բ
  * ��    ����X ָ��Բ��Բ�ĺ����꣬��Χ��0~127
  * ��    ����Y ָ��Բ��Բ�������꣬��Χ��0~63
  * ��    ����Radius ָ��Բ�İ뾶����Χ��0~255
  * ��    ����IsFilled ָ��Բ�Ƿ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawCircle(int16_t X, int16_t Y, int16_t Radius, uint8_t IsFilled)
{
	int16_t x, y, d, j;
	
	/*ʹ��Bresenham�㷨��Բ�����Ա����ʱ�ĸ������㣬Ч�ʸ���*/
	/*�ο��ĵ���https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
	/*�ο��̳̣�https://www.bilibili.com/video/BV1VM4y1u7wJ*/
	
	d = 1 - Radius;
	x = 0;
	y = Radius;
	
	/*��ÿ���˷�֮һԲ������ʼ��*/
	OLED_DrawPoint(X + x, Y + y);
	OLED_DrawPoint(X - x, Y - y);
	OLED_DrawPoint(X + y, Y + x);
	OLED_DrawPoint(X - y, Y - x);
	
	if (IsFilled)		//ָ��Բ���
	{
		/*������ʼ��Y����*/
		for (j = -y; j < y; j ++)
		{
			/*��ָ�����򻭵㣬��䲿��Բ*/
			OLED_DrawPoint(X, Y + j);
		}
	}
	
	while (x < y)		//����X���ÿ����
	{
		x ++;
		if (d < 0)		//��һ�����ڵ�ǰ�㶫��
		{
			d += 2 * x + 1;
		}
		else			//��һ�����ڵ�ǰ�㶫�Ϸ�
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*��ÿ���˷�֮һԲ���ĵ�*/
		OLED_DrawPoint(X + x, Y + y);
		OLED_DrawPoint(X + y, Y + x);
		OLED_DrawPoint(X - x, Y - y);
		OLED_DrawPoint(X - y, Y - x);
		OLED_DrawPoint(X + x, Y - y);
		OLED_DrawPoint(X + y, Y - x);
		OLED_DrawPoint(X - x, Y + y);
		OLED_DrawPoint(X - y, Y + x);
		
		if (IsFilled)	//ָ��Բ���
		{
			/*�����м䲿��*/
			for (j = -y; j < y; j ++)
			{
				/*��ָ�����򻭵㣬��䲿��Բ*/
				OLED_DrawPoint(X + x, Y + j);
				OLED_DrawPoint(X - x, Y + j);
			}
			
			/*�������ಿ��*/
			for (j = -x; j < x; j ++)
			{
				/*��ָ�����򻭵㣬��䲿��Բ*/
				OLED_DrawPoint(X - y, Y + j);
				OLED_DrawPoint(X + y, Y + j);
			}
		}
	}
}

/**
  * ��    ����OLED����Բ
  * ��    ����X ָ����Բ��Բ�ĺ����꣬��Χ��0~127
  * ��    ����Y ָ����Բ��Բ�������꣬��Χ��0~63
  * ��    ����A ָ����Բ�ĺ�����᳤�ȣ���Χ��0~255
  * ��    ����B ָ����Բ��������᳤�ȣ���Χ��0~255
  * ��    ����IsFilled ָ����Բ�Ƿ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawEllipse(int16_t X, int16_t Y, int16_t A, int16_t B, uint8_t IsFilled)
{
	int16_t x, y, j;
	int16_t a = A, b = B;
	float d1, d2;
	
	/*ʹ��Bresenham�㷨����Բ�����Ա��ⲿ�ֺ�ʱ�ĸ������㣬Ч�ʸ���*/
	/*�ο����ӣ�https://blog.csdn.net/myf_666/article/details/128167392*/
	
	x = 0;
	y = b;
	d1 = b * b + a * a * (-b + 0.5);
	
	if (IsFilled)	//ָ����Բ���
	{
		/*������ʼ��Y����*/
		for (j = -y; j < y; j ++)
		{
			/*��ָ�����򻭵㣬��䲿����Բ*/
			OLED_DrawPoint(X, Y + j);
			OLED_DrawPoint(X, Y + j);
		}
	}
	
	/*����Բ������ʼ��*/
	OLED_DrawPoint(X + x, Y + y);
	OLED_DrawPoint(X - x, Y - y);
	OLED_DrawPoint(X - x, Y + y);
	OLED_DrawPoint(X + x, Y - y);
	
	/*����Բ�м䲿��*/
	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 <= 0)		//��һ�����ڵ�ǰ�㶫��
		{
			d1 += b * b * (2 * x + 3);
		}
		else				//��һ�����ڵ�ǰ�㶫�Ϸ�
		{
			d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			y --;
		}
		x ++;
		
		if (IsFilled)	//ָ����Բ���
		{
			/*�����м䲿��*/
			for (j = -y; j < y; j ++)
			{
				/*��ָ�����򻭵㣬��䲿����Բ*/
				OLED_DrawPoint(X + x, Y + j);
				OLED_DrawPoint(X - x, Y + j);
			}
		}
		
		/*����Բ�м䲿��Բ��*/
		OLED_DrawPoint(X + x, Y + y);
		OLED_DrawPoint(X - x, Y - y);
		OLED_DrawPoint(X - x, Y + y);
		OLED_DrawPoint(X + x, Y - y);
	}
	
	/*����Բ���ಿ��*/
	d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	
	while (y > 0)
	{
		if (d2 <= 0)		//��һ�����ڵ�ǰ�㶫��
		{
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x ++;
			
		}
		else				//��һ�����ڵ�ǰ�㶫�Ϸ�
		{
			d2 += a * a * (-2 * y + 3);
		}
		y --;
		
		if (IsFilled)	//ָ����Բ���
		{
			/*�������ಿ��*/
			for (j = -y; j < y; j ++)
			{
				/*��ָ�����򻭵㣬��䲿����Բ*/
				OLED_DrawPoint(X + x, Y + j);
				OLED_DrawPoint(X - x, Y + j);
			}
		}
		
		/*����Բ���ಿ��Բ��*/
		OLED_DrawPoint(X + x, Y + y);
		OLED_DrawPoint(X - x, Y - y);
		OLED_DrawPoint(X - x, Y + y);
		OLED_DrawPoint(X + x, Y - y);
	}
}

/**
  * ��    ����OLED��Բ��
  * ��    ����X ָ��Բ����Բ�ĺ����꣬��Χ��0~127
  * ��    ����Y ָ��Բ����Բ�������꣬��Χ��0~63
  * ��    ����Radius ָ��Բ���İ뾶����Χ��0~255
  * ��    ����StartAngle ָ��Բ������ʼ�Ƕȣ���Χ��-180~180
  *           ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
  * ��    ����EndAngle ָ��Բ������ֹ�Ƕȣ���Χ��-180~180
  *           ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
  * ��    ����IsFilled ָ��Բ���Ƿ���䣬����Ϊ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawArc(int16_t X, int16_t Y, int16_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
	int16_t x, y, d, j;
	if(Radius <=0){return;} //�뾶Ϊ0��ֱ�ӷ���
	/*�˺�������Bresenham�㷨��Բ�ķ���*/
	
	d = 1 - Radius;
	x = 0;
	y = Radius;
	
	/*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
	if (OLED_IsInAngle(x, y, StartAngle, EndAngle))	{OLED_DrawPoint(X + x, Y + y);}
	if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
	if (OLED_IsInAngle(y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
	if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
	
	if (IsFilled)	//ָ��Բ�����
	{
		/*������ʼ��Y����*/
		for (j = -y; j < y; j ++)
		{
			/*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
			if (OLED_IsInAngle(0, j, StartAngle, EndAngle)) {OLED_DrawPoint(X, Y + j);}
		}
	}
	
	while (x < y)		//����X���ÿ����
	{
		x ++;
		if (d < 0)		//��һ�����ڵ�ǰ�㶫��
		{
			d += 2 * x + 1;
		}
		else			//��һ�����ڵ�ǰ�㶫�Ϸ�
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
		if (OLED_IsInAngle(x, y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + y);}
		if (OLED_IsInAngle(y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
		if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
		if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
		if (OLED_IsInAngle(x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y - y);}
		if (OLED_IsInAngle(y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y - x);}
		if (OLED_IsInAngle(-x, y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + y);}
		if (OLED_IsInAngle(-y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + x);}
		
		if (IsFilled)	//ָ��Բ�����
		{
			/*�����м䲿��*/
			for (j = -y; j < y; j ++)
			{
				/*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
				if (OLED_IsInAngle(x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + j);}
				if (OLED_IsInAngle(-x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + j);}
			}
			
			/*�������ಿ��*/
			for (j = -x; j < x; j ++)
			{
				/*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
				if (OLED_IsInAngle(-y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + j);}
				if (OLED_IsInAngle(y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + j);}
			}
		}
	}
}



/**
  * ��    ����OLEDԲ�Ǿ���
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~OLED_WIDTH-1
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~OLED_HEIGHT-1
  * ��    ����Width ָ�����εĿ��ȣ���Χ��0~128
  * ��    ����Height ָ�����εĸ߶ȣ���Χ��0~64
  * ��    ����Radius Բ�ǰ뾶
  * ��    ����IsFilled ָ�������Ƿ����
  *           ��Χ��OLED_UNFILLED		�����
  *                 OLED_FILLED			���
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_DrawRoundedRectangle(int16_t X, int16_t Y, int16_t Width, int16_t Height, int16_t Radius, uint8_t IsFilled)
{
    // ��ȫ���
    if (Width == 0 || Height == 0) return;  // ���Ȼ�߶�Ϊ0,ֱ�ӷ���
    if (Radius > Width / 2 || Radius > Height / 2) {
        Radius = (Width < Height ? Width : Height) / 2;  // ����Բ�ǰ뾶���������ߵ�һ��
    }
    if (Radius <= 0) {
        OLED_DrawRectangle(X, Y, Width, Height, IsFilled);  // ����뾶Ϊ0,�˻�Ϊ��ͨ����
        return;
    }
		// �����ĸ�Բ��
		OLED_DrawArc(X + Radius, Y + Radius, Radius,180,  -90, IsFilled);
		OLED_DrawArc(X + Width - Radius - 1, Y + Radius, Radius,-90,  0, IsFilled);
		OLED_DrawArc(X + Radius, Y + Height - Radius - 1, Radius,90,  180, IsFilled);
		OLED_DrawArc(X + Width - Radius - 1, Y + Height - Radius - 1, Radius,0,  90, IsFilled);


    // ������ƾ�������
    if (IsFilled) {
        OLED_DrawRectangle(X + Radius, Y, Width - 2 * Radius, Height, OLED_FILLED);
        OLED_DrawRectangle(X, Y + Radius, Width, Height - 2 * Radius, OLED_FILLED);
    } else {
        // ���ƶ����͵ײ���ֱ��
        OLED_DrawLine(X + Radius, Y, X + Width - Radius - 1, Y);
        OLED_DrawLine(X + Radius, Y + Height - 1, X + Width - Radius - 1, Y + Height - 1);
        // ���������Ҳ��ֱ��
        OLED_DrawLine(X, Y + Radius, X, Y + Height - Radius - 1);
        OLED_DrawLine(X + Width - 1, Y + Radius, X + Width - 1, Y + Height - Radius - 1);
    }
}









