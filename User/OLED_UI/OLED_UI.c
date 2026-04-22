#include "OLED_UI.h"


#ifdef OLED_UI
/**
 * @brief ����Ŀ��Դ��ַ��
 * @param "https://github.com/bdth-7777777/OLED_UI"
 */
/*OLED_UIȫ�ֱ������� */
OLED_UI_Counter OLED_FPS;
OLED_Key OLED_UI_Key;
OLED_Key OLED_UI_LastKey;
MenuPage*  CurrentMenuPage;
MenuWindow *CurrentWindow;
MutexFlag KeyEnterFlag;
MutexFlag FadeOutFlag;
MutexFlag WindowFlag;
bool ColorMode;
bool OLED_UI_ShowFps;
int16_t OLED_UI_Brightness;
OLED_UI_WindowSustainCounter OLED_SustainCounter;
int16_t WindowProbDeltaData;
/***********************************************************************************************/
/***************************��Щ�������ڴ洢��Ҫ�󶨶����Ŀؼ��Ĳ���*******************************/

// OLED_UI_Cursor�����ڴ洢���Ľṹ�壬���ƹ����ƶ�
OLED_ChangeArea OLED_UI_Cursor;
// OLED_UI_MenuFrame�����ڴ洢�˵��߿�Ľṹ�壬���Ʋ˵��߿����ڲ�������ƶ�
OLED_ChangeArea OLED_UI_MenuFrame;
// OLED_UI_Window�����ڴ洢���ڵĽṹ�壬���ƴ������ڲ�������ƶ�
OLED_ChangeArea OLED_UI_Window;
// OLED_UI_ScrollBarHeight�����ڴ洢�������߶ȵĽṹ�壬���ƹ������߶ȵı仯
OLED_ChangeDistance OLED_UI_ScrollBarHeight;
// OLED_UI_ProbWidth�����ڴ洢���������ȵĽṹ�壬���ƽ��������ȵı仯
OLED_ChangeDistance OLED_UI_ProbWidth;
// OLED_UI_PageStartPoint�����ڴ洢ҳ����ʼ��Ľṹ�壬����ҳ��������ƶ�
OLED_ChangePoint OLED_UI_PageStartPoint ;
// OLED_UI_LineStep�����ڴ洢�м��Ľṹ�壬�����м��ı仯
OLED_ChangeDistance OLED_UI_LineStep;



/**
 * @brief ��ȡ��ǰ��Ļˢ���ʣ�����洢��ȫ�ֱ���OLED_FPS.value��
 * @param ��
 * @note �ú�����Ҫ����20ms�����ڵ��ã�����ᵼ�¼�������
 * @return ��
 */
void GetFPS(void){
	if(OLED_FPS.step<49){
		OLED_FPS.step++;
	}else{
		OLED_FPS.step=0;
		OLED_FPS.value = OLED_FPS.count;
		OLED_FPS.count=0;
	}
}

/**
 * @brief ��ʾ��ǰ��Ļˢ����
 * @param ��
 * @note �轫�˺���������ѭ�����У�ÿѭ��һ�μ�Ϊһ��ˢ�¡�
 * @return ��
 */
void OLED_UI_ShowFPS(void){
    OLED_FPS.count ++;
	
	if (OLED_UI_ShowFps){
		OLED_Printf(OLED_WIDTH - CalcStringWidth(OLED_8X8_FULL, OLED_6X8_HALF, "%d",OLED_FPS.value),0,OLED_6X8_HALF,"%d",OLED_FPS.value);
	}
}
/**
 * @brief ��ȡ��ǰҳ����������
 * @param style CHINESE�����ġ��� ASCII��ASCII��
 * @return ��ǰҳ����������
 */
OLED_Font GetOLED_Font(OLED_Font fontsize,bool style){
	//���ݵ�ǰҳ��������С��������
	OLED_Font ChineseFont,ASCIIFont;
	switch(fontsize){
		case OLED_UI_FONT_8:
			ChineseFont = OLED_8X8_FULL,ASCIIFont = OLED_6X8_HALF;break;
		case OLED_UI_FONT_12:
			ChineseFont = OLED_12X12_FULL,ASCIIFont = OLED_7X12_HALF;break;
		case OLED_UI_FONT_16:
			ChineseFont = OLED_16X16_FULL,ASCIIFont = OLED_8X16_HALF;break;
		case OLED_UI_FONT_20:
			ChineseFont = OLED_20X20_FULL,ASCIIFont = OLED_10X20_HALF;break;
		default:
			ChineseFont = OLED_12X12_FULL,ASCIIFont = OLED_7X12_HALF;break;
	}
	if(style == CHINESE){
		return ChineseFont;
	}else{
		return ASCIIFont;
	}

}
/**
 * @brief ��ת��ʾ���
 * @param X ���X����
 * @param Y ���Y����
 * @param Width ������
 * @param Height ���߶�
 * @param Style �����ʽ
 * @note �ú������ڷ�ת��ʾ��꣬ʹ����ʾΪ��ɫ
 * @return ��
 */
void ReverseCoordinate(int16_t X, int16_t Y, int16_t Width, int16_t Height,uint8_t Style){
	switch(Style){
		
		case REVERSE_RECTANGLE://���η�ɫ
			OLED_ReverseArea(X, Y, Width, Height);
			break;
		case REVERSE_ROUNDRECTANGLE://Բ�Ǿ��η�ɫ
			if(Width >= 3 && Height >= 3){
				OLED_ReverseArea(X, Y, 1, 1);
				OLED_ReverseArea(X+Width-1, Y, 1, 1);
				OLED_ReverseArea(X, Y+Height-1, 1, 1);
				OLED_ReverseArea(X+Width-1, Y+Height-1, 1, 1);
			}
			OLED_ReverseArea(X, Y, Width, Height);
			break;

		case HOLLOW_RECTANGLE://���ľ���
			OLED_ReverseArea(X, Y, Width, Height);
			OLED_ReverseArea(X+1, Y+1, Width-2, Height-2);
			break;
		case HOLLOW_ROUNDRECTANGLE://���ľ���
			OLED_ReverseArea(X, Y, Width, Height);
			OLED_ReverseArea(X+1, Y+1, Width-2, Height-2);
			if(Width >= 3){
				OLED_ReverseArea(X, Y, 1, 1);
				OLED_ReverseArea(X+Width-1, Y, 1, 1);
			}
			if(Height >= 3){
				OLED_ReverseArea(X, Y+Height-1, 1, 1);
				OLED_ReverseArea(X+Width-1, Y+Height-1, 1, 1);
			}
			break;
		case REVERSE_BLOCK://С����
			
			OLED_ReverseArea(X, Y + 1, GetOLED_Font(CurrentMenuPage->General_FontSize,ASCII), Height);
			
			break;
		case NOT_SHOW:
			break;
		default:
			OLED_ReverseArea(X, Y, Width, Height);
		break;
	}
}

/** 
 * @brief����ָ������Ӧ��ģʽ������Ч��(�ɰ������)
 * @param x0 ������ʼX����
 * @param y0 ������ʼY����
 * @param width �������
 * @param height ����߶�
 * @param fadeLevel ������λ��1��5֮���ֵ����ʾ��ͬ������Ϩ��ģʽ
 * @note �ú���������ָ������Ӧ��ģʽ������Ч����ʹ�ø�����������𽥱䰵��Ч�������ɰ��������
*/
void OLED_UI_FadeOut_Masking(int16_t x0, int16_t y0, int16_t width, int16_t height, int8_t fadeLevel) {
    // ��鲢��������Χ
    if (x0 < 0) {
        width += x0;
        x0 = 0;
    }
    if (y0 < 0) {
        height += y0;
        y0 = 0;
    }
    if (x0 + width > OLED_WIDTH) {
        width = OLED_WIDTH - x0;
    }
    if (y0 + height > OLED_HEIGHT) {
        height = OLED_HEIGHT - y0;
    }
    if (width <= 0 || height <= 0) {
        return;
    }

    // ȷ��������λ����Ч��Χ��
    if (fadeLevel < 1 || fadeLevel > 5) {
        return;
    }

    // ����2x2����Ľ���ģʽ
    // ÿ�������ʾһ��2x2��������Щ������ҪϨ��
    // 0��ʾ��������1��ʾϨ��
    const uint8_t patterns[5][2][2] = {
        {{0, 0},  // Level 1: ȫ��
         {0, 0}},
        
        {{1, 0},  // Level 2: ���Ͻ�Ϩ��
         {0, 0}},
        
        {{1, 0},  // Level 3: ���ϽǺ����½�Ϩ��
         {0, 1}},
        
        {{1, 0},  // Level 4: ֻ�������Ͻ�
         {1, 1}},
        
        {{1, 1},  // Level 5: ȫ��
         {1, 1}}
    };

    // ����߽�
    int16_t xEnd = x0 + width;
    int16_t yEnd = y0 + height;

    // Ӧ�ý���Ч��
    for (int16_t y = y0; y < yEnd; y++) {
        int page = y / 8;
        int bit_pos = y % 8;
        uint8_t pixel_mask = 1 << bit_pos;
        
        for (int16_t x = x0; x < xEnd; x++) {
            // ������2x2�����е����λ��
            int grid_x = (x - x0) % 2;
            int grid_y = (y - y0) % 2;
            
            // ���ݽ������������λ�þ����Ƿ�Ϩ������
            if (patterns[fadeLevel - 1][grid_y][grid_x]) {
                OLED_DisplayBuf[page][x] &= ~pixel_mask;
            }
        }
    }
}





/**
 * @brief ����ǰ�˵�ҳ�������Ԫ�ؽ���
 * @param ��
 * @note �ú������ڽ���ǰ�˵�ҳ�������Ԫ���𽥱䰵��Ч�������ɰ��������
 * @return ��
 */
void OLED_UI_FadeoutCurrentArea(int16_t x, int16_t y, int16_t width, int16_t height) {
	if(CurrentMenuPage->General_MovingSpeed <= 0){
		OLED_Clear();
		return;
	}
    for(uint8_t i=1;i<=5;i++){
		// Ӧ�ý���Ч��
			
		OLED_UI_FadeOut_Masking(x,y,width,height,i);
		// ��ʾ����
        OLED_Update();
		Delay_ms(FADEOUT_TIME);
    }
	// Delay_ms(20);
}
/**
 * @brief ȫ������
 * @param ��
 * @note �ú������ڽ���ǰ�˵�ҳ�������Ԫ���𽥱䰵��Ч�������ɰ��������
 * @return ��
 */
void OLED_UI_FadeoutAllArea(void) {
	if(CurrentMenuPage->General_MovingSpeed <= 0){
		OLED_Clear();
		return;
	}
    for(uint8_t i=1;i<=5;i++){
		// Ӧ�ý���Ч��
			
		OLED_UI_FadeOut_Masking(0 ,0 , OLED_WIDTH, OLED_HEIGHT,i);
		// ��ʾ����
        OLED_Update();
		Delay_ms(FADEOUT_TIME);
    }
	// Delay_ms(20);
}

/**
 * @brief ��ȡ�˵���ṹ����������һ��Ԫ�ص�ID
 * @param items �ṹ������MenuItem��ָ��
 * @return �˵���ṹ�������Ԫ������
 */
MenuID GetMenuItemNum(MenuItem * items){
	MenuID num = 0;
	while(items[num].General_item_text != NULL){
		num+=1;
	}
	return num;
}


/**
 * @brief ���ݵ�ǰ��ѡ�Ķ�����ʽ���ı両��������
 * @param CurrentNum ��ǰֵ��ָ��
 * @param TargetNum Ŀ��ֵָ��
 * @param StartNum ��ʼֵָ��
 * @param CurrentStepNum ��ǰ����ָ��
 * @return ��
 */
