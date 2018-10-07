#include <stdbool.h>
#include "stm32f10x_conf.h"
#include "user_conf.h"
#include "io_buf_ctrl.h"
#include "key_led.h"
#include "key_led_table.h"

u8 g_u8KeyTable[KEY_Y_CNT][KEY_X_CNT] = 
{
	{
		_Key_Caption_Text1, _Key_Caption_Text2, _Key_Caption_Text3, _Key_Caption_Text4, 
		_Key_Caption_Lock, _Key_Video_Ctrl_Live, _Key_Cam_Ctrl_Wide, _Key_Video_Ctrl_LiveStop,
	}, /* 1 */
	
	{
		_Key_Switch_Video1, _Key_Switch_Video2, _Key_Switch_Video3, _Key_Switch_Video4,
		_Key_Switch_Video5, _Key_Switch_Video6, _Key_Switch_Cut, _Key_Cam_Ctrl_Tele,
	}, /* 2 */
	
	{
		_Key_Caption_Pic1, _Key_Caption_Pic2, _Key_Caption_Pic3, _Key_Caption_Pic4,
		_Key_Caption_EN, _Key_Video_Ctrl_Record, _Key_Video_Ctrl_RecordPause, _Key_Video_Ctrl_RecordStop,
	}, /* 3 */
	
	{
		_Key_Switch_Video_Bak1, _Key_Switch_Video_Bak2, _Key_Switch_Video_Bak3, _Key_Switch_Video_Bak4,
		_Key_Switch_Video_Bak5, _Key_Switch_Video_Bak6, _Key_Switch_Mix, _Key_Switch_Tack,
	}, /* 4 */
			  
	{
		_Key_Cam_Ctrl_Set, _Key_Cam_Ctrl_Select_Bak, _Key_Cam_Ctrl_Call, _Key_Cam_Ctrl_Wide_Most,
		_Key_Cam_Ctrl_Noraml_Most, _Key_Cam_Ctrl_Tele_Most, _Key_Global_Auto, _Key_Trace_Auto, 
	}, /* 5 */
	
	{
		_Key_Switch_Effict1, _Key_Switch_Effict2, _Key_Switch_Effict3, _Key_Switch_Effict4,
		_Key_Switch_Effict5, _Key_Switch_Effict6, _Key_Switch_Effict7, _Key_Switch_Effict8,
	}, /* 6 */
	
	{
		_Key_Switch_Effict9, _Key_Switch_Effict0, _Key_Cam_Ctrl_Num3, _Key_Cam_Ctrl_Num5,
		_Key_Cam_Ctrl_Num4, _Key_Cam_Ctrl_Num2, _Key_Cam_Ctrl_Num6, _Key_Cam_Ctrl_Num8,
	}, /* 7 */
	
	{
		_Key_Cam_Ctrl_Num7, _Key_Cam_Ctrl_Num1, _Key_Cam_Ctrl_Num9, _Key_Cam_Ctrl_Num0,
		_Key_Cam_Ctrl_Select, _Key_Cam_Ctrl_Speed, _Key_Switch_Time, 0,
	}, /* 8 */
	

};

 const u16 g_u16PushRodLoc[24] = 
{
	_Led_Push_Rod0,
	_Led_Push_Rod1,
	_Led_Push_Rod2,
	_Led_Push_Rod3,
	_Led_Push_Rod4,
	_Led_Push_Rod5,
	_Led_Push_Rod6,
	_Led_Push_Rod7,
	_Led_Push_Rod8,
	_Led_Push_Rod9,
	_Led_Push_Rod10,
	_Led_Push_Rod11,
	_Led_Push_Rod12,
	_Led_Push_Rod13,
	_Led_Push_Rod14,
	_Led_Push_Rod15,
	_Led_Push_Rod16,
	_Led_Push_Rod17,
	_Led_Push_Rod18,
	_Led_Push_Rod19,
	_Led_Push_Rod20,
	_Led_Push_Rod21,
	_Led_Push_Rod22,
	_Led_Push_Rod23,
};


const u16 g_u16CaptionTextLoc[4] =
{
	_Led_Caption_Text1,
	_Led_Caption_Text2,
	_Led_Caption_Text3,
	_Led_Caption_Text4,
		
};
const u16 g_u16CaptionPicLoc[4] =
{
	_Led_Caption_Pic1,
	_Led_Caption_Pic2,
	_Led_Caption_Pic3,
	_Led_Caption_Pic4,
};
const u16 g_u16EffictNumLoc[20] = 	/* 高十个元素, 为红灯 */
{
	
	_Led_Switch_Effict0_Green,
	_Led_Switch_Effict1_Green,
	_Led_Switch_Effict2_Green,
	_Led_Switch_Effict3_Green,
	_Led_Switch_Effict4_Green,
	_Led_Switch_Effict5_Green,
	_Led_Switch_Effict6_Green,
	_Led_Switch_Effict7_Green,
	_Led_Switch_Effict8_Green,
	_Led_Switch_Effict9_Green,

	_Led_Switch_Effic_0_Red,
	_Led_Switch_Effict1_Red,
	_Led_Switch_Effict2_Red,
	_Led_Switch_Effict3_Red,
	_Led_Switch_Effict4_Red,
	_Led_Switch_Effict5_Red,
	_Led_Switch_Effict6_Red,
	_Led_Switch_Effict7_Red,
	_Led_Switch_Effict8_Red,
	_Led_Switch_Effict9_Red,
};


