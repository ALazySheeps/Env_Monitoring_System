#include "OLED_UI_MenuData.h"
#include "OLED_UI.h"

#if 0
/*���ļ����ڴ�Ų˵����ݡ�ʵ���ϲ˵����ݿ��Դ�����κεط�������ڴ˴���Ϊ�˹淶�����ģ�黯*/

// ColorMode ��һ����OLED_UI���ж����bool���ͱ��������ڿ���OLED��ʾ����ɫģʽ�� DARKMODE Ϊ��ɫģʽ�� LIGHTMOOD Ϊǳɫģʽ�����ｫ��������Ϊ�˴�����ѡ��˵��
extern bool ColorMode;
extern bool OLED_UI_ShowFps;
// OLED_UI_Brightness ��һ����OLED_UI���ж����int16_t���ͱ��������ڿ���OLED��ʾ�����ȡ����ｫ��������Ϊ�˴����������ȵĻ��������ڣ���Χ0-255��
extern int16_t OLED_UI_Brightness;
float testfloatnum = 0.5;
int32_t testintnum = 1;
#define SPEED 10

//���ڴ��ڵĽṹ��
MenuWindow SetBrightnessWindow = {
	.General_Width = 80,								//���ڿ���
	.General_Height = 28, 							//���ڸ߶�
	.Text_String = "��Ļ������Ļ����",					//���ڱ���
	.Text_FontSize = OLED_UI_FONT_12,				//�ָ�
	.Text_FontSideDistance = 4,							//����������ľ���
	.Text_FontTopDistance = 3,							//������붥���ľ���
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//��������
	.General_ContinueTime = 4.0,						//���ڳ���ʱ��

	.Prob_Data_Int_16 = &OLED_UI_Brightness,				//��ʾ�ı�����ַ
	.Prob_DataStep = 5,								//����
	.Prob_MinData = 5,									//��Сֵ
	.Prob_MaxData = 255, 								//���ֵ
	.Prob_BottomDistance = 3,							//�ײ����
	.Prob_LineHeight = 8,								//�������߶�
	.Prob_SideDistance = 4,								//�߾�
};
/**
 * @brief ������ʾ���ȴ���
 */
void BrightnessWindow(void){
	OLED_UI_CreateWindow(&SetBrightnessWindow);
}
//���ڴ��ڵĽṹ��
MenuWindow NullWindow = {
	.General_Width = 80,								//���ڿ���
	.General_Height = 28, 							//���ڸ߶�
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//��������
	.General_ContinueTime = 4.0,						//���ڳ���ʱ��
};
/**
 * @brief ������ʾ���ȴ���
 */
void EmptyWindow(void){
	OLED_UI_CreateWindow(&NullWindow);
}
//���ڴ��ڵĽṹ��
MenuWindow TextWindow = {
	.General_Width = 75,								//���ڿ���
	.General_Height = 18, 							//���ڸ߶�
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//��������
	.General_ContinueTime = 4.0,						//���ڳ���ʱ��

	.Text_String = "����text",					//���ڱ���
	.Text_FontSize = OLED_UI_FONT_12,				//�ָ�
	.Text_FontSideDistance = 8,							//����������ľ���
	.Text_FontTopDistance = 2,							//������붥���ľ���
	

};
/**
 * @brief ������ʾ���ȴ���
 */
void ShowTextWindow(void){
	OLED_UI_CreateWindow(&TextWindow);
}
//���ڴ��ڵĽṹ��
MenuWindow FloatDataWindow = {
	.General_Width = 80,								//���ڿ���
	.General_Height = 28, 							//���ڸ߶�
	.Text_String = "�������ݲ���",					//���ڱ���
	.Text_FontSize = OLED_UI_FONT_12,				//�ָ�
	.Text_FontSideDistance = 4,							//����������ľ���
	.Text_FontTopDistance = 3,							//������붥���ľ���
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//��������
	.General_ContinueTime = 4.0,						//���ڳ���ʱ��

	.Prob_Data_Float = &testfloatnum,				//��ʾ�ı�����ַ
	.Prob_DataStep = 0.1,								//����
	.Prob_MinData = -100,									//��Сֵ
	.Prob_MaxData = 100, 								//���ֵ
	.Prob_BottomDistance = 3,							//�ײ����
	.Prob_LineHeight = 8,								//�������߶�
	.Prob_SideDistance = 4,	
};
/**
 * @brief ������ʾ���ȴ���
 */