void ChangeFloatNum(float *CurrentNum, float *TargetNum, float *ErrorNum, float *LastErrorNum, float * IntegralNum, float *DerivativeNum)  {
	if(CurrentMenuPage->General_MoveStyle ==  UNLINEAR){
		if(*CurrentNum == *TargetNum){
			return;
		}
		//����û����ٶ�����Ϊ0����ô��ǰֱֵ�ӵ���Ŀ��ֵ
		if(CurrentMenuPage->General_MovingSpeed <= 0){

			*ErrorNum = 0;
			*LastErrorNum = 0;
		    *CurrentNum = *TargetNum;
			return;
		}
		*LastErrorNum = *ErrorNum;
		//���㱾�����ֵ
		*ErrorNum = *TargetNum - *CurrentNum; 
		//���㵱ǰֵ
		*CurrentNum += 0.02*CurrentMenuPage->General_MovingSpeed * (*ErrorNum);
		//��Ŀ��ֵ�뵱ǰֵ���С���ٶ�ֵ��1/20ʱ����Ϊ�Ѿ�����Ŀ��ֵ
		if(fabs(*CurrentNum - *TargetNum) < CurrentMenuPage->General_MovingSpeed/20.0f){

			*ErrorNum = 0;
			*LastErrorNum = 0;
		    *CurrentNum = *TargetNum;
			return;
		}
	}
	//�����ǰ�Ķ�����ʽ��PID_CURVE��ʽ
	if(CurrentMenuPage->General_MoveStyle ==  PID_CURVE){
		/*����һ�����صķ�������Ϊ����ǰֵ����Ŀ��ֵ��ʱ�������������ˣ����ǻ����û�б����㡣����ʵ������������Ч������õġ� */
		//����û����ٶ�����Ϊ0����ô��ǰֱֵ�ӵ���Ŀ��ֵ�����������м�ֵ����
		if(CurrentMenuPage->General_MovingSpeed <= 0){

			*ErrorNum = 0;
			*LastErrorNum = 0;
			*DerivativeNum = 0;
			*IntegralNum = 0;
		    *CurrentNum = *TargetNum;
			return;
		}
		// ����PID����
		//����PID����
		float Kp = 0.02f * CurrentMenuPage->General_MovingSpeed;
		float Ki = 0.005f * CurrentMenuPage->General_MovingSpeed;
		float Kd = 0.002f ;

		//��¼��һ�����ֵ
		*LastErrorNum = *ErrorNum;
		//���㱾�����ֵ
		*ErrorNum = *TargetNum - *CurrentNum; 
		//�������ֵ
		*IntegralNum += *ErrorNum;
		//����΢��ֵ��������ʱ����Ϊ0.1s
		*DerivativeNum = (*ErrorNum - *LastErrorNum) / 0.1;
		//���㵱ǰֵ
		*CurrentNum += Kp * (*ErrorNum) + Ki *  (*IntegralNum) + Kd *(*DerivativeNum);
		//��Ŀ��ֵ�뵱ǰֵ���С��0.5ʱ����Ŀ��ֵǿ�Ƶ��ڵ�ǰֵ�����˻�������㣬���������м�ֵ����
		if(fabs(*TargetNum - *CurrentNum) < 0.5f){

			*ErrorNum = 0;
			*LastErrorNum = 0;
			*DerivativeNum = 0;
		    *CurrentNum = *TargetNum;
			return;
		}	
	}
	
}

/**
 * @brief �����Ըı�������
 * @param CurrentNum ��ǰֵ��ָ��
 * @param TargetNum Ŀ��ֵָ��
 * @param StepNum ����ָ��
 */
void ChangeDistance(OLED_ChangeDistance *distance){
	ChangeFloatNum(&distance->CurrentDistance,&distance->TargetDistance,&distance->Error,&distance->LastError,&distance->Integral,&distance->Derivative);
}

/**
 * @brief �����Ըı���������
 * @param OLED_MovingArea �ṹ�������ָ��
 * @return ��
 */
void ChangePoint(OLED_ChangePoint *point){
	ChangeFloatNum(&point->CurrentPoint.X,&point->TargetPoint.X,&point->Error.X,&point->LastError.X,&point->Integral.X,&point->Derivative.X);
	ChangeFloatNum(&point->CurrentPoint.Y,&point->TargetPoint.Y,&point->Error.Y,&point->LastError.Y,&point->Integral.Y,&point->Derivative.Y);
}
/**
 * @brief �����Ըı��������
 * @param OLED_MovingArea �ṹ�������ָ��
 * @return ��
 */
void ChangeArea(OLED_ChangeArea *area)	{
	ChangeFloatNum(&area->CurrentArea.X,&area->TargetArea.X,&area->Error.X,&area->LastError.X,&area->Integral.X,&area->Derivative.X);
	ChangeFloatNum(&area->CurrentArea.Y,&area->TargetArea.Y,&area->Error.Y,&area->LastError.Y,&area->Integral.Y,&area->Derivative.Y);
	ChangeFloatNum(&area->CurrentArea.Width,&area->TargetArea.Width,&area->Error.Width,&area->LastError.Width,&area->Integral.Width,&area->Derivative.Width);
	ChangeFloatNum(&area->CurrentArea.Height,&area->TargetArea.Height,&area->Error.Height,&area->LastError.Height,&area->Integral.Height,&area->Derivative.Height);
}




/**
 * @brief �Ե�ǰ�Ĳ˵�ҳ��Ĳ������м�����ʼ��
 * @param ��
 * @note ����ȷ���¼��½����Ӳ˵�ʱ�Ĳ���
 * @return ��
 */
void CurrentMenuPageInit(void){
	//�����ǰ�Ĳ˵�����ΪLIST
	if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
		//����ȫ��ҳ�浱ǰ��ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��+���λ����ʼ��
		OLED_UI_PageStartPoint.CurrentPoint.X = OLED_UI_MenuFrame.CurrentArea.X+CurrentMenuPage->List_StartPointX + OLED_WIDTH;
		OLED_UI_PageStartPoint.CurrentPoint.Y = OLED_UI_MenuFrame.CurrentArea.Y+CurrentMenuPage->List_StartPointY;
		//����ȫ��ҳ��Ŀ����ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��+���λ����ʼ��
		OLED_UI_PageStartPoint.TargetPoint.X = CurrentMenuPage->List_MenuArea.X+CurrentMenuPage->List_StartPointX;
		OLED_UI_PageStartPoint.TargetPoint.Y = CurrentMenuPage->List_MenuArea.Y+CurrentMenuPage->List_StartPointY;
		//����ȫ��ҳ��Ŀ������Ϊ��ǰ�˵��ṹ�������
		OLED_UI_MenuFrame.TargetArea.X = CurrentMenuPage->List_MenuArea.X;
		OLED_UI_MenuFrame.TargetArea.Y = CurrentMenuPage->List_MenuArea.Y;
		OLED_UI_MenuFrame.TargetArea.Width = CurrentMenuPage->List_MenuArea.Width;
		OLED_UI_MenuFrame.TargetArea.Height = CurrentMenuPage->List_MenuArea.Height;

		//���õ�ǰ�м��Ϊ-�����С������˵���չ���Ķ���Ч��
		OLED_UI_LineStep.CurrentDistance =-3;
		//����Ŀ���м��Ϊ�û����õ��о�
		OLED_UI_LineStep.TargetDistance = CurrentMenuPage->General_LineSpace;
		//���õ�ǰ���Ϊ��ǰ�˵���ĵ�һ��
		CurrentMenuPage->_ActiveMenuID = 0;
		//���õ�ǰ��λΪ0
		CurrentMenuPage->_Slot = 0;
	}else
	//�����ǰ�Ĳ˵�����ΪTILES
	if (CurrentMenuPage->General_MenuType == MENU_TYPE_TILES)
	{
		//����ȫ��ҳ��Ŀ����ʼ��Ϊ��Ļ��������ƫ�ư���������ȣ�ʹ�õ�ǰ�˵������
		OLED_UI_PageStartPoint.TargetPoint.X = CurrentMenuPage->Tiles_ScreenWidth/2-CurrentMenuPage->Tiles_TileWidth/2;
		//����ȫ��ҳ��Ŀ����ʼ��ΪԤ�����ʼ��
		OLED_UI_PageStartPoint.TargetPoint.Y = TILES_STARTPOINT_Y;
		//����ȫ��ҳ�浱ǰ��ʼ��Ϊһ������λ�ã�ʹ�ÿ�ʼʱ�ж���
		OLED_UI_PageStartPoint.CurrentPoint.X = -50;
		OLED_UI_PageStartPoint.CurrentPoint.Y = -CurrentMenuPage->Tiles_TileWidth;
		//���õ�ǰ�������Ϊ1�Ա��������Ч��
		OLED_UI_LineStep.CurrentDistance = 1;
		//����Ŀ��������Ϊ�û����õ��о�
		OLED_UI_LineStep.TargetDistance = CurrentMenuPage->General_LineSpace;
		//���õ�ǰ���Ϊ��ǰ�˵���ĵ�һ��
		CurrentMenuPage->_ActiveMenuID = 0;
	}
	//�������Ŀ�ʼ����㣬ȷ����ȷ�ϻ��Ƿ��ز���ʱ�������Ĳ˵�����¿�ʼ
	SetLineSplitZero();
	
}
/**
 * @brief ��ԭ�˵���������һ�ε�״̬
 * @param ��
 * @note ���ڷ�����һ���˵�ʱ�Ĳ���
 * @return ��
 */
void CurrentMenuPageBackUp(void){
	//�����ǰ�Ĳ˵�����ΪLIST
	if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
		//����ȫ��ҳ�浱ǰ��ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��+2
		OLED_UI_PageStartPoint.CurrentPoint.X = OLED_UI_MenuFrame.CurrentArea.X + CurrentMenuPage->List_StartPointX - OLED_WIDTH;
		OLED_UI_PageStartPoint.CurrentPoint.Y = CurrentMenuPage->_StartPoint.Y;
		//����ȫ��ҳ��Ŀ����ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��
		OLED_UI_PageStartPoint.TargetPoint.X = CurrentMenuPage->_StartPoint.X;
		OLED_UI_PageStartPoint.TargetPoint.Y = CurrentMenuPage->_StartPoint.Y;
		//���õ�ǰ�м��Ϊ-�����С�����춯��Ч��
		OLED_UI_LineStep.CurrentDistance = CurrentMenuPage->General_LineSpace;
		//����Ŀ���м��
		OLED_UI_LineStep.TargetDistance = CurrentMenuPage->General_LineSpace;
	}else
	//�����ǰ�Ĳ˵�����ΪTILES
	if (CurrentMenuPage->General_MenuType == MENU_TYPE_TILES)
	{
		//����ȫ��ҳ�浱ǰ��ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��+2
		OLED_UI_PageStartPoint.CurrentPoint.X = CurrentMenuPage->_StartPoint.X + CurrentMenuPage->Tiles_TileWidth;
		OLED_UI_PageStartPoint.CurrentPoint.Y = -CurrentMenuPage->Tiles_TileHeight-1;
		//����ȫ��ҳ��Ŀ����ʼ��Ϊ�˵��ṹ��Ŀ�ʼ��
		OLED_UI_PageStartPoint.TargetPoint.X = CurrentMenuPage->_StartPoint.X;
		OLED_UI_PageStartPoint.TargetPoint.Y = CurrentMenuPage->_StartPoint.Y;
		//���õ�ǰ�м��Ϊ-�����С�����춯��Ч��
		OLED_UI_LineStep.CurrentDistance = CurrentMenuPage->General_LineSpace;
		//����Ŀ���м��
		OLED_UI_LineStep.TargetDistance = CurrentMenuPage->General_LineSpace;
	}
	
	//�������Ŀ�ʼ����㣬ȷ����ȷ�ϻ��Ƿ��ز���ʱ�������Ĳ˵�����¿�ʼ
	SetLineSplitZero();
}