const u16 g_u16SwitchVideoLoc[6] = 
{
	_Led_Switch_Video1,
	_Led_Switch_Video2,
	_Led_Switch_Video3,
	_Led_Switch_Video4,
	_Led_Switch_Video5,
	_Led_Switch_Video6,
};
const u16 g_u16SwitchVideoBackLoc[6] = 
{
	_Led_Switch_Video_Bak1,
	_Led_Switch_Video_Bak2,
	_Led_Switch_Video_Bak3,
	_Led_Switch_Video_Bak4,
	_Led_Switch_Video_Bak5,
	_Led_Switch_Video_Bak6,
};


/* dp, g, f, e, d, c, b, a */
const u8 g_u8LED7Code[] = 
{
	0x3F,		// 0
	0x06,		// 1
	0x5B,		// 2
	0x4F,		// 3
	0x66,		// 4
	0x6D,		// 5
	0x7D,		// 6
	0x07,		// 7
	0x7F,		// 8
	0x6F,		// 9
	0x77,		// A
	0x7C,		// B
	0x39,		// C
	0x5E,		// D
	0x79,		// E
	0x71,		// F
	0x40,		// -
};
 
const u16 g_u16SpeedNixieTubeLoc[16] = /* 高十个元素,在后8个字节*/
{
	 _Led_Speed_Unit_a,
	 _Led_Speed_Unit_b,
	 _Led_Speed_Unit_c,
	 _Led_Speed_Unit_d,
	 _Led_Speed_Unit_e,
	 _Led_Speed_Unit_f,
	 _Led_Speed_Unit_g,
	 _Led_Speed_Unit_dp,
	 
	 _Led_Speed_Ten_a,
	 _Led_Speed_Ten_b,
	 _Led_Speed_Ten_c,
	 _Led_Speed_Ten_d,
	 _Led_Speed_Ten_e,
	 _Led_Speed_Ten_f,
	 _Led_Speed_Ten_g,
	 _Led_Speed_Ten_dp,
};


const u16 g_u16TimeNixieTubeLoc[16] = /* 高十个元素,在后8个字节*/
{
	_Led_Time_Unit_a,
	_Led_Time_Unit_b,
	_Led_Time_Unit_c,
	_Led_Time_Unit_d,
	_Led_Time_Unit_e,
	_Led_Time_Unit_f,
	_Led_Time_Unit_g,
	_Led_Time_Unit_dp,
	
	_Led_Time_Ten_a,
	_Led_Time_Ten_b,
	_Led_Time_Ten_c,
	_Led_Time_Ten_d,
	_Led_Time_Ten_e,
	_Led_Time_Ten_f,
	_Led_Time_Ten_g,
	_Led_Time_Ten_dp,
};

const u16 g_u16CamAddrLoc[6] = 
{
	_Led_Cam_Ctrl_Cam1,
	_Led_Cam_Ctrl_Cam2,
	_Led_Cam_Ctrl_Cam3,
	_Led_Cam_Ctrl_Cam4,
	_Led_Cam_Ctrl_Cam5,
	_Led_Cam_Ctrl_Cam6,
};

const u16 g_u16ZoomScenceLoc[3] = 
{
	_Led_Cam_Ctrl_Wide_Most,
	_Led_Cam_Ctrl_Noraml_Most,
	_Led_Cam_Ctrl_Tele_Most,
};

const u16 g_u16PresetNumLoc[20] = 	/* 高十个元素, 为红灯 */
{
	_Led_Cam_Ctrl_Num0_Green,
	_Led_Cam_Ctrl_Num1_Green,
	_Led_Cam_Ctrl_Num2_Green,
	_Led_Cam_Ctrl_Num3_Green,
	_Led_Cam_Ctrl_Num4_Green,
	_Led_Cam_Ctrl_Num5_Green,
	_Led_Cam_Ctrl_Num6_Green,
	_Led_Cam_Ctrl_Num7_Green,
	_Led_Cam_Ctrl_Num8_Green,
	_Led_Cam_Ctrl_Num9_Green,
	
	_Led_Cam_Ctrl_Num0_Red,
	_Led_Cam_Ctrl_Num1_Red,
	_Led_Cam_Ctrl_Num2_Red,
	_Led_Cam_Ctrl_Num3_Red,
	_Led_Cam_Ctrl_Num4_Red,
	_Led_Cam_Ctrl_Num5_Red,
	_Led_Cam_Ctrl_Num6_Red,
	_Led_Cam_Ctrl_Num7_Red,
	_Led_Cam_Ctrl_Num8_Red,
	_Led_Cam_Ctrl_Num9_Red,
};