void ShowFloatDataWindow(void){
	OLED_UI_CreateWindow(&FloatDataWindow);
}
//���ڴ��ڵĽṹ��
MenuWindow IntDataWindow = {
	.General_Width = 80,								//���ڿ���
	.General_Height = 28, 							//���ڸ߶�
	.Text_String = "�������ݲ���",					//���ڱ���
	.Text_FontSize = OLED_UI_FONT_12,				//�ָ�
	.Text_FontSideDistance = 4,							//����������ľ���
	.Text_FontTopDistance = 3,							//������붥���ľ���
	.General_WindowType = WINDOW_ROUNDRECTANGLE, 	//��������
	.General_ContinueTime = 4.0,						//���ڳ���ʱ��

	.Prob_Data_Int_32 = &testintnum,				//��ʾ�ı�����ַ
	.Prob_DataStep = 1,								//����
	.Prob_MinData = -100,									//��Сֵ
	.Prob_MaxData = 100, 								//���ֵ
	.Prob_BottomDistance = 3,							//�ײ����
	.Prob_LineHeight = 8,								//�������߶�
	.Prob_SideDistance = 4,	
};
/**
 * @brief ������ʾ���ȴ���
 */
void ShowIntDataWindow(void){
	OLED_UI_CreateWindow(&IntDataWindow);
}
//��LOGO�ƶ��Ľṹ��
OLED_ChangePoint LogoMove;
//��LOGO�����ƶ��Ľṹ��
OLED_ChangePoint LogoTextMove;
//welcome�����ƶ��Ľṹ��
OLED_ChangePoint WelcomeTextMove;

extern OLED_ChangePoint OLED_UI_PageStartPoint ;



//���ò˵���ĸ�����ʾ����
void SettingAuxFunc(void){
	//�ڹ涨λ����ʾLOGO
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		LogoMove.TargetPoint.X = 0;
		LogoMove.TargetPoint.Y = 0;
	}
	//��LOGOTEXT�ƶ�����Ļ�Ҳ࿴�����ĵط�
	LogoTextMove.TargetPoint.X = 129;
	LogoTextMove.TargetPoint.Y = 0;
	//��Welcome�����ƶ�����Ļ�ײ��������ĵط�
	WelcomeTextMove.TargetPoint.X = 128;
	WelcomeTextMove.TargetPoint.Y = 0;
	ChangePoint(&LogoMove);
	OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	ChangePoint(&LogoTextMove);
	OLED_ShowImageArea(LogoTextMove.CurrentPoint.X,LogoTextMove.CurrentPoint.Y,26,64,0,0,128,128,OLED_UI_LOGOTEXT64);
	ChangePoint(&WelcomeTextMove);
	OLED_ShowImageArea(WelcomeTextMove.CurrentPoint.X,WelcomeTextMove.CurrentPoint.Y,16,64,0,0,128,128,OLED_UI_LOGOGithub);
}