/**
 * @brief ��ʼ��OLED_UI�����õ�ǰҳ��Ľṹ��ָ�룬����ʼ��OLED��ʾ��
 * @param Page �˵�ҳ��ṹ��
 * @return ��
 */
void OLED_UI_Init(MenuPage* Page){
	//��ʼ��OLED��ʾ��
	OLED_Init();
	Key_Init();
	Encoder_Init();

	OLED_FPS.count = 0;
	OLED_FPS.value = 0;
	OLED_FPS.step = 0;

	OLED_UI_Key.Enter = 1;
	OLED_UI_Key.Back = 1;
	OLED_UI_Key.Up = 1;
	OLED_UI_Key.Down = 1;

	OLED_UI_LastKey = OLED_UI_Key;

	CurrentWindow = NULL;
	KeyEnterFlag = FLAGEND;
	FadeOutFlag = FLAGEND;
	WindowFlag = FLAGEND;
	ColorMode = DARKMODE;
	OLED_UI_ShowFps = true;
	OLED_UI_Brightness = 100;
	OLED_SustainCounter.count = 0;
	OLED_SustainCounter.SustainFlag = false;
	WindowProbDeltaData = 0;

	//���õ�ǰҳ��Ľṹ��ָ��
	CurrentMenuPage = Page;	//���õ�ǰҳ��Ľṹ��ָ��
	//��ʼ���˵�ҳ�����
	CurrentMenuPageInit();

	Timer_Init();
	
}



/**
 * @brief ��ȡenter�¼�״̬�������ж��Ƿ�����ִ�лص�����
 * @param void
 * @return ��
 */
bool GetEnterFlag(void){
	if(KeyEnterFlag == FLAGEND){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief ��ȡenter�¼�״̬�������ж��Ƿ�����ִ�лص�����
 * @param void
 * @return ��
 */
bool GetFadeoutFlag(void){
	if(FadeOutFlag == FLAGEND){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief �����ַ����Ŀ��ȣ���������Ӣ���ַ�����
 * @param String �ַ���ָ��
 * @param ChineseFont �����������
 * @param ASCIIFont ASCII�������
 * @return �ַ����Ŀ���
 */
int16_t CalcStringWidth(int16_t ChineseFont, int16_t ASCIIFont, const char *format, ...) {
    int16_t StringLength = 0;
    char String[MAX_STRING_LENGTH];

    va_list args;
    va_start(args, format);
    vsnprintf(String, sizeof(String), format, args); // ʹ��vsnprintf
    va_end(args);

    char *ptr = String;
    while (*ptr != '\0') {
        if ((unsigned char)*ptr & 0x80) { // ���������ַ�
            StringLength += ChineseFont;
            ptr += 2;
        } else {
            StringLength += ASCIIFont;
            ptr++;
        }
    }

    return StringLength;
}
/**
 * @brief ��ȡ�����������
 * @param window
 * @return ����ֵΪ���� WINDOW_DATA_STYLE_FLOAT ��int16_tֵΪ���� WINDOW_DATA_STYLE_INT ����ָ�뷵�� WINDOW_DATA_STYLE_NONE
 */
int8_t GetWindowProbDataStyle(MenuWindow* window){

	//����������ʷǷ��ڴ�
	if(window == NULL){
		return WINDOW_DATA_STYLE_NONE;
	}
	// ���������������Ϊint8_t
	if(window->Prob_Data_Int_8 != NULL){
		return WINDOW_DATA_STYLE_INT8;
		// ���������������Ϊint16_t
	}else if(window->Prob_Data_Int_16 != NULL){
		return WINDOW_DATA_STYLE_INT16;
		// ���������������Ϊint32_t
	}else if(window->Prob_Data_Int_32 != NULL){
		return WINDOW_DATA_STYLE_INT32;
		// ���������������Ϊint64_t
	}else if(window->Prob_Data_Int_64 != NULL){
		return WINDOW_DATA_STYLE_INT64;
		// ���������������Ϊfloat
	}else if(window->Prob_Data_Float != NULL){
		return WINDOW_DATA_STYLE_FLOAT;
	}else{
		return WINDOW_DATA_STYLE_NONE;
	}
}

/**
 * @brief ���ƴ���
 * @param ��
 * @return ��
 */
void OLED_DrawWindow(void){
	//������ڱ�־λû�б���λ���򲻽��д���Ч���������ڵ�Ŀ��λ����λ��Ļ�ⲿ
	if(OLED_SustainCounter.SustainFlag == false){
		OLED_UI_Window.TargetArea.Height = 30;
		OLED_UI_Window.TargetArea.Width = 60;
		OLED_UI_Window.TargetArea.X = (OLED_WIDTH - 60)/2;	
		OLED_UI_Window.TargetArea.Y = -40;
	}
	if(CurrentWindow == NULL){
		return;
	}
	OLED_Font ChineseFont = GetOLED_Font(CurrentWindow->Text_FontSize,CHINESE),ASCIIFont = GetOLED_Font(CurrentWindow->Text_FontSize,ASCII);

	

	//������ڶ�����û���˳���Ļ������ƴ���
	if(OLED_SustainCounter.SustainFlag == true || (OLED_UI_Window.CurrentArea.Height != 30 && OLED_UI_Window.CurrentArea.Width != 60 && OLED_UI_Window.CurrentArea.Y != -40)){
		//ͨ�����ж��Ƿ���Ҫ����Բ�Ǿ���
		if(CurrentWindow->General_WindowType == WINDOW_RECTANGLE){
			OLED_DrawRectangle(OLED_UI_Window.CurrentArea.X - 1,OLED_UI_Window.CurrentArea.Y - 1,OLED_UI_Window.CurrentArea.Width + 2,OLED_UI_Window.CurrentArea.Height + 2,OLED_UNFILLED);
			OLED_ClearArea(OLED_UI_Window.CurrentArea.X,OLED_UI_Window.CurrentArea.Y,OLED_UI_Window.CurrentArea.Width,OLED_UI_Window.CurrentArea.Height);
		}else{
			OLED_DrawRoundedRectangle(OLED_UI_Window.CurrentArea.X - 1,OLED_UI_Window.CurrentArea.Y - 1,OLED_UI_Window.CurrentArea.Width + 2,OLED_UI_Window.CurrentArea.Height + 2,2,OLED_UNFILLED);
			OLED_ClearArea(OLED_UI_Window.CurrentArea.X,OLED_UI_Window.CurrentArea.Y,OLED_UI_Window.CurrentArea.Width,OLED_UI_Window.CurrentArea.Height);
		}
		//��ʾ����
		/**
		 * ������ʾ������
		 * X����ǰ�����������ʼ��X + �˴������õ����������
		 * Y�� ��ǰ�����������ʼ��Y + ���嶥�����
		 * Width����ǰ���ڿ��ȼ�ȥ 2*���ֱ߾� ��ȥ ���ݵĿ��� ��ȥ���ݺ����ֵľ���WINDOW_DATA_TEXT_DISTANCE
		 * Height���ַ����߶�
		 * ��ʾ���ֵ���ʼ���ǣ�
		 * X�� ��ǰ�����������ʼ��X + �˴������õ����������
		 * Y�� ��ǰ�����������ʼ��Y + ���嶥�����
		 * Width���ַ�������
		 * Height���ַ����߶�
		 * */
        // �ȼ��㲻�������ݿ��ȵ��ַ���������ΪĬ�Ͽ���
		int16_t MaxLength  = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance;
		int16_t DataLength = 0;
		//������������
		int8_t DataStyle = GetWindowProbDataStyle(CurrentWindow);
		//������������ݲ�Ϊ�գ���˵���û������˽�����������ʾ������
		//�������ָ�벻Ϊ��
		if(DataStyle != WINDOW_DATA_STYLE_NONE ){
			//�����������Ϊ����
			if (DataStyle == WINDOW_DATA_STYLE_FLOAT)
			{
				//�����ַ��������Ƶ�������
				MaxLength = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance - CalcStringWidth(ChineseFont,	ASCIIFont,	"%.*f",FLOAT_POINT_LENGTH,*CurrentWindow->Prob_Data_Float) - WINDOW_DATA_TEXT_DISTANCE;
				//����������ռ�Ŀ���
				DataLength = CalcStringWidth(ChineseFont,ASCIIFont,"%.*f",FLOAT_POINT_LENGTH,*CurrentWindow->Prob_Data_Float);
				//��ʾ����
				OLED_PrintfMixArea(
					//��������
					OLED_UI_Window.CurrentArea.X,
					OLED_UI_Window.CurrentArea.Y,
					OLED_UI_Window.CurrentArea.Width,
					OLED_UI_Window.CurrentArea.Height,
					OLED_UI_Window.CurrentArea.X + CurrentWindow->General_Width - 1 - CurrentWindow->Text_FontSideDistance - DataLength,
					OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
					ChineseFont,ASCIIFont,
					"%.*f",FLOAT_POINT_LENGTH,*CurrentWindow->Prob_Data_Float);

			}else{
				
				

				switch (DataStyle) {
				    case WINDOW_DATA_STYLE_INT8:

						//�����ַ��������Ƶ�������
						MaxLength = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance - CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_8)- 		WINDOW_DATA_TEXT_DISTANCE;
						//����������ռ�Ŀ���
						DataLength = CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_8);
						//��ʾ����
						OLED_PrintfMixArea(
							//��������
							OLED_UI_Window.CurrentArea.X,
							OLED_UI_Window.CurrentArea.Y,
							OLED_UI_Window.CurrentArea.Width,
							OLED_UI_Window.CurrentArea.Height,
							OLED_UI_Window.CurrentArea.X + CurrentWindow->General_Width - 1 - CurrentWindow->Text_FontSideDistance - DataLength,
							OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
							ChineseFont,ASCIIFont,
							"%d",*CurrentWindow->Prob_Data_Int_8);

				        break;
				    case WINDOW_DATA_STYLE_INT16:
							//�����ַ��������Ƶ�������
							MaxLength = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance - CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_16)- 			WINDOW_DATA_TEXT_DISTANCE;
							//����������ռ�Ŀ���
							DataLength = CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_16);
							//��ʾ����
							OLED_PrintfMixArea(
								//��������
								OLED_UI_Window.CurrentArea.X,
								OLED_UI_Window.CurrentArea.Y,
								OLED_UI_Window.CurrentArea.Width,
								OLED_UI_Window.CurrentArea.Height,
								OLED_UI_Window.CurrentArea.X + CurrentWindow->General_Width - 1 - CurrentWindow->Text_FontSideDistance - DataLength,
								OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
								ChineseFont,ASCIIFont,
								"%d",*CurrentWindow->Prob_Data_Int_16);

				        break;
				    case WINDOW_DATA_STYLE_INT32:


							//�����ַ��������Ƶ�������
							MaxLength = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance - CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_32)- WINDOW_DATA_TEXT_DISTANCE;
							//����������ռ�Ŀ���
							DataLength = CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_32);
							//��ʾ����
							OLED_PrintfMixArea(
								//��������
								OLED_UI_Window.CurrentArea.X,
								OLED_UI_Window.CurrentArea.Y,
								OLED_UI_Window.CurrentArea.Width,
								OLED_UI_Window.CurrentArea.Height,
								OLED_UI_Window.CurrentArea.X + CurrentWindow->General_Width - 1 - CurrentWindow->Text_FontSideDistance - DataLength,
								OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
								ChineseFont,ASCIIFont,
								"%d",*CurrentWindow->Prob_Data_Int_32);

				        break;
				    case WINDOW_DATA_STYLE_INT64:

							//�����ַ��������Ƶ�������
							MaxLength = OLED_UI_Window.CurrentArea.Width - 2*CurrentWindow->Text_FontSideDistance - CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_64)- 			WINDOW_DATA_TEXT_DISTANCE;
							//����������ռ�Ŀ���
							DataLength = CalcStringWidth(ChineseFont,ASCIIFont,"%d",*CurrentWindow->Prob_Data_Int_64);
							//��ʾ����
							OLED_PrintfMixArea(
								//��������
								OLED_UI_Window.CurrentArea.X,
								OLED_UI_Window.CurrentArea.Y,
								OLED_UI_Window.CurrentArea.Width,
								OLED_UI_Window.CurrentArea.Height,
								OLED_UI_Window.CurrentArea.X + CurrentWindow->General_Width - 1 - CurrentWindow->Text_FontSideDistance - DataLength,
								OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
								ChineseFont,ASCIIFont,
								"%d",*CurrentWindow->Prob_Data_Int_64);

				        break;

				}

				
				
				
				
				
				
			}
			

			//��ʾ�����������
			OLED_DrawRoundedRectangle(OLED_UI_Window.CurrentArea.X +CurrentWindow->Prob_SideDistance,
			OLED_UI_Window.CurrentArea.Y + OLED_UI_Window.CurrentArea.Height  - CurrentWindow->Prob_LineHeight - CurrentWindow->Prob_BottomDistance,
			OLED_UI_Window.CurrentArea.Width- 2*CurrentWindow->Prob_SideDistance,CurrentWindow->Prob_LineHeight,2,OLED_UNFILLED);
			//��ʾ���������ڲ���
			OLED_DrawRectangle(OLED_UI_Window.CurrentArea.X +CurrentWindow->Prob_SideDistance + 2,
							OLED_UI_Window.CurrentArea.Y + OLED_UI_Window.CurrentArea.Height  - CurrentWindow->Prob_LineHeight - CurrentWindow->Prob_BottomDistance + 2,
							OLED_UI_ProbWidth.CurrentDistance>=OLED_UI_Window.CurrentArea.Width- 2*CurrentWindow->Prob_SideDistance - 4  ?OLED_UI_Window.CurrentArea.Width- 2*CurrentWindow->Prob_SideDistance - 4: OLED_UI_ProbWidth.CurrentDistance  ,CurrentWindow->Prob_LineHeight-4,OLED_FILLED);
		}
		if(CurrentWindow->Text_String != NULL){
			int16_t WindowTextStringLength = CalcStringWidth(ChineseFont,ASCIIFont,CurrentWindow->Text_String);
			//����ַ����Ŀ��ȳ���������޶�����
			if(WindowTextStringLength > MaxLength){
#if IF_WAIT_ANIMATION_FINISH
                if( OLED_UI_Window.CurrentArea.X == OLED_UI_Window.TargetArea.X &&
                        OLED_UI_Window.CurrentArea.Y == OLED_UI_Window.TargetArea.Y &&
                        OLED_UI_Window.CurrentArea.Width == OLED_UI_Window.TargetArea.Width &&
                        OLED_UI_Window.CurrentArea.Height == OLED_UI_Window.TargetArea.Height){
#endif
		    	CurrentWindow->_LineSlip-=LINE_SLIP_SPEED;
#if IF_WAIT_ANIMATION_FINISH
                }
#endif
		}
			if(CurrentWindow->_LineSlip < -WindowTextStringLength){
		   	 	CurrentWindow->_LineSlip =  MaxLength + 1;
			}

			OLED_PrintfMixArea(
			        OLED_UI_Window.CurrentArea.X + CurrentWindow->Text_FontSideDistance,
			        OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
			        MaxLength,
			        OLED_UI_Window.CurrentArea.Height,
					OLED_UI_Window.CurrentArea.X + CurrentWindow->Text_FontSideDistance + CurrentWindow->_LineSlip,
					OLED_UI_Window.CurrentArea.Y + CurrentWindow->Text_FontTopDistance,
					ChineseFont,ASCIIFont,CurrentWindow->Text_String);
			}

	}else{
		// ������ڶ����Ѿ��˳���Ļ���򽫵�ǰ����ָ��ָ��NULL
		OLED_UI_ProbWidth.CurrentDistance = 0;
		OLED_UI_ProbWidth.Derivative = 0;
		OLED_UI_ProbWidth.Error = 0;
		OLED_UI_ProbWidth.Integral = 0;
		OLED_UI_ProbWidth.LastError = 0;
		OLED_UI_ProbWidth.TargetDistance = 0;
		CurrentWindow = NULL;
	}
	
}







