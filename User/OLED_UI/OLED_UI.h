#ifndef __OLED_UI_H
#define __OLED_UI_H
// ����Ƿ���C++������
#ifdef __cplusplus
extern "C" {
#endif
/*�����Ҫʹ��OLED_UI�⣬�벻Ҫ������ע�͵� */
#define OLED_UI 

#ifdef OLED_UI

#include "OLED_UI_Driver.h"
#include "OLED.h"
#include "stdint.h"
#include "stdbool.h"

// �Դ滺����
extern uint8_t OLED_DisplayBuf[OLED_HEIGHT/8][OLED_WIDTH];

/************************************************************/
/***********************�û��������õĺ궨��******************/

// /***********�����б���˵��ʼ������ڲ˵������λ�õĺ�***********/


/***********���ڴ�����˵��ʼ�������Ļ����λ�õĺ�***********/
#define TILES_STARTPOINT_Y			(6)			//������˵��ʼ���������Ļ������Y����

/***********���ڴ�����˵���Ĺ�������ʼ����Դ����ײ�λ�õĺ�***********/
#define TILES_SCROLLBAR_Y			(4)			//������˵��ʼ���������Ļ������Y����

/***********���ڴ�����˵������־�����Ļ�ײ��ľ���ĺ�***********/
#define TILES_BOTTOM_DISTANCE						(0)			//������˵������־�����Ļ�ײ��ľ���

/************���ڲ˵����������ٶȵĺ�**********************/
//���˵���ȳ����˵��������ʱ����ui��ܻ��Զ�ʵ�ֲ˵���ĺ��������ʾ�����ǲ˵���������������ÿһ֡���������ؾ��룩
#define LINE_SLIP_SPEED			(0.5)			//�˵����������ٶȡ�������С�������������1������������1��ż����֮һ����

/************�����Ƿ���ƴ���ָʾ��ͷ�ĺ�**********************/
#define IF_DRAW_ARROR			(true)			//�Ƿ���ƴ���ָʾ��ͷ

#define OLED_UI_ENABLE_TILES			(0)



/************���ڲ˵���ǰ׺���ŵĺ�**********************/

#define FUNCTION_PREFIX			    "~"			//����ǰ׺����
#define SUBMENU_PREFIX				">"			//�˵�ǰ׺����
#define RADIO_PREFIX				"*"			//��ѡ��ǰ׺����
#define NONE_PREFIX					"-"			//�޲���ǰ׺����

#define LINEPERFIX_DISTANCE			(2)			//��ǰ׺����������ֵľ���

/*******************�����Ƿ�ȴ�������������ٹ������ı��ĺ�******************/

#define IF_WAIT_ANIMATION_FINISH          (true)

/*******************���ڳ��������ĺ�******************/
#define IF_START_UP_AND_DOWN_LONG_PRESS    (true)   //�Ƿ����ϰ������°����ĳ�������
#define PRESS_TIME                      (0.6)    //���°�����Ϊ������ʱ�䣨��λ�룩
#define CONTINUE_PRESS_TIME             (2.0)    //�ڳ���0.8��֮�����������ʱ�䣨��λ�룩
#define PRESS_MOVE_SPEED                (5)      //��������֮��ѡ��������ٶȣ�1Ϊ��죬����Խ��Խ����
#define CONTINUE_PRESS_MOVE_SPEED       (1)      //��������֮���������CONTINUE_PRESS_TIME���ѡ��������ٶȣ�1Ϊ��죬����Խ��Խ����
/*******************���ڴ�������������֮�����ĺ�******************/
#define WINDOW_DATA_TEXT_DISTANCE           (4)

/**************���ڵ���ÿ֡��ʱ��ĺ�**********/
#define FADEOUT_TIME					(40)			//�˵����ÿ֡��ʱ��


/***********************���ڴ�����ʾС�����λ����**********/ 
#define FLOAT_POINT_LENGTH			(2)			//��ʾ����������ʱС�������ʾ��λ��
/************************************************************/







/**********�û��������õĺ궨�塾���º궨�岻Ҫ�Ķ���********/

/***********�йع�����͵ĺ�***********/
#define REVERSE_RECTANGLE 				(0)			//���η�ɫ
#define REVERSE_ROUNDRECTANGLE 		(1)			//Բ�Ǿ��η�ɫ
#define HOLLOW_RECTANGLE 					(2)			//���ľ���
#define HOLLOW_ROUNDRECTANGLE 			(3)			//����Բ�Ǿ���
#define REVERSE_BLOCK						(4)			//�»���
#define NOT_SHOW							(5)			//����ʾ���

/***********����UI�����С�ĺ�***********/
#define OLED_UI_FONT_8	   		 (8)
#define OLED_UI_FONT_12			  	(12)
#define OLED_UI_FONT_16		  		(16)
#define OLED_UI_FONT_20		  		(20)

#define CHINESE						(0)			//����
#define ASCII						(1)			//ASCII
/***********������ʾģʽ�ĺ�***********/
#define DARKMODE						true			//��ɫģʽ
#define LIGHTMODE						false			//ǳɫģʽ



/***********���ڻ��������߱�־λ�ĺ�***********/
#define FLAGEND			  	      (0)
#define FLAGSTART		      (1)
#define ENTER_FLAGSTART	   		      (1)
#define BACK_FLAGSTART		      (2)


/************���ڲ˵��ṹ�嵱�й��ڲ˵�����ĺ�***********/
#define FULLSCREEN      1,1,OLED_WIDTH-2,OLED_HEIGHT-2

/*********************����ȷ�Ϸ��صĺ�********************** */
#define OLED_UI_BACK    			(0)
#define OLED_UI_ENTER   			(1)

/*********************���ڲ˵����͵ĺ�********************** */

#define MENU_TYPE_LIST				(0)			//�б�����
#define MENU_TYPE_TILES				(1)			//��������


/*********************���ڶ������͵ĺ�********************** */
#define UNLINEAR 			      (0)
#define PID_CURVE     	 	      (1)

/*********************���ڴ������͵ĺ�********************** */
#define WINDOW_RECTANGLE			(0)			//���δ���
#define WINDOW_ROUNDRECTANGLE		(1)			//Բ�Ǿ��δ���

/*********************���ڴ����������͵ĺ�* ***************/
#define WINDOW_DATA_STYLE_NONE	    (0)			//��
#define WINDOW_DATA_STYLE_FLOAT		(1)			//����������
#define WINDOW_DATA_STYLE_INT8		(2)			//����8λ����
#define WINDOW_DATA_STYLE_INT16		(3)			//����16λ����
#define WINDOW_DATA_STYLE_INT32		(4)			//����32λ����
#define WINDOW_DATA_STYLE_INT64		(5)			//����64λ����



/***************************�궨��****************************/
/************************************************************/

/*��ʾ�˵����͵����ݽṹ*/
typedef int8_t MenuStyle;


/*��ʾ�˵�ID�����ݽṹ*/
typedef int16_t MenuID;

/*��ʾ�˵�ID�����ݽṹ*/
typedef float MenuMovingSpeed;

/*��ʾ�˵�ID�����ݽṹ*/
typedef int8_t OLED_Font;

/*��ʾ���������־λ�����ݽṹ��ֻ������״̬FLAGSTART��FLAGEND*/
typedef int8_t MutexFlag;

/*�˵�id�ṹ�壬�洢�ž������ƵĲ˵�id�Ͳ��������ƵĲ˵�id*/
typedef struct MenuID_Type{
	MenuID Safe;
	MenuID Unsafe;
}MenuID_Type;

/*OLED_UI�����е�����Ľṹ��*/
typedef struct OLED_Point{
	float X; 
	float Y;
} OLED_Point;

/*OLED_UI�����й�λ�����С�Ľṹ��*/
typedef struct  OLED_Area{
    float X;
    float Y;
    float Width;
    float Height;
} OLED_Area;

/*OLED_UI�������ڴ�Ű����������ݵĽṹ��*/
typedef struct OLED_Key{ 
	uint8_t Enter;	//ȷ�ϼ�
	uint8_t Back;	//���ؼ�
	uint8_t Up;		//��
	uint8_t Down;	//��
} OLED_Key;

/*OLED_UI���д�Ź����Ϣ�Ľṹ�塾�����������ƶ�Ч���� */
typedef struct OLED_ChangeArea{
	OLED_Area CurrentArea;	//��ǰ�������
	OLED_Area TargetArea;		//Ŀ��������
	OLED_Area Error;			//���ֵ
	OLED_Area LastError;		//��һ�ε����ֵ
	OLED_Area Integral;		//����ֵ
	OLED_Area Derivative;		//΢��ֵ

}OLED_ChangeArea;

typedef struct OLED_ChangePoint{
	OLED_Point CurrentPoint;	//��ǰ������
	OLED_Point TargetPoint;		//Ŀ�������
	OLED_Point Error;			//���ֵ
	OLED_Point LastError;		//��һ�ε����ֵ
	OLED_Point Integral;		//����ֵ
	OLED_Point Derivative;		//΢��ֵ

}OLED_ChangePoint;

/**
 * @brief �˽ṹ�����ڼ��㶯��,��Ҫ�������ڷ����ԣ�pid�ȵĲ�����
 *  @param CurrentDistance ��ǰֵ
 *  @param TargetDistance Ŀ��ֵ
 *  @param Error ���ֵ
 *  @param LastError ��һ�ε����ֵ
 *  @param Integral ����ֵ
 *  @param Derivative ΢��ֵ
 *  */ 
typedef struct OLED_ChangeDistance{
	float CurrentDistance;		//��ǰֵ
	float TargetDistance;		//Ŀ��ֵ
	float Error;					//���ֵ
	float LastError;				//��һ�ε����ֵ
	float Integral;				//����ֵ
	float Derivative;				//΢��ֵ

}OLED_ChangeDistance;

/*OLED_UI���д�ż�������Ϣ�Ľṹ��*/
typedef struct OLED_UI_Counter{
	int16_t count;
	int16_t value;
	int16_t step;
}OLED_UI_Counter;

/*OLED_UI��������ʵ�ִ���ͣ���Ľṹ��*/
typedef struct OLED_UI_WindowSustainCounter{
	int16_t count;		//������
	bool SustainFlag;	//��־λ�����ڱ�ʾ�Ƿ���ͣ��״̬
}OLED_UI_WindowSustainCounter;

/*OLED_UI���в˵����ڵĽṹ��*/
typedef struct MenuWindow{
	int16_t General_Width;									//[ͨ������]���ڿ���
	int16_t General_Height;									//[ͨ������]���ڸ߶�
	float General_ContinueTime;                             //[ͨ������]����ͣ��ʱ��
	uint8_t General_WindowType;                             //[ͨ������]��������

	char* Text_String;										//[�ı�����]������ʾ������
	OLED_Font Text_FontSize;								//[�ı�����]���������С
	int16_t Text_FontSideDistance;						//[�ı�����]����������ľ���
	int16_t Text_FontTopDistance;						//[�ı�����]������붥���ľ���




	float* Prob_Data_Float;										//[����������]��������ָ��(��������)����ѡһ��
	int8_t* Prob_Data_Int_8;										//[����������]��������ָ��(int8_t��������)����ѡһ��
	int16_t* Prob_Data_Int_16;										//[����������]��������ָ��(int16_t��������)����ѡһ��
	int32_t* Prob_Data_Int_32;										//[����������]��������ָ��(int16_t��������)����ѡһ��
	int64_t* Prob_Data_Int_64;										//[����������]��������ָ��(int16_t��������)����ѡһ��
	float Prob_DataStep;									//[����������]�������ݲ���
	float Prob_MinData;									//[����������]�������ݵ���Сֵ
	float Prob_MaxData;									//[����������]�������ݵ����ֵ
	int16_t Prob_BottomDistance;							//[����������]�������ײ����봰�ڵײ��ľ���
	int16_t Prob_SideDistance;								//[����������]��������Ե���봰�ڱ�Ե�ľ���
	int16_t Prob_LineHeight;								//[����������]�����������߶�

	float _LineSlip;                                        //[˽������]���ڹ�����ʾ���ı�
}MenuWindow;




/*OLED_UI���в˵���Ľṹ�壬���ڴ�Ų˵���������Ϣ��
�������ƣ������С���ص��������Ӳ˵�ָ�룬���˵�ָ�룬��ʼ�㣬ѡ�������Ƿ��Ծ״̬���Ƿ������һ���˵���*/
typedef struct MenuPage {
    MenuStyle General_MenuType;
    MenuMovingSpeed General_MovingSpeed;
    uint8_t General_CursorStyle;
    uint8_t General_MoveStyle;
    OLED_Font General_FontSize;
    struct MenuPage* General_ParentMenuPage;
    struct MenuItem* General_MenuItems;
    int16_t General_LineSpace;
    void (*General_ShowAuxiliaryFunction)(void);

    OLED_Area List_MenuArea;
    bool List_IfDrawFrame;
    bool List_IfDrawLinePerfix;
	int16_t List_StartPointX;
    int16_t List_StartPointY;

    int16_t Tiles_ScreenWidth;
    int16_t Tiles_ScreenHeight;
    int16_t Tiles_TileWidth;
    int16_t Tiles_TileHeight;

    MenuID _ActiveMenuID;
    MenuID _Slot;
    OLED_Point _StartPoint;
	bool _IfInit;
} MenuPage;

typedef struct MenuItem {
    char* General_item_text;
    void (*General_callback)(void);
    MenuPage* General_SubMenuPage;

    bool* List_BoolRadioBox;
    const uint8_t* Tiles_Icon;

    float _LineSlip;
} MenuItem;

/******************************************************************************** */
/******************************************************************************** */
void GetFPS(void);
void OLED_UI_ShowFPS(void);
OLED_Font GetOLED_Font(OLED_Font fontsize,bool style);
void ReverseCoordinate(int16_t X, int16_t Y, int16_t Width, int16_t Height,uint8_t Style);
void OLED_UI_FadeOut_Masking(int16_t x0, int16_t y0, int16_t width, int16_t height, int8_t fadeLevel);
void OLED_UI_FadeoutCurrentArea(int16_t x, int16_t y, int16_t width, int16_t height);
void OLED_UI_FadeoutAllArea(void);
MenuID GetMenuItemNum(MenuItem * items);
void ChangeFloatNum(float *CurrentNum, float *TargetNum, float *ErrorNum, float *LastErrorNum, float * IntegralNum, float *DerivativeNum);
void ChangeDistance(OLED_ChangeDistance *distance);
void ChangePoint(OLED_ChangePoint *point);
void ChangeArea(OLED_ChangeArea *area);
void CurrentMenuPageInit(void);
void CurrentMenuPageBackUp(void);
void OLED_UI_Init(MenuPage* Page);
bool GetEnterFlag(void);
bool GetFadeoutFlag(void);
int16_t CalcStringWidth(int16_t ChineseFont, int16_t ASCIIFont, const char *format, ...);
int8_t GetWindowProbDataStyle(MenuWindow* window);
void OLED_DrawWindow(void);
void MenuItemsMoveUp(void);
void MenuItemsMoveDown(void);
void MenuItemsMoveLeft(void);
void MenuItemsMoveRight(void);
int16_t GetCurrentMenuPageMaxSlotNum(void);
void SetTargetCursor(void);
void SetTargetMenuFrame(void);
void SetLineSplitZero(void);
void SetTargetScrollBarHeight(void);
void SetTargetProbWidth(void);
void DrawLinePermix(MenuPage* page,MenuID i,OLED_Point* CursorPoint,OLED_Font ChineseFont,OLED_Font ASCIIFont);
void PrintMenuElements(void);
MenuID_Type OLED_KeyAndEncoderRecord(void);
void SetEnterFlag(void);
void ResetEnterFlag(void);
void SetFadeOutFlag(MutexFlag action);
void ResetFadeOutFlag(void);
void EnterEventMenuItem(void);
void BackEventMenuItem(void);
void OLED_UI_Back(void);
void RunCurrentCallBackFunction(void);
void SetCursorZero(void);
void OLED_UI_CreateWindow(MenuWindow* window);
void RunFadeOut(void);
void OLED_WindowDataDispose(void);
void MoveMenuElements(void);
void OLED_UI_MainLoop(void);
void OLED_UI_InterruptHandler(void);     



/******************************************************************************** */
/******************************************************************************** */
//�ı亯��
void ChangeDistance(OLED_ChangeDistance *distance);
void ChangePoint(OLED_ChangePoint *point);
void ChangeArea(OLED_ChangeArea *area);


//��ָ�������Ԫ�ؽ���
void OLED_UI_FadeoutCurrentArea(int16_t x, int16_t y, int16_t width, int16_t height);

//ȫ������
void OLED_UI_FadeoutAllArea(void);

//��ʼ��OLED_UI�����õ�ǰҳ��Ľṹ��ָ�룬����ʼ��OLED��ʾ��
void OLED_UI_Init(MenuPage* Page);

//���غ���
void OLED_UI_Back(void);

//��������
void OLED_UI_CreateWindow(MenuWindow* window);

//OLED_UI����ѭ������
void OLED_UI_MainLoop(void);

//OLED_UI���жϺ������ڲ����������ж��ڴ���������
void OLED_UI_InterruptHandler(void);          //OLED_UI����жϴ�������,��Ҫ�����жϺ����ڵ��ã��жϺ���2��Ҫ����Ϊ20ms



#endif

#ifdef __cplusplus
}  // extern "C"
#endif
#endif