//���ڲ˵��ĸ�����ʾ����
void AboutThisDeviceAuxFunc(void){
	//��LOGO�ƶ�����Ļ�Ϸ��������ĵط�
	LogoMove.TargetPoint.X = 0;
	LogoMove.TargetPoint.Y = -80;
	ChangePoint(&LogoMove);
    OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	//����Ļ�Ҳ���ʾLOGO����
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		LogoTextMove.TargetPoint.X = 102;
		LogoTextMove.TargetPoint.Y = 0;
	}
	ChangePoint(&LogoTextMove);
	OLED_ShowImageArea(LogoTextMove.CurrentPoint.X,LogoTextMove.CurrentPoint.Y,26,64,0,0,128,128,OLED_UI_LOGOTEXT64);
}
//����OLED UI�ĸ�����ʾ����
void AboutOLED_UIAuxFunc(void){
	//��LOGO�ƶ�����Ļ�Ϸ��������ĵط�
	LogoMove.TargetPoint.X = 0;
	LogoMove.TargetPoint.Y = -80;
	ChangePoint(&LogoMove);
	OLED_ShowImageArea(LogoMove.CurrentPoint.X,LogoMove.CurrentPoint.Y,32,64,0,0,128,128,OLED_UI_SettingsLogo);
	//����Ļ�Ҳ���ʾWelcome����
	if(fabs(OLED_UI_PageStartPoint.CurrentPoint.X - OLED_UI_PageStartPoint.TargetPoint.X) < 4){
		WelcomeTextMove.TargetPoint.X = 110;
		WelcomeTextMove.TargetPoint.Y = 0;
	}
	ChangePoint(&WelcomeTextMove);
	OLED_ShowImageArea(WelcomeTextMove.CurrentPoint.X,WelcomeTextMove.CurrentPoint.Y,16,64,0,0,128,128,OLED_UI_LOGOGithub);

}
//���˵��ĸ�����ʾ����
void MainAuxFunc(void){
	//����ʾ
	LogoMove.TargetPoint.X = -200;
	LogoMove.TargetPoint.Y = 0;
	LogoMove.CurrentPoint.X = -200;
	LogoMove.CurrentPoint.Y = 0;

	LogoTextMove.TargetPoint.X = 129;
	LogoTextMove.TargetPoint.Y = 0;
	LogoTextMove.CurrentPoint.X = 129;
	LogoTextMove.CurrentPoint.Y = 0;
	
	WelcomeTextMove.TargetPoint.X = 128;
	WelcomeTextMove.TargetPoint.Y = 0;
	WelcomeTextMove.CurrentPoint.X = 128;
	WelcomeTextMove.CurrentPoint.Y = 0;
}