/**
 * @brief ���˵����������ƶ�һ��
 * @param ��
 * @return ��
 */
void MenuItemsMoveUp(void){
	OLED_UI_PageStartPoint.TargetPoint.Y -= (OLED_UI_LineStep.TargetDistance + CurrentMenuPage->General_FontSize);
}
/**
 * @brief ���˵����������ƶ�һ��
 * @param ��
 * @return ��
 */
void MenuItemsMoveDown(void){
	OLED_UI_PageStartPoint.TargetPoint.Y += (OLED_UI_LineStep.TargetDistance + CurrentMenuPage->General_FontSize);
}
/**
 * @brief ���˵����������ƶ�һ��
 * @param ��
 * @return ��
 */
void MenuItemsMoveLeft(void){
	OLED_UI_PageStartPoint.TargetPoint.X -= (OLED_UI_LineStep.TargetDistance + CurrentMenuPage->Tiles_TileWidth);
}
/**
 * @brief ���˵����������ƶ�һ��
 * @param ��
 * @return ��
 */
void MenuItemsMoveRight(void){
	OLED_UI_PageStartPoint.TargetPoint.X += (OLED_UI_LineStep.TargetDistance + CurrentMenuPage->Tiles_TileWidth);
}
/**
 * @brief ��ȡ��ǰ�˵�ҳ��Ĳ�λ����
 * @param ��
 * @return ��ǰ�˵�ҳ��Ĳ�λ����
 */
int16_t GetCurrentMenuPageMaxSlotNum(void){
	return (int16_t)(CurrentMenuPage->List_MenuArea.Height - CurrentMenuPage->List_StartPointY+OLED_UI_LineStep.TargetDistance-1) / (OLED_UI_LineStep.TargetDistance + CurrentMenuPage->General_FontSize );
}



/**
 * @brief ����Ŀ��������
 * @param ��
 * @return ��
 */
void SetTargetCursor(void){
	//�����ǰҳ�������ΪList��
	if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
		//Ŀ����x������� ��ʼ��ӡҳ����ʼ���x�����1����ȥ1��Ϊ��ȷ����긲�ǵ��˵�������֡�
		OLED_UI_Cursor.TargetArea.X = OLED_UI_PageStartPoint.TargetPoint.X -1;

		//Ŀ����y������� ��ʼ��ӡҳ����ʼ���y����  ����  (����߶� �� �о�)�� ��ǰҳ���ID�� ��1����ȥ1��Ϊ��ȷ����긲�ǵ��˵�������֡�
		OLED_UI_Cursor.TargetArea.Y = OLED_UI_PageStartPoint.TargetPoint.Y + 
		CurrentMenuPage->_ActiveMenuID * ( CurrentMenuPage->General_LineSpace + CurrentMenuPage->General_FontSize) -1 ;
		//Ŀ����߶ȵ��� ����߶� ��2����2��Ϊ��ȷ����긲�ǵ��˵�������֡�
		OLED_UI_Cursor.TargetArea.Height = CurrentMenuPage->General_FontSize + 2;
		//Ŀ������ȵ��� ��ǰ�ַ����Ŀ���	����2��Ϊ��ȷ����긲�ǵ��˵�������֡�
		//�������ǰ׺
		int8_t LinePerfixWidth = 0;
		if(CurrentMenuPage->List_IfDrawLinePerfix == true){
			LinePerfixWidth = GetOLED_Font(CurrentMenuPage->General_FontSize,ASCII) + LINEPERFIX_DISTANCE;
		}
		////��ѡ�����
		int8_t RadioCompensationWidth = 0;
		//�����Ҫ���Ƶ�ѡ��(��BoolRadioBox��Ϊ��)
		if(CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].List_BoolRadioBox != NULL){
			RadioCompensationWidth = (GetOLED_Font(CurrentMenuPage->General_FontSize,CHINESE) + 2);
		}else{
			RadioCompensationWidth = 0;
		}
		OLED_UI_Cursor.TargetArea.Width = 
		fmin((float)CalcStringWidth(
			//�ַ�������
			GetOLED_Font(CurrentMenuPage->General_FontSize,CHINESE),GetOLED_Font(CurrentMenuPage->General_FontSize,ASCII),CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_item_text) + 2 + LinePerfixWidth ,
			//��ǰҳ��Ŀ��ȼӵ�ǰҳ�����ʼ�����ȥ��ʼ��ӡҳ����ʼ��������ȥ6���ǹ��������ȼ�һ��������ǰ׺�Ŀ���
			OLED_UI_MenuFrame.CurrentArea.Width + OLED_UI_MenuFrame.CurrentArea.X - OLED_UI_PageStartPoint.CurrentPoint.X - 6 - LinePerfixWidth + LinePerfixWidth - RadioCompensationWidth) ;
	}
	//�����ǰҳ�������ΪTiles��
	if(CurrentMenuPage->General_MenuType == MENU_TYPE_TILES){
		//�����಻��Ҫ������ʾ����������Ϊ0.
		// SetCursorZero();
		OLED_UI_Cursor.TargetArea.X = CurrentMenuPage->Tiles_ScreenWidth/2 - CalcStringWidth(GetOLED_Font(CurrentMenuPage->General_FontSize,CHINESE),GetOLED_Font(CurrentMenuPage->General_FontSize,ASCII),CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_item_text)/2 - 1;
		OLED_UI_Cursor.TargetArea.Y = CurrentMenuPage->Tiles_ScreenHeight - CurrentMenuPage->General_FontSize - TILES_BOTTOM_DISTANCE - 1;
		OLED_UI_Cursor.TargetArea.Height = CurrentMenuPage->General_FontSize + 2;
		OLED_UI_Cursor.TargetArea.Width = CalcStringWidth(GetOLED_Font(CurrentMenuPage->General_FontSize,CHINESE),GetOLED_Font(CurrentMenuPage->General_FontSize,ASCII),CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_item_text) + 2;

	}
}
/**
 * @brief ����Ŀ��˵��߿�
 * @param ��
 * @return ��
 */
void SetTargetMenuFrame(void){
	OLED_UI_MenuFrame.TargetArea.X = CurrentMenuPage->List_MenuArea.X;
	OLED_UI_MenuFrame.TargetArea.Y = CurrentMenuPage->List_MenuArea.Y;
	OLED_UI_MenuFrame.TargetArea.Width = CurrentMenuPage->List_MenuArea.Width;
	OLED_UI_MenuFrame.TargetArea.Height = CurrentMenuPage->List_MenuArea.Height;

}
/**
 * @brief ����ǰҳ���LineSlip ����Ϊ0
 * @param ��
 * @return ��
 */
void SetLineSplitZero(void){
	MenuPage* page = CurrentMenuPage;
	for(MenuID i = 0; i<GetMenuItemNum(page->General_MenuItems);i++){
		page->General_MenuItems[i]._LineSlip = 0;
	}
}

/**
 * @brief ����Ŀ��������߶�
 * @param ��
 * @return ��
 */
void SetTargetScrollBarHeight(void){
	if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
		OLED_UI_ScrollBarHeight.TargetDistance = (float)CurrentMenuPage->List_MenuArea.Height*(CurrentMenuPage->_ActiveMenuID + 1)/GetMenuItemNum(CurrentMenuPage->General_MenuItems);
	}else if(CurrentMenuPage->General_MenuType == MENU_TYPE_TILES){
		OLED_UI_ScrollBarHeight.TargetDistance = (float)(CurrentMenuPage->Tiles_ScreenWidth *(CurrentMenuPage->_ActiveMenuID + 1)/GetMenuItemNum(CurrentMenuPage->General_MenuItems));
	}
}
/**
 * @brief ����Ŀ�����������
 * @param ��
 * @return ��
 */
void SetTargetProbWidth(void){
	// if(CurrentWindow == NULL)
	// {
	// 	return;
	// }
	//ȷ����������
	MenuWindow* window = CurrentWindow;
	int8_t DataStyle = GetWindowProbDataStyle(window);
	
	if(DataStyle != WINDOW_DATA_STYLE_NONE){
		if(DataStyle == WINDOW_DATA_STYLE_FLOAT){
			OLED_UI_ProbWidth.TargetDistance = ((*window->Prob_Data_Float - window->Prob_MinData)/((float)window->Prob_MaxData - window->Prob_MinData ))*	(OLED_UI_Window.CurrentArea.Width- 2*window->Prob_SideDistance - 4);
		}else{

			switch (DataStyle) {
				case WINDOW_DATA_STYLE_INT8:
				
					OLED_UI_ProbWidth.TargetDistance = ((*CurrentWindow->Prob_Data_Int_8 - window->Prob_MinData)/((float)window->Prob_MaxData - window->Prob_MinData ))*	(OLED_UI_Window.CurrentArea.Width- 2*window->Prob_SideDistance - 4);
					break;
				case WINDOW_DATA_STYLE_INT16:
				
					OLED_UI_ProbWidth.TargetDistance = ((*CurrentWindow->Prob_Data_Int_16 - window->Prob_MinData)/((float)window->Prob_MaxData - window->Prob_MinData ))*	(OLED_UI_Window.CurrentArea.Width- 2*window->Prob_SideDistance - 4);
					break;
				case WINDOW_DATA_STYLE_INT32:
				
					OLED_UI_ProbWidth.TargetDistance = ((*CurrentWindow->Prob_Data_Int_32 - window->Prob_MinData)/((float)window->Prob_MaxData - window->Prob_MinData ))*	(OLED_UI_Window.CurrentArea.Width- 2*window->Prob_SideDistance - 4);
					break;
				case WINDOW_DATA_STYLE_INT64:
				
					OLED_UI_ProbWidth.TargetDistance = ((*CurrentWindow->Prob_Data_Int_64 - window->Prob_MinData)/((float)window->Prob_MaxData - window->Prob_MinData ))*	(OLED_UI_Window.CurrentArea.Width- 2*window->Prob_SideDistance - 4);
					break;

					
			}


			
		}
	}else{
		return;
	}
	
}

/**
 * @brief ���ݵ�ǰҳ����������Ƿ������ǰ׺
 * @param page �˵�ҳ��ṹ��ָ��
 * @param id �˵���ID��
 * @param CursorPoint ��������
 * @return ��
 */
void DrawLinePermix(MenuPage* page,MenuID i,OLED_Point* CursorPoint,OLED_Font ChineseFont,OLED_Font ASCIIFont){
	//�����Ҫ��ӡ��ǰ׺
	if(page->List_IfDrawLinePerfix == true){
		char* LinePerfixSymb = "";
		//�����ǰ�Ĳ˵������Ӳ˵���û�лص���������ô��ӡ��Ӧ�ķ���
		if(CurrentMenuPage->General_MenuItems[i].General_SubMenuPage != NULL && page->General_MenuItems[i].General_callback == NULL && page->General_MenuItems[i].List_BoolRadioBox == NULL){
			LinePerfixSymb = SUBMENU_PREFIX;
		}else//����лص�����
		if(CurrentMenuPage->General_MenuItems[i].General_SubMenuPage == NULL && page->General_MenuItems[i].General_callback != NULL && page->General_MenuItems[i].List_BoolRadioBox == NULL){
			LinePerfixSymb = FUNCTION_PREFIX;
		}else
		if(CurrentMenuPage->General_MenuItems[i].General_SubMenuPage == NULL && page->General_MenuItems[i].General_callback == NULL && page->General_MenuItems[i].List_BoolRadioBox != NULL)
		{
			LinePerfixSymb = RADIO_PREFIX;
		}else{
			LinePerfixSymb = NONE_PREFIX;
		}

		OLED_PrintfMixArea(//�����Ƶ������ڴ�ӡ����
					   //������ʼx����
				       OLED_UI_MenuFrame.CurrentArea.X ,
					   OLED_UI_MenuFrame.CurrentArea.Y,
					   OLED_UI_MenuFrame.CurrentArea.Width - 6,
					   OLED_UI_MenuFrame.CurrentArea.Height,
					   //��ӡ���ֵ�����
					   CursorPoint->X,
					   CursorPoint->Y,
					   //��ӡ���ֵĴ�С
					   ChineseFont,ASCIIFont,
					   //��ӡ���ֵ�����
					   LinePerfixSymb);
		
	}

}


/**
 * @brief ���ݴ���Ľṹ������ָ���ӡ�˵�Ԫ��
 * @param ��
 * @return ��
 */
void PrintMenuElements(void){
	//���ȿӡ�����ǰҳ��Ľṹ��ָ��ȡ�����������������������forѭ�����иı�ṹ��ָ�룬��ᵼ��forѭ�����������ʵ�NULLָ�룬����Ӳ��������ɿ���
	MenuPage* page = CurrentMenuPage;
	OLED_ChangePoint TempTargetPoint = OLED_UI_PageStartPoint;
	OLED_ChangeArea TempTargetArea = OLED_UI_MenuFrame;
	
	//��ȡ��ǰҳ��Ĳ˵�������
	MenuID num = GetMenuItemNum(page->General_MenuItems);
	//��ȡ�ı���С���ӵ�ǰҳ���������������ASCII��������������������
	OLED_Font ChineseFont = GetOLED_Font(page->General_FontSize,CHINESE),ASCIIFont = GetOLED_Font(page->General_FontSize,ASCII);
	//���������������,��ʼ��Ϊ��ǰ�˵��ṹ��Ŀ�ʼ��
	OLED_Point CursorPoint = TempTargetPoint.CurrentPoint;
	//����ҳ���Ƿ��Ѿ���ʼ���ˣ����û�У����ʼ��
   
	//�����ǰҳ�������Ϊ�б���
	if(page->General_MenuType == MENU_TYPE_LIST){
		//��ǰ׺����
		int16_t LinePerfixWidth = 0;
		////��ѡ�����
		int16_t RadioCompensationWidth = 0;

		//���Ʊ߿������һ���ȼӶ���Ϊ��ʹ����򲻻ᵲס�˵���������ʵ����������ڲ˵�����
		if(page->List_IfDrawFrame == true){
			OLED_DrawRectangle(TempTargetArea.CurrentArea.X-1,TempTargetArea.CurrentArea.Y-1,	TempTargetArea.CurrentArea.Width+2,TempTargetArea.CurrentArea.Height+2,OLED_UNFILLED);
		}
		//�����Ҫ������ǰ׺
		if(page->List_IfDrawLinePerfix == true){
			//����ǰ׺��������ΪASCII������ȼ�LINEPERFIX_DISTANCE������ַ����ľ��룩
			LinePerfixWidth = ASCIIFont + LINEPERFIX_DISTANCE;
		}


		//��ӡ�˵���
		for(MenuID i = 0; i<num;i++){
			
			if(CursorPoint.Y + ChineseFont <0 || CursorPoint.Y > OLED_HEIGHT){
				CursorPoint.Y += (page->General_FontSize + OLED_UI_LineStep.CurrentDistance);
				continue;
			}

			//��¼����ѭ�����ַ�������
			int16_t StringLength = CalcStringWidth(ChineseFont,ASCIIFont,page->General_MenuItems[i].General_item_text);

			//�������������ǰ׺
			DrawLinePermix(page,i,&CursorPoint,ChineseFont,ASCIIFont);

			//�����Ҫ���Ƶ�ѡ��(��BoolRadioBox��Ϊ��)
			if(page->General_MenuItems[i].List_BoolRadioBox != NULL){
				RadioCompensationWidth = (ChineseFont + 2);
				char* RadioBoxSymb = "";
				if(*page->General_MenuItems[i].List_BoolRadioBox == true){
					RadioBoxSymb = "ON";
				}else{
					RadioBoxSymb = "OFF";
				}


				OLED_PrintfMixArea(//�����Ƶ������ڴ�ӡ����
							   //������ʼx���������ǰ׺���ȣ����������Զ�������ӡ��ǰ׺�Ŀռ�
						       TempTargetArea.CurrentArea.X ,
							   TempTargetArea.CurrentArea.Y,
							   TempTargetArea.CurrentArea.Width - 6,
							   TempTargetArea.CurrentArea.Height,

							   //��ӡ���ֵ�����
							   (int16_t)(TempTargetArea.CurrentArea.X + TempTargetArea.CurrentArea.Width - 6 - 2 - CalcStringWidth(ChineseFont, ASCIIFont, RadioBoxSymb)),
							   CursorPoint.Y,
							   //��ӡ���ֵĴ�С
							   ChineseFont,ASCIIFont,
							   //��ӡ���ֵ�����
							   RadioBoxSymb);
			}else{
				RadioCompensationWidth = 0;
			}

			//����ַ����Ŀ��ȳ���������޶�����
			if(StringLength > (TempTargetArea.TargetArea.X + TempTargetArea.TargetArea.Width - 6 - 2) - TempTargetPoint.TargetPoint.X - LinePerfixWidth - RadioCompensationWidth ){
#if IF_WAIT_ANIMATION_FINISH
			    if(TempTargetArea.TargetArea.Width == TempTargetArea.CurrentArea.Width &&
					TempTargetArea.TargetArea.X == TempTargetArea.CurrentArea.X &&
					TempTargetArea.TargetArea.Height == TempTargetArea.CurrentArea.Height &&
					TempTargetArea.TargetArea.Y == TempTargetArea.CurrentArea.Y){
#endif
						page->General_MenuItems[i]._LineSlip -= LINE_SLIP_SPEED;
#if IF_WAIT_ANIMATION_FINISH
					}
#endif
				
				
				//���page->MenuItems[i]._LineSlipС�ڸ����ַ������ȣ�˵���ַ����Ѿ����Ƶ�������
				if(page->General_MenuItems[i]._LineSlip < -StringLength){
					//��λ����������޶����ȵ��Ҳ�ոպÿ������ĵط�
					page->General_MenuItems[i]._LineSlip = (TempTargetArea.TargetArea.X + TempTargetArea.TargetArea.Width - 6) - CursorPoint.X - LinePerfixWidth;
				}


			}

			OLED_PrintfMixArea(TempTargetArea.CurrentArea.X + LinePerfixWidth + CurrentMenuPage->List_StartPointX ,
			 					TempTargetArea.CurrentArea.Y,
			 					TempTargetArea.CurrentArea.Width - 6 - LinePerfixWidth - CurrentMenuPage->List_StartPointX  -2 - RadioCompensationWidth,
			 					TempTargetArea.CurrentArea.Height,
								//�������LinePerfixWidth��Ϊ�˸���ǰ׺���¿ռ�
							   	CursorPoint.X + LinePerfixWidth + page->General_MenuItems[i]._LineSlip,
							   	CursorPoint.Y,
							   	ChineseFont,ASCIIFont,page->General_MenuItems[i].General_item_text);

			// ��ӡ�������
			CursorPoint.Y += (page->General_FontSize + OLED_UI_LineStep.CurrentDistance);

		}

		//���ƹ���������������
		OLED_DrawRectangle(TempTargetArea.CurrentArea.X + TempTargetArea.CurrentArea.Width - 5,TempTargetArea.CurrentArea.Y,5,(OLED_UI_ScrollBarHeight.CurrentDistance > page->List_MenuArea.Height) ?page->List_MenuArea.Height:OLED_UI_ScrollBarHeight.CurrentDistance,OLED_FILLED);
		OLED_DrawLine(TempTargetArea.CurrentArea.X + TempTargetArea.CurrentArea.Width - 3,TempTargetArea.CurrentArea.Y,TempTargetArea.CurrentArea.X + TempTargetArea.CurrentArea.Width-3,TempTargetArea.CurrentArea.Height + TempTargetArea.CurrentArea.Y-1);
	}
#if OLED_UI_ENABLE_TILES
	//�����ǰ��ҳ��Ϊ��������
	if(page->General_MenuType == MENU_TYPE_TILES){
		//��ӡ������
		for(MenuID i = 0; i<num;i++){
			if(CursorPoint.X + page->Tiles_TileWidth < 0 || CursorPoint.X > OLED_WIDTH){
				CursorPoint.X += (page->Tiles_TileWidth + OLED_UI_LineStep.CurrentDistance);
				continue;
			}

			//��ʾ����ͼ��
			OLED_ShowImageArea(ceil(CursorPoint.X),CursorPoint.Y,page->Tiles_TileWidth,page->Tiles_TileHeight,0,0,page->Tiles_ScreenWidth,page->Tiles_ScreenHeight,page->General_MenuItems[i].Tiles_Icon == NULL?UnKnown:page->General_MenuItems[i].Tiles_Icon);
			// ��ӡ�������
			CursorPoint.X += (page->Tiles_TileWidth + OLED_UI_LineStep.CurrentDistance);
			//��ʾ�˵�������
			
		}
		if(IF_DRAW_ARROR == true){
			//����ָʾ��ͷ
			OLED_ShowImageArea(page->Tiles_ScreenWidth/2 - 3,0,6,5,0,0,page->Tiles_ScreenWidth,page->Tiles_ScreenHeight,Arrow);
		}
		//��¼����ѭ�����ַ�������
		int16_t StringLength = CalcStringWidth(ChineseFont,ASCIIFont,page->General_MenuItems[page->_ActiveMenuID].General_item_text);
		//����ַ����Ŀ��ȴ����û������õ���Ļ����
		if(StringLength > page->Tiles_ScreenWidth){
#if IF_WAIT_ANIMATION_FINISH
		    if(OLED_UI_PageStartPoint.CurrentPoint.X == OLED_UI_PageStartPoint.TargetPoint.X &&
		        OLED_UI_PageStartPoint.CurrentPoint.Y == OLED_UI_PageStartPoint.TargetPoint.Y ){
#endif
		        page->General_MenuItems[page->_ActiveMenuID]._LineSlip -= LINE_SLIP_SPEED;
#if IF_WAIT_ANIMATION_FINISH
		    }
#endif
		}else{
		    SetLineSplitZero();
		}
		//���page->MenuItems[i]._LineSlipС�ڸ����ַ������ȣ�˵���ַ����Ѿ����Ƶ�������
		if(page->General_MenuItems[page->_ActiveMenuID]._LineSlip < -StringLength){
		     //��λ����������޶����ȵ��Ҳ�ոպÿ������ĵط�
		     page->General_MenuItems[page->_ActiveMenuID]._LineSlip = page->Tiles_ScreenWidth + 1;
		}

		OLED_PrintfMixArea(0,0,page->Tiles_ScreenWidth,page->Tiles_ScreenHeight,
		        StringLength > page->Tiles_ScreenWidth? 0 + page->General_MenuItems[page->_ActiveMenuID]._LineSlip : page->Tiles_ScreenWidth/2 - CalcStringWidth(ChineseFont,ASCIIFont,page->General_MenuItems[page->_ActiveMenuID].General_item_text)/2 + page->General_MenuItems[page->_ActiveMenuID]._LineSlip,
							   page->Tiles_ScreenHeight - page->General_FontSize - TILES_BOTTOM_DISTANCE,
							   ChineseFont,ASCIIFont,
							   page->General_MenuItems[page->_ActiveMenuID].General_item_text);
		//���ƹ���������������
		int16_t ScrollBarHeight = (page->Tiles_ScreenHeight >= 128? 5:3);
		OLED_DrawRectangle(0,TILES_STARTPOINT_Y + page->Tiles_TileHeight + TILES_SCROLLBAR_Y,
						OLED_UI_ScrollBarHeight.CurrentDistance,ScrollBarHeight,OLED_FILLED);
		OLED_DrawLine(0,TILES_STARTPOINT_Y + page->Tiles_TileHeight + TILES_SCROLLBAR_Y + ScrollBarHeight/2,page->Tiles_ScreenWidth-1,TILES_STARTPOINT_Y + page->Tiles_TileHeight + TILES_SCROLLBAR_Y + ScrollBarHeight/2);

		
		
	}
#endif
	if(page->General_ShowAuxiliaryFunction != NULL){
		//���Ƹ�������
		page->General_ShowAuxiliaryFunction();
	}
	
}