//���˵��Ĳ˵���
MenuItem MainMenuItems[] = {

	{.General_item_text = "Settings",.General_callback = NULL,.General_SubMenuPage = &SettingsMenuPage,.Tiles_Icon = Image_setings},
	{.General_item_text = "WeChat",.General_callback = NULL,.General_SubMenuPage = NULL,.Tiles_Icon = Image_wechat},
	{.General_item_text = "Alipay",.General_callback = NULL,.General_SubMenuPage = NULL,.Tiles_Icon = Image_alipay},
	{.General_item_text = "������ Calc ���ı����� LongText",.General_callback = NULL,.General_SubMenuPage = NULL,.Tiles_Icon = Image_calc},
	{.General_item_text = "Night",.General_callback = NULL,.General_SubMenuPage = NULL,.Tiles_Icon = Image_night},
	{.General_item_text = "More",.General_callback = NULL,.General_SubMenuPage = &MoreMenuPage,.Tiles_Icon = Image_more},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/

};
//���ò˵�����������
MenuItem SettingsMenuItems[] = {
	{.General_item_text = "����",.General_callback = BrightnessWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�ڰ�ģʽ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = &ColorMode},
	{.General_item_text = "��ʾ֡��",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = &OLED_UI_ShowFps},
	{.General_item_text = "���豸",.General_callback = NULL,.General_SubMenuPage = &AboutThisDeviceMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "����OLED UI",.General_callback = NULL,.General_SubMenuPage = &AboutOLED_UIMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "��л�ۿ�,һ������! Thanks for watching, three clicks!",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem AboutThisDeviceMenuItems[] = {
	{.General_item_text = "-[MCU:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " STM32F103",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " RAM:20KB",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " ROM:64KB",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[Screen:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " SSD1306 128x64 OLED",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[CP:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " SoftWare SPI",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem AboutOLED_UIMenuItems[] = {
	{.General_item_text = "-[Author:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " bilibili @��nm������",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "-[Adress:]",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = " https://github.com/bdth-7777777/OLED_UI",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},

	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem MoreMenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "����߶�8demo",.General_callback = NULL,.General_SubMenuPage = &Font8MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "����߶�12demo",.General_callback = NULL,.General_SubMenuPage = &Font12MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "����߶�16demo",.General_callback = NULL,.General_SubMenuPage = &Font16MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "����߶�20demo",.General_callback = NULL,.General_SubMenuPage = &Font20MenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�demo",.General_callback = NULL,.General_SubMenuPage = &LongMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "�ص�����demo",.General_callback = NULL,.General_SubMenuPage = &SpringMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����˵��б�demo",.General_callback = NULL,.General_SubMenuPage = &LongListMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "��С����˵�demo",.General_callback = NULL,.General_SubMenuPage = &SmallAreaMenuPage,.List_BoolRadioBox = NULL},
	{.General_item_text = "�մ���demo",.General_callback = EmptyWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "���ִ���demo",.General_callback = ShowTextWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "����������������demo",.General_callback = ShowFloatDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "��������������demo",.General_callback = ShowIntDataWindow,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};
MenuItem Font8MenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem Font12MenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem Font16MenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem Font20MenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem LongMenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�ǳ��ǳ��ǳ��������ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Very Very Very Long English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem SpringMenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem LongListMenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item1",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item2",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item3",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item4",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item5",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item6",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item7",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item8",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item9",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item10",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item11",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item12",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item13",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item14",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item15",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item16",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item17",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item18",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item19",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item20",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item21",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item22",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item23",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item24",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item25",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item26",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item27",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item28",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item29",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item30",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item31",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item32",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item33",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item34",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item35",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item36",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item37",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item38",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item39",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item40",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item41",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item42",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item43",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item44",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item45",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item46",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item47",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item48",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item49",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item50",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item51",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item52",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item53",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item54",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item55",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item56",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item57",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item58",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item59",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item60",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item61",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item62",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item63",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item64",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item65",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item66",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item67",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item68",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item69",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item70",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item71",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item72",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item73",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item74",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item75",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item76",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item77",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item78",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item79",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item80",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item81",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item82",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item83",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item84",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item85",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},	
	{.General_item_text = "Item86",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item87",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item88",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item89",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item90",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item91",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item92",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item93",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item94",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item95",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item96",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item97",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item98",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item99",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item100",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item101",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item102",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item103",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item104",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item105",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item106",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item107",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item108",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item109",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item110",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item111",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item112",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item113",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item114",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item115",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item116",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item117",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item118",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item119",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item120",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item121",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item122",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item123",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item124",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item125",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item126",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item127",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item128",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "Item129",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};

MenuItem SmallAreaMenuItems[] = {
	{.General_item_text = "[����]",.General_callback = OLED_UI_Back,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "�����ı�",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "English Text",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "1234567890",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = "abcdefghijklmnopqrstuvwxyz",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = ",.[]!@#$+-/^&*()",.General_callback = NULL,.General_SubMenuPage = NULL,.List_BoolRadioBox = NULL},
	{.General_item_text = NULL},/*���һ���General_item_text��ΪNULL����ʾ����Ϊ�ָ���*/
};



MenuPage MainMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_TILES,  		 //�˵�����Ϊ��������
	.General_CursorStyle = NOT_SHOW,			 //�������
	.General_FontSize = OLED_UI_FONT_16,			//�ָ�
	.General_ParentMenuPage = NULL,				//�������Ǹ��˵������Ը��˵�ΪNULL
	.General_LineSpace = 5,						//������� ��λ�����أ����ڴ������Ͳ˵�����ֵ��ʾÿ������֮��ļ�࣬�����б����Ͳ˵�����ֵ��ʾ�м�ࣩ
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽ
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = MainAuxFunc,		 //��ʾ��������
	.General_MenuItems = MainMenuItems,			//�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.Tiles_ScreenHeight = 64,					//��Ļ�߶�
	.Tiles_ScreenWidth = 128,						//��Ļ����
	.Tiles_TileWidth = 32,						 //��������
	.Tiles_TileHeight = 32,						 //�����߶�
};


MenuPage SettingsMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������Ϊ����
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MainMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = SettingAuxFunc,		 //��ʾ��������
	.General_MenuItems = SettingsMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {32, 0, 95, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����
};

MenuPage AboutThisDeviceMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_BLOCK,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &SettingsMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = AboutThisDeviceAuxFunc,		 //��ʾ��������
	.General_MenuItems = AboutThisDeviceMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 100, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = false,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage AboutOLED_UIMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_BLOCK,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &SettingsMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = AboutOLED_UIAuxFunc,		 //��ʾ��������
	.General_MenuItems = AboutOLED_UIMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 105, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = false,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};
MenuPage MoreMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MainMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = MoreMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {1, 1, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage Font8MenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_8,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 5,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = Font8MenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage Font12MenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = Font12MenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage Font16MenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_16,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 5,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = Font16MenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {1, 1, 126, 62},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage Font20MenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_20,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 10,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = Font20MenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage LongMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = LongMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage SpringMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = PID_CURVE,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = SpringMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage LongListMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 4,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = LongListMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {0, 0, 128, 64},			 //�б���ʾ����
	.List_IfDrawFrame = false,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};

MenuPage SmallAreaMenuPage = {
	//ͨ�����ԣ�����
	.General_MenuType = MENU_TYPE_LIST,  		 //�˵�����Ϊ�б�����
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,	 //�������ΪԲ�Ǿ���
	.General_FontSize = OLED_UI_FONT_12,			//�ָ�
	.General_ParentMenuPage = &MoreMenuPage,		 //���˵�Ϊ���˵�
	.General_LineSpace = 6,						//�м�� ��λ������
	.General_MoveStyle = UNLINEAR,				//�ƶ���ʽΪ���������߶���
	.General_MovingSpeed = SPEED,					//�����ƶ��ٶ�(��ֵ����ʵ��Ч������)
	.General_ShowAuxiliaryFunction = NULL,		 //��ʾ��������
	.General_MenuItems = SmallAreaMenuItems,		 //�˵�����������

	//�������ԣ�����.General_MenuType������ѡ��
	.List_MenuArea = {10, 10, 60, 36},			 //�б���ʾ����
	.List_IfDrawFrame = true,					 //�Ƿ���ʾ�߿�
	.List_IfDrawLinePerfix = true,				 //�Ƿ���ʾ��ǰ׺
	.List_StartPointX = 4,                        //�б���ʼ��X����
	.List_StartPointY = 2,                        //�б���ʼ��Y����

};
#endif

extern bool ColorMode;
extern bool OLED_UI_ShowFps;
extern float sensor_data[];

static MenuWindow AboutWindow = {
	.General_Width = 86,
	.General_Height = 24,
	.General_WindowType = WINDOW_ROUNDRECTANGLE,
	.General_ContinueTime = 2.0,
	.Text_String = "Env Monitor",
	.Text_FontSize = OLED_UI_FONT_8,
	.Text_FontSideDistance = 4,
	.Text_FontTopDistance = 3,
};

static void ShowAboutWindow(void)
{
	OLED_UI_CreateWindow(&AboutWindow);
}

MenuPage MainMenuPage;
MenuPage DisplayMenuPage;
MenuPage SensorMenuPage;
MenuPage Sensor0Page;
MenuPage Sensor1Page;
MenuPage Sensor2Page;
MenuPage Sensor3Page;
MenuPage Sensor4Page;
MenuPage Sensor5Page;
MenuPage Sensor6Page;

static const char *SensorNames[] = {
	"Light1",
	"Light2",
	"Temp",
	"Vref",
	"IntTemp",
	"RefInt",
	"Gray",
};

static void PrintSensorValue(uint8_t idx)
{
	float v = sensor_data[idx];
	int32_t v100 = (int32_t)(v * 100.0f);
	char sign = '+';
	if (v100 < 0) {
		sign = '-';
		v100 = -v100;
	}
	OLED_Printf(4, 20, OLED_6X8_HALF, (char *)"%s %c%ld.%02ld", (char *)SensorNames[idx], sign,
	           (long)(v100 / 100), (long)(v100 % 100));
}

static void Sensor0Aux(void) { PrintSensorValue(0); }
static void Sensor1Aux(void) { PrintSensorValue(1); }
static void Sensor2Aux(void) { PrintSensorValue(2); }
static void Sensor3Aux(void) { PrintSensorValue(3); }
static void Sensor4Aux(void) { PrintSensorValue(4); }
static void Sensor5Aux(void) { PrintSensorValue(5); }
static void Sensor6Aux(void) { PrintSensorValue(6); }

static MenuItem SensorDetailMenuItems[] = {
	{.General_item_text = "[Back]", .General_callback = OLED_UI_Back, .General_SubMenuPage = NULL, .List_BoolRadioBox = NULL},
	{.General_item_text = NULL},
};

static MenuItem SensorMenuItems[] = {
	{.General_item_text = "Light1", .General_callback = NULL, .General_SubMenuPage = &Sensor0Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "Light2", .General_callback = NULL, .General_SubMenuPage = &Sensor1Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "Temp", .General_callback = NULL, .General_SubMenuPage = &Sensor2Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "Vref", .General_callback = NULL, .General_SubMenuPage = &Sensor3Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "IntTemp", .General_callback = NULL, .General_SubMenuPage = &Sensor4Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "RefInt", .General_callback = NULL, .General_SubMenuPage = &Sensor5Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "Gray", .General_callback = NULL, .General_SubMenuPage = &Sensor6Page, .List_BoolRadioBox = NULL},
	{.General_item_text = "[Back]", .General_callback = OLED_UI_Back, .General_SubMenuPage = NULL, .List_BoolRadioBox = NULL},
	{.General_item_text = NULL},
};

MenuItem DisplayMenuItems[] = {
	{.General_item_text = "Sensor", .General_callback = NULL, .General_SubMenuPage = &SensorMenuPage, .List_BoolRadioBox = NULL},
	{.General_item_text = "DarkMode", .General_callback = NULL, .General_SubMenuPage = NULL, .List_BoolRadioBox = &ColorMode},
	{.General_item_text = "ShowFPS", .General_callback = NULL, .General_SubMenuPage = NULL, .List_BoolRadioBox = &OLED_UI_ShowFps},
	{.General_item_text = "[Back]", .General_callback = OLED_UI_Back, .General_SubMenuPage = NULL, .List_BoolRadioBox = NULL},
	{.General_item_text = NULL},
};

MenuItem MainMenuItems[] = {
	{.General_item_text = "Display", .General_callback = NULL, .General_SubMenuPage = &DisplayMenuPage, .List_BoolRadioBox = NULL},
	{.General_item_text = "About", .General_callback = ShowAboutWindow, .General_SubMenuPage = NULL, .List_BoolRadioBox = NULL},
	{.General_item_text = NULL},
};

MenuPage MainMenuPage = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = NULL,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = NULL,
	.General_MenuItems = MainMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage DisplayMenuPage = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &MainMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = NULL,
	.General_MenuItems = DisplayMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage SensorMenuPage = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &DisplayMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = NULL,
	.General_MenuItems = SensorMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor0Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor0Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor1Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor1Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor2Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor2Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor3Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor3Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor4Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor4Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor5Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor5Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

MenuPage Sensor6Page = {
	.General_MenuType = MENU_TYPE_LIST,
	.General_CursorStyle = REVERSE_ROUNDRECTANGLE,
	.General_FontSize = OLED_UI_FONT_8,
	.General_ParentMenuPage = &SensorMenuPage,
	.General_LineSpace = 4,
	.General_MoveStyle = UNLINEAR,
	.General_MovingSpeed = 10,
	.General_ShowAuxiliaryFunction = Sensor6Aux,
	.General_MenuItems = SensorDetailMenuItems,
	.List_MenuArea = {0, 0, 128, 64},
	.List_IfDrawFrame = false,
	.List_IfDrawLinePerfix = true,
	.List_StartPointX = 4,
	.List_StartPointY = 2,
};