/**
 * @brief �������������¼����
 * @param ��
 * @return ��һ������һ�ֵ�_ActiveMenuID��ֵ
 * @note ʵ����_ActiveMenuID��ֵ���䡣
  */
MenuID_Type OLED_KeyAndEncoderRecord(void){
    static bool IfUpTapAndHold = false;
    static bool IfDownTapAndHold = false;
	//��¼��һ�ְ���״̬
    OLED_UI_LastKey.Up=OLED_UI_Key.Up;
	OLED_UI_LastKey.Down=OLED_UI_Key.Down;
	OLED_UI_LastKey.Enter=OLED_UI_Key.Enter;
	OLED_UI_LastKey.Back=OLED_UI_Key.Back;
    
    //��¼��ǰ����״̬
	OLED_UI_Key.Enter = Key_GetEnterStatus();
	OLED_UI_Key.Back = Key_GetBackStatus();
	OLED_UI_Key.Up = Key_GetUpStatus();
	OLED_UI_Key.Down = Key_GetDownStatus();
#if IF_START_UP_AND_DOWN_LONG_PRESS

	static int16_t UpPressCounter = 0;
	static int16_t UpPressedCounter  = 0;
	static int16_t DownPressCounter = 0;
	static int16_t DownPressedCounter = 0;
	//�����һ�κ���һ�ζ����µ�״̬����
	if(OLED_UI_LastKey.Up == 0 && OLED_UI_Key.Up == 0){
	    UpPressCounter++;
	    if(UpPressCounter >= (float)PRESS_TIME * 50){
	        UpPressedCounter ++;
	        if(UpPressedCounter >= (UpPressCounter >= (PRESS_TIME + CONTINUE_PRESS_TIME) * 50? CONTINUE_PRESS_MOVE_SPEED : PRESS_MOVE_SPEED)){
	            IfUpTapAndHold = true;
	            UpPressedCounter = 0;
	            IfUpTapAndHold = true;
	        }else{
	            IfUpTapAndHold = false;
	        }
	    }

	}else{
	    UpPressCounter = 0;
	    UpPressedCounter = 0;
	    IfUpTapAndHold = false;
	}
	//�����һ�κ���һ�ζ����µ�״̬����
	    if(OLED_UI_LastKey.Down == 0 && OLED_UI_Key.Down == 0){
	        DownPressCounter++;

	        if(DownPressCounter >= (float)PRESS_TIME * 50){
	            DownPressedCounter ++;
	            if(DownPressedCounter >= (DownPressCounter >= (PRESS_TIME + CONTINUE_PRESS_TIME) * 50? CONTINUE_PRESS_MOVE_SPEED : PRESS_MOVE_SPEED)){
	                IfDownTapAndHold = true;
	                DownPressedCounter = 0;
	                IfDownTapAndHold = true;
	            }else{
	                IfDownTapAndHold = false;
	            }
	        }

	    }else{
	        DownPressCounter = 0;
	        DownPressedCounter = 0;
	        IfDownTapAndHold = false;
	    }

#endif
	if(OLED_UI_Key.Up == OLED_UI_Key.Down){
	    IfUpTapAndHold = false;
	    IfDownTapAndHold = false;

	}

	//��ȡ��ǰҳ��Ĳ˵�������
	int16_t MaxID = GetMenuItemNum(CurrentMenuPage->General_MenuItems);
	MenuID_Type IncreaseID = {0,0};
	int16_t ActiveMenuID = CurrentMenuPage->_ActiveMenuID;
	int16_t LastActiveID = ActiveMenuID;
	//��ȡ������״̬
	ActiveMenuID += Encoder_Get();

	//�����⵽���ϡ���������һ״̬����ε�״̬��ͬ������һ״̬��̧��״̬��˵���û������ˡ��ϡ����������Ҹող�̧��
	if((OLED_UI_Key.Up != OLED_UI_LastKey.Up && OLED_UI_Key.Up == 1) || IfUpTapAndHold){
		ActiveMenuID--;
	}

	//�����⵽���¡���������һ״̬����ε�״̬��ͬ������һ״̬��̧��״̬��˵���û������ˡ��¡����������Ҹող�̧��
	if((OLED_UI_Key.Down != OLED_UI_LastKey.Down && OLED_UI_Key.Down == 1) || IfDownTapAndHold){
		ActiveMenuID++;
	}
	
	IncreaseID.Unsafe = ActiveMenuID - LastActiveID;
	//�����ǰ�˵���ID��Խ�磬����������0~MaxID-1֮��
	if(ActiveMenuID >= MaxID-1){
		ActiveMenuID = MaxID-1;
	}
	if(ActiveMenuID <= 0){
		ActiveMenuID = 0;
	}

	IncreaseID.Safe = ActiveMenuID - LastActiveID;
	return IncreaseID;
}
/**
 * @brief ��KeyEnterFlag��FLAGSTART�����ڱ�ǻص���������ִ��
 * @param ��
 * @return ��
 */
void SetEnterFlag(void){
	KeyEnterFlag = FLAGSTART;
	Encoder_Disable();  // ʧ�ܱ�����
}

/**
 * @brief ��KeyEnterFlag��FLAGEND�����ڱ�ʾ�ص�����û������ִ��
 * @param void
 * @return ��
 */
void ResetEnterFlag(void){
	KeyEnterFlag = FLAGEND;
}


/**
 * @brief ��FadeOutFlag��FLAGSTART�����ڱ�ǽ���Ч������ִ��
 * @param ��
 * @return ��
 */
void SetFadeOutFlag(MutexFlag action){
	FadeOutFlag = action;
	Encoder_Disable();  // ʧ�ܱ�����
}

/**
 * @brief ��FadeOutFlag��FLAGEND�����ڱ�ʾ����Ч��û������ִ��
 * @param void
 * @return ��
 */
void ResetFadeOutFlag(void){
	FadeOutFlag = FLAGEND;
}

/**
 * @brief �˺�����������Enter��������������Ϊ���¼��������
 * 		1. ��ǰ�˵����лص���������ô�ͽ�KeyEnterFlag��λ��
 * 		2. ��ǰ�˵���û�лص��������������Ӳ˵�����ô�ͽ����Ӳ˵�
 * 		3. ��ǰ�˵���û�лص�������Ҳû���Ӳ˵�����ô��ʲô������
 * 		4. ��ǰ�˵�����лص������������Ӳ˵�����ô��ʲôҲ����
 * @param ��
 * @return ��
 */
void EnterEventMenuItem(void){
    //�����ǰѡ�в˵����лص���������û���Ӳ˵�����ô�ͽ�KeyEnterFlag��λ
    if(CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_callback != NULL && CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_SubMenuPage == NULL){

        SetEnterFlag();
    }
	//�����ǰѡ�в˵���û�лص��������������Ӳ˵�����ô��ȷ�ϱ�־λ
    if(CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_SubMenuPage != NULL 
	&& CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_callback == NULL){
		SetFadeOutFlag(ENTER_FLAGSTART);
    }

}
/**
 * @brief ���¡����ء�������Ĳ���
 * @param ��
 * @return ��
 */
void BackEventMenuItem(void){
	//�����ǰ�˵��ĸ��˵���Ϊ��
	if(CurrentMenuPage->General_ParentMenuPage != NULL){
		//�÷��ر���λ
        SetFadeOutFlag(BACK_FLAGSTART);
    }
	
}
/**
 * @brief ���غ���
 * @param ��
 * @note ģ�ⰴ�¡����ء�����
 * @return ��
 */
void OLED_UI_Back(void){
	BackEventMenuItem();
}

/**
 * @brief ���벢���лص�����
 * @param void
 * @return ��
 */
void RunCurrentCallBackFunction(void){
	//KeyEnterFlag == FLAGSTART���������ʾenter������
	if(KeyEnterFlag == FLAGSTART){
		CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_callback();	
		//�ڻص�����ִ�����֮�󣬽�KeyEnterFlag��λ��
		ResetEnterFlag();
		Encoder_Enable();  // ʹ�ܱ�����
	}
}
/**
 * @brief ����ǰ���������Ŀ������������Ϊ0
 * @param ��
 * @return ��
 */
void SetCursorZero(void){
	OLED_UI_Cursor.TargetArea.X = 0;
	OLED_UI_Cursor.TargetArea.Y = 0;
	OLED_UI_Cursor.TargetArea.Width = 0;
	OLED_UI_Cursor.TargetArea.Height = 0;
	OLED_UI_Cursor.CurrentArea.X = 0;
	OLED_UI_Cursor.CurrentArea.Y = 0;
	OLED_UI_Cursor.CurrentArea.Width = 0;
	OLED_UI_Cursor.CurrentArea.Height = 0;
}
/**
 * @brief ���ô��ڴ�С
 * @param Width ���ڿ���
 * @param Height ���ڸ߶�
 * @return ��
 */
void OLED_UI_CreateWindow(MenuWindow* window){
	//�����ǰ���ڻ�û�н����û������´������ڣ������ý��������ȣ����ֶ���������
	if(CurrentWindow == NULL){
		//����ǰ��������������
		OLED_UI_ProbWidth.CurrentDistance = 0;
		window->_LineSlip = 0;
	}
	//�����ڱ�־λ����Ϊtrue����ʾ��ʼ����Ч��
	OLED_SustainCounter.SustainFlag = true;
	
	//���ô���Ч��ʱ�������
	OLED_SustainCounter.count = 0;
	//������ڱ�־λ����λ��������Ŀ�괰�ڵ�λ�õ���Ļ����
	
	//����Ŀ�괰�ڵ�λ��Ϊ��Ļ���������ʾ
	OLED_UI_Window.TargetArea.Width = window->General_Width;
	OLED_UI_Window.TargetArea.Height = window->General_Height;
	OLED_UI_Window.TargetArea.X = (OLED_WIDTH - window->General_Width)/2;
	OLED_UI_Window.TargetArea.Y = (OLED_HEIGHT - window->General_Height)/2;
	
	//����ǰ����ָ��ָ��window
	CurrentWindow = window;
	
}




/**
 * @brief ���н���Ч��
 * @param ��
 * @return ��
 */
void RunFadeOut(void){
	/*�����ǰ��FadeOutFlag�Ѿ�����λ����˵���������н���Ч����
	��ǰ�����н���Ч����ǰ��������2����
	1.���ڰ���ȷ�ϼ�������¡��������ǰѡ�в˵���û�лص��������������Ӳ˵�������ʱ FadeOutFlag == ENTER_FLAGSTART
	2.���ڰ��·��ؼ�������¡��������ǰ�˵��ĸ��˵���Ϊ�ա�����ʱ FadeOutFlag == BACK_FLAGSTART
	*/
	if(FadeOutFlag != FLAGEND){
		
		//�����ǰ�˵����б���
		if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
			//��ǰ�˵����ҳ���������б��������£�������ȷ�ϰ���
			if(FadeOutFlag == ENTER_FLAGSTART){
				// ����ȷ�ϲ���֮�󣬵�ǰҳ��ű�ȷ��Ϊ�Ѿ���ʼ��
				CurrentMenuPage->_IfInit = true;
				//�������Ӳ˵�������£������ǰҳ��ĵ�ǰ�Ӳ˵����ҳ���������б���
				if(CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_SubMenuPage->General_MenuType == MENU_TYPE_LIST){
					//ֻ�����ǰҳ������
					OLED_UI_FadeoutCurrentArea(CurrentMenuPage->List_MenuArea.X,CurrentMenuPage->List_MenuArea.Y,CurrentMenuPage->List_MenuArea.Width-5,CurrentMenuPage->List_MenuArea.Height-2);
				}else{
					//���ȫ������
					OLED_UI_FadeoutAllArea();
					//���������ĵ�ǰ�߶���Ϊ0
					OLED_UI_ScrollBarHeight.CurrentDistance = 0;
				}

				//����ǰ�˵���λ�ñ��棬�Ա㷵��ʱ�ָ�
				CurrentMenuPage->_StartPoint.X = OLED_UI_PageStartPoint.TargetPoint.X;
				CurrentMenuPage->_StartPoint.Y = OLED_UI_PageStartPoint.TargetPoint.Y;

				//����ǰ�˵���ָ��ָ���Ӳ˵�
				CurrentMenuPage = CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_SubMenuPage;
				//�Ե�ǰ�Ӳ˵����г�ʼ��
				CurrentMenuPageInit();
			}
			//��ǰ�˵����ҳ���������б��������£�������ȡ������
			if(FadeOutFlag == BACK_FLAGSTART) {
				//�����ǰҳ��ĸ��˵����ҳ���������б���
				if(CurrentMenuPage->General_ParentMenuPage->General_MenuType == MENU_TYPE_LIST){
					//ֻ�����ǰҳ������
					OLED_UI_FadeoutCurrentArea(CurrentMenuPage->List_MenuArea.X,CurrentMenuPage->List_MenuArea.Y,CurrentMenuPage->List_MenuArea.Width-5,CurrentMenuPage->List_MenuArea.Height-2);
				}else{
					//���ȫ������
					OLED_UI_FadeoutAllArea();
					//���������ĵ�ǰ�߶���Ϊ0
					OLED_UI_ScrollBarHeight.CurrentDistance = 0;
				}
				//����ǰ�˵���ָ��ָ�򸸲˵�
				CurrentMenuPage = CurrentMenuPage->General_ParentMenuPage;
				//����ǰ�˵���λ�õȲ����ָ�
				if(CurrentMenuPage->_IfInit == false){
		
					CurrentMenuPageInit();
				}else{
					//����ǰ�˵���λ�õȲ����ָ�
					CurrentMenuPageBackUp();
				}
			}
			
			//��FadeOutFlag��λ
			ResetFadeOutFlag();
			//����ǰ���������Ŀ������������Ϊ0
			SetCursorZero();

		}else //�����ǰ�˵������Ǵ�����
		if(CurrentMenuPage->General_MenuType == MENU_TYPE_TILES){
			//���ȫ������
			OLED_UI_FadeoutAllArea();
			//��ǰ�˵����ҳ�������Ǵ����������£�������ȷ�ϲ���
			if(FadeOutFlag == ENTER_FLAGSTART){
				// ����ȷ�ϲ���֮�󣬵�ǰҳ��ű�ȷ��Ϊ�Ѿ���ʼ��
				CurrentMenuPage->_IfInit = true;
				//����ǰ�˵���λ�ñ��棬�Ա㷵��ʱ�ָ�
				CurrentMenuPage->_StartPoint.X = OLED_UI_PageStartPoint.TargetPoint.X;
				CurrentMenuPage->_StartPoint.Y = OLED_UI_PageStartPoint.TargetPoint.Y;
				//����ǰ�˵���ָ��ָ���Ӳ˵�
				CurrentMenuPage = CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].General_SubMenuPage;
				//�Ե�ǰ�Ӳ˵����г�ʼ��
				CurrentMenuPageInit();
				
			}
			//��ǰ�˵����ҳ�������Ǵ����������£������˷��ز���
			if(FadeOutFlag == BACK_FLAGSTART){
				//����ǰ�˵���ָ��ָ�򸸲˵�
				CurrentMenuPage = CurrentMenuPage->General_ParentMenuPage;
				if(CurrentMenuPage->_IfInit == false){
		
					CurrentMenuPageInit();
				}else{
					//����ǰ�˵���λ�õȲ����ָ�
					CurrentMenuPageBackUp();
				}
				
			}
			//���������ĵ�ǰ�߶���Ϊ0
			OLED_UI_ScrollBarHeight.CurrentDistance = 0;
			//����ǰ���������Ŀ������������Ϊ0
			SetCursorZero();
			//��FadeOutFlag��λ
			ResetFadeOutFlag();
		}
		// ʹ�ܱ�����
		Encoder_Enable();
		
	}
}

/**
 * @brief �����ڲ����ݴ���
 * @param ��
 * @return ��
 */
void OLED_WindowDataDispose(){
	
	if(CurrentWindow != NULL){
		if(OLED_SustainCounter.count >= (int16_t)(CurrentWindow->General_ContinueTime * 50)){
			OLED_SustainCounter.SustainFlag = false;
			OLED_SustainCounter.count = 0;
		}
		
	}
	
	int8_t DataStyle = GetWindowProbDataStyle(CurrentWindow);
	//�������������
	if(DataStyle != WINDOW_DATA_STYLE_NONE){

		//�����������������
		if(DataStyle == WINDOW_DATA_STYLE_FLOAT){
			//�����С��
			*CurrentWindow->Prob_Data_Float += (WindowProbDeltaData * CurrentWindow->Prob_DataStep);
			if(*CurrentWindow->Prob_Data_Float <= CurrentWindow->Prob_MinData) {*CurrentWindow->Prob_Data_Float = CurrentWindow->Prob_MinData;}
			if(*CurrentWindow->Prob_Data_Float >= CurrentWindow->Prob_MaxData) {*CurrentWindow->Prob_Data_Float = CurrentWindow->Prob_MaxData;}
		}else{
			

			switch (DataStyle) {
				case WINDOW_DATA_STYLE_INT8:
					*CurrentWindow->Prob_Data_Int_8 += (WindowProbDeltaData * CurrentWindow->Prob_DataStep);
					if(*CurrentWindow->Prob_Data_Int_8 <= CurrentWindow->Prob_MinData) {*CurrentWindow->Prob_Data_Int_8 = CurrentWindow->Prob_MinData;}
					if(*CurrentWindow->Prob_Data_Int_8 >= CurrentWindow->Prob_MaxData) {*CurrentWindow->Prob_Data_Int_8 = CurrentWindow->Prob_MaxData;}
					break;
				case WINDOW_DATA_STYLE_INT16:
					
					*CurrentWindow->Prob_Data_Int_16 += (WindowProbDeltaData * CurrentWindow->Prob_DataStep);
					if(*CurrentWindow->Prob_Data_Int_16 <= CurrentWindow->Prob_MinData) {*CurrentWindow->Prob_Data_Int_16 = CurrentWindow->Prob_MinData;}
					if(*CurrentWindow->Prob_Data_Int_16 >= CurrentWindow->Prob_MaxData) {*CurrentWindow->Prob_Data_Int_16 = CurrentWindow->Prob_MaxData;}
					break;
				case WINDOW_DATA_STYLE_INT32:
					*CurrentWindow->Prob_Data_Int_32 += (WindowProbDeltaData * CurrentWindow->Prob_DataStep);
					if(*CurrentWindow->Prob_Data_Int_32 <= CurrentWindow->Prob_MinData) {*CurrentWindow->Prob_Data_Int_32 = CurrentWindow->Prob_MinData;}
					if(*CurrentWindow->Prob_Data_Int_32 >= CurrentWindow->Prob_MaxData) {*CurrentWindow->Prob_Data_Int_32 = CurrentWindow->Prob_MaxData;}
					break;
				case WINDOW_DATA_STYLE_INT64:
					*CurrentWindow->Prob_Data_Int_64 += (WindowProbDeltaData * CurrentWindow->Prob_DataStep);
					if(*CurrentWindow->Prob_Data_Int_64 <= CurrentWindow->Prob_MinData) {*CurrentWindow->Prob_Data_Int_64 = CurrentWindow->Prob_MinData;}
					if(*CurrentWindow->Prob_Data_Int_64 >= CurrentWindow->Prob_MaxData) {*CurrentWindow->Prob_Data_Int_64 = CurrentWindow->Prob_MaxData;}
					break;

			}
			
		}
	}
	WindowProbDeltaData = 0;
	
}

/**
 * @brief ��ӡ�˵�Ԫ�ز�����Ŀ��ֵ�ı�Ԫ�صĲ���
 * @param ��
 * @return ��
 */
void MoveMenuElements(void){

	//����Ŀ��������
	SetTargetCursor();
	//����Ŀ��˵��߿�
	SetTargetMenuFrame();
	//����Ŀ�����������
	SetTargetProbWidth();
	// //����Ŀ��������߶�
	SetTargetScrollBarHeight();


	// �ı�˵���ʼԪ�ص�����
	ChangePoint(&OLED_UI_PageStartPoint);
	// �ı�˵�����м��
	ChangeDistance(&OLED_UI_LineStep);
	// �ı�������߶�
	ChangeDistance(&OLED_UI_ScrollBarHeight);
	
	

	// �ı�˵��߿����
	ChangeArea(&OLED_UI_MenuFrame);

	// ��ӡ�˵�ҳ���Ԫ��
	PrintMenuElements();

	//�ı���Ĳ���
	ChangeArea(&OLED_UI_Cursor);
	//��ʾ���
	ReverseCoordinate(OLED_UI_Cursor.CurrentArea.X,OLED_UI_Cursor.CurrentArea.Y,OLED_UI_Cursor.CurrentArea.Width,OLED_UI_Cursor.CurrentArea.Height,CurrentMenuPage->General_CursorStyle);
	//������ɫģʽ
	OLED_SetColorMode(ColorMode);

	OLED_Brightness(OLED_UI_Brightness);

	ChangeDistance(&OLED_UI_ProbWidth);
	// �ı䴰�ڲ���
	ChangeArea(&OLED_UI_Window);

	// ������������
	OLED_WindowDataDispose();

	// ���ƴ���
	OLED_DrawWindow();


	
	
}


/**
 * @brief OLED_UI 主循环入口（渲染 + 刷新）
 * @note 该函数应在 while(1) 中被尽可能高频调用，用于完成一帧 UI 的绘制与显示。
 *       20ms 定时中断只负责输入采样/状态机推进（OLED_UI_InterruptHandler），不负责刷新屏幕。
 *
 * @details 调用顺序（每帧）：
 *          1) RunFadeOut()：处理进入/返回等渐隐过渡
 *          2) OLED_Clear()：清屏（清显存缓冲 OLED_DisplayBuf）
 *          3) MoveMenuElements()：根据当前状态/动画参数绘制菜单与窗口元素到缓冲区
 *          4) RunCurrentCallBackFunction()：在允许的时机执行当前菜单项回调（例如弹窗）
 *          5) OLED_UI_ShowFPS()：可选显示 FPS
 *          6) OLED_Update()：将缓冲区整屏刷到 OLED（I2C/SPI 由底层驱动决定）
 */
void OLED_UI_MainLoop(void){

	//����������������λʱ�����н���Ч��
	RunFadeOut();
	
	//����
	OLED_Clear();

	

	//�ƶ��˵�Ԫ��
	MoveMenuElements();

	
	//������������λʱ�����е�ǰ�˵���Ļص�����
	RunCurrentCallBackFunction();
	
	//��ʾFPS
	OLED_UI_ShowFPS();
	//ˢ��
	OLED_Update();
}




/**
 * @brief  OLED_UI���жϺ������ڲ����������ж��ڴ���������
 * @param  ��
 * @note ���ڸú������жϵ��е��ã����Ծ������漰ָ��Ĳ�������Ϊ�ҷ�����stm32��û�������ָ�����esp32������쳣��
 * @return ��
 */
void OLED_UI_InterruptHandler(void){
	if (CurrentMenuPage == NULL) {
		return;
	}
	// ��ȡ��ǰ��Ļˢ����
    GetFPS();
	MenuWindow* window = CurrentWindow;
	// �����ǰ������ִ�еĻص��������򲻴����ж��ڵ�����
    if(GetEnterFlag() && GetFadeoutFlag()){
    	

		//��ȡ_ActiveMenuID�ı仯ֵ��_ActiveMenuID��ֵ���䣬����¼�˰����ı仯��
		//�˺�����������ֵ������ȫֵ�ͷǰ�ȫֵ����ȫֵ�����ƶ����¹�꣬�ǰ�ȫֵ���ڴ��ڽ�����
		MenuID_Type IncreaseID = OLED_KeyAndEncoderRecord();


		//�������ͣ���ı�־λΪtrue��˵����ǰ�������д��ڣ����ڻ�û����ȫ��ʧ��
		if(OLED_SustainCounter.SustainFlag == true){
			//������������ǰ����ı仯ֵ����0
			if(IncreaseID.Unsafe != 0){
				//���ڼ���ֵ���㣬ʹ�ô��ڼ���ͣ��Ԥ���ʱ��
				OLED_SustainCounter.count = 0;
			}
			//���ı��ֵ����ȫ�ֱ���WindowProbDeltaData����������ѭ���ڲ��ı䴰�ڽ������ĳ��ȣ��ı���������䵱ǰֵ�漰ָ�����������ʵ�����ж��ڲ����и��ʻ�����쳣��
			WindowProbDeltaData += IncreaseID.Unsafe;
			//����ȫֵ���㣬��Ϊ��ʱ���ڲ�û����ʧ������ȫֵ�������ڲ˵�id��
			IncreaseID.Safe = 0;
		}
		 
		//����仯ֵС��0����ô�൱�ڰ���IncreaseID.Safe�Ρ��ϡ�����
		if(IncreaseID.Safe < 0 ){
			for(int i = 0; i < -IncreaseID.Safe; i++){
				//�����ǰ�˵��������б���
				if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
					/*********************���¡��ϡ��������еĲ���*************************/
					//�����ǰ�˵�ҳ��Ĺ���Ѿ���������Ĳ�λ,���ҵ�ǰ�˵���ǵ�һ���˵����ô�������ƶ��˵����Ŀ��λ��
           			if(CurrentMenuPage->_Slot == 0 && CurrentMenuPage->_ActiveMenuID !=0){
						MenuItemsMoveDown();

					}
					//�����껹û�е�������Ĳ�λ����ô�������ƶ���λ
					if(CurrentMenuPage->_Slot > 0){
						CurrentMenuPage->_Slot--;
					}
					CurrentMenuPage->_ActiveMenuID--;
				}
				//�����ǰ�˵��������б���
				if(CurrentMenuPage->General_MenuType == MENU_TYPE_TILES){
					CurrentMenuPage->_ActiveMenuID--;
					MenuItemsMoveRight();
				}
			}
		}
		if(IncreaseID.Safe > 0){
			for(int i = 0; i < IncreaseID.Safe; i++){
				/*********************���¡��¡��������еĲ���*************************/
					if(CurrentMenuPage->General_MenuType == MENU_TYPE_LIST){
					//�����ǰ�˵�ҳ��Ĺ���Ѿ�������ײ��Ĳ�λ,���ҵ�ǰ�˵�������һ���˵����ô�������ƶ��˵����Ŀ��λ��
					if(CurrentMenuPage->_Slot == GetCurrentMenuPageMaxSlotNum()-1 && CurrentMenuPage->_ActiveMenuID != GetMenuItemNum(CurrentMenuPage->General_MenuItems)){
						MenuItemsMoveUp();

					}
					//�����껹û�е�����ײ��Ĳ�λ����ô�������ƶ���λ
					if(CurrentMenuPage->_Slot < GetCurrentMenuPageMaxSlotNum()-1){
						CurrentMenuPage->_Slot++;
					}
					CurrentMenuPage->_ActiveMenuID++;
				}
				//�����ǰ�˵��������б���
				if(CurrentMenuPage->General_MenuType == MENU_TYPE_TILES){
					CurrentMenuPage->_ActiveMenuID++;
					MenuItemsMoveLeft();
				}

			}
		}
		
	
    	
		//�����⵽�����ء���������һ״̬����ε�״̬��ͬ������һ״̬��̧��״̬��˵���û������ˡ����ء����������Ҹող�̧��
		if(OLED_UI_Key.Back != OLED_UI_LastKey.Back && OLED_UI_Key.Back == 1){
			//�����ǰû�����д���
			if(OLED_SustainCounter.SustainFlag != true){
				BackEventMenuItem();
			}else{
				OLED_SustainCounter.count = (int16_t)(window->General_ContinueTime * 50);
			}
			
		}
		//�����⵽��ȷ�ϡ���������һ״̬����ε�״̬��ͬ������һ״̬��̧��״̬��˵���û������ˡ�ȷ�ϡ����������Ҹող�̧��
		if(OLED_UI_Key.Enter != OLED_UI_LastKey.Enter && OLED_UI_Key.Enter == 1){
			//�����ǰû�����д���
			if(OLED_SustainCounter.SustainFlag != true){
				EnterEventMenuItem();
				if (CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].List_BoolRadioBox != NULL) {
				    *CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].List_BoolRadioBox = !(*CurrentMenuPage->General_MenuItems[CurrentMenuPage->_ActiveMenuID].List_BoolRadioBox);
				}
			}else{
				//����ȫֵ���㣬��Ϊ��ʱ���ڲ�û����ʧ������ȫֵ�������ڲ˵�id��
				OLED_SustainCounter.count = 0;
			}
		}
		
	}
	
    //�����ǰ�������д��ڣ���ô����
	if(OLED_SustainCounter.SustainFlag == true){
		OLED_SustainCounter.count++;
	}
	
}
#endif


