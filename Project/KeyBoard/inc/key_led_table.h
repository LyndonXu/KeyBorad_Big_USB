#ifndef _KEY_LED_TABLE_H_
#define _KEY_LED_TABLE_H_
#include "stm32f10x_conf.h"
#include "user_conf.h"

#define LOC(x, y) 		((((x - 1) & 0xFF) << 8) | ((y - 1) & 0xFF))  	/* 高8 位X 的位置，低8 位Y 的位置 */
#define GET_X(loc)		((loc >> 8) & 0xFF)
#define GET_Y(loc)		(loc & 0xFF)
#define GET_XY(loc) 	GET_X(loc), GET_Y(loc)

extern u8 g_u8KeyTable[KEY_Y_CNT][KEY_X_CNT];
enum 
{
	_Key_Global_Auto = 1,

	_Key_Trace_Auto, 

	_Key_Switch_Time,		/* 特殊性, 没有按下抬起 */

	_Key_Cam_Ctrl_Speed,	/* 特殊性, 没有按下抬起 */

	_Key_Cam_Ctrl_Set,	/* 特殊性, 没有按下抬起 */
	
	_Key_Caption_Lock,
	_Key_Caption_Text1,
	_Key_Caption_Text2,
	_Key_Caption_Text3,
	_Key_Caption_Text4,

	_Key_Caption_EN,
	_Key_Caption_Pic1,
	_Key_Caption_Pic2,
	_Key_Caption_Pic3,
	_Key_Caption_Pic4,

	_Key_Caption_Reserved,



	_Key_Switch_Tack,
	
	_Key_Switch_Video1,
	_Key_Switch_Video2,
	_Key_Switch_Video3,
	_Key_Switch_Video4,
	_Key_Switch_Video5,
	_Key_Switch_Video6,

	_Key_Switch_Video_Bak1,
	_Key_Switch_Video_Bak2,
	_Key_Switch_Video_Bak3,
	_Key_Switch_Video_Bak4,
	_Key_Switch_Video_Bak5,
	_Key_Switch_Video_Bak6,

 	_Key_Switch_Effict0,
 	_Key_Switch_Effict1,
	_Key_Switch_Effict2,
	_Key_Switch_Effict3,
	_Key_Switch_Effict4,
	_Key_Switch_Effict5,
	_Key_Switch_Effict6,
	_Key_Switch_Effict7,
	_Key_Switch_Effict8,
	_Key_Switch_Effict9,

	_Key_Switch_Cut,

	_Key_Switch_Mix,

	_Key_Switch_Reserved,



	_Key_Video_Ctrl_Live,
	_Key_Video_Ctrl_LiveStop,

	_Key_Video_Ctrl_Record,
	_Key_Video_Ctrl_RecordPause,
	_Key_Video_Ctrl_RecordStop,
	_Key_Video_Ctrl_Reserved,


	
	_Key_Cam_Ctrl_Num0,
	_Key_Cam_Ctrl_Num1,
	_Key_Cam_Ctrl_Num2,
	_Key_Cam_Ctrl_Num3,
	_Key_Cam_Ctrl_Num4,
	_Key_Cam_Ctrl_Num5,
	_Key_Cam_Ctrl_Num6,
	_Key_Cam_Ctrl_Num7,
	_Key_Cam_Ctrl_Num8,
	_Key_Cam_Ctrl_Num9,

	_Key_Cam_Ctrl_Call,

	_Key_Cam_Ctrl_Wide_Most,
	_Key_Cam_Ctrl_Noraml_Most,
	_Key_Cam_Ctrl_Tele_Most,

	_Key_Cam_Ctrl_Tele,
	_Key_Cam_Ctrl_Wide,

	_Key_Cam_Ctrl_Select,
	_Key_Cam_Ctrl_Select_Bak,

	_Key_Cam_Ctrl_Reserved,

};


enum 
{
	_Led_Global_Auto = LOC(7, 5),
	_Led_Trace_Auto = LOC(8, 5), 
	_Led_Caption_Text1 = LOC(1, 1),
	_Led_Caption_Text2 = LOC(2, 1),
	_Led_Caption_Text3 = LOC(3, 1),
	_Led_Caption_Text4 = LOC(4, 1),
	_Led_Caption_Pic1 = LOC(1, 3),
	_Led_Caption_Pic2 = LOC(2, 3),
	
	_Led_Caption_Pic3 = LOC(3, 3),
	_Led_Caption_Pic4 = LOC(4, 3),
	_Led_Caption_Lock = LOC(5, 1),
	_Led_Caption_EN = LOC(5, 3),
	_Led_Switch_Video1 = LOC(1, 2),
	_Led_Switch_Video2 = LOC(2, 2),
	_Led_Switch_Video3 = LOC(3, 2),
	_Led_Switch_Video4 = LOC(4, 2),
	
	_Led_Switch_Video5 = LOC(5, 2),
	_Led_Switch_Video6 = LOC(6, 2),


	
	_Led_Switch_Video_Bak1 = LOC(1, 4),
	_Led_Switch_Video_Bak2 = LOC(2, 4),
	_Led_Switch_Video_Bak3 = LOC(3, 4),
	_Led_Switch_Video_Bak4 = LOC(4, 4),
	_Led_Switch_Video_Bak5 = LOC(5, 4),
	_Led_Switch_Video_Bak6 = LOC(6, 4),

	_Led_Switch_Cut = LOC(7, 2),
	_Led_Switch_Mix = LOC(7, 4),
	_Led_Switch_Tack = LOC(8, 4),

	_Led_Switch_Effict1_Red = LOC(1, 6),
	_Led_Switch_Effict2_Red = LOC(3, 6),
	_Led_Switch_Effict3_Red = LOC(5, 6),
	_Led_Switch_Effict4_Red = LOC(7, 6),
	_Led_Switch_Effict5_Red = LOC(1, 7),
	_Led_Switch_Effict6_Red = LOC(3, 7),
	_Led_Switch_Effict7_Red = LOC(5, 7),
	_Led_Switch_Effict8_Red = LOC(7, 7),
	_Led_Switch_Effict9_Red = LOC(1, 8),
	_Led_Switch_Effic_0_Red = LOC(3, 8),
	
	_Led_Switch_Effict1_Green = LOC(2, 6),
	_Led_Switch_Effict2_Green = LOC(4, 6),
	_Led_Switch_Effict3_Green = LOC(6, 6),
	_Led_Switch_Effict4_Green = LOC(8, 6),
	_Led_Switch_Effict5_Green = LOC(2, 7),
	_Led_Switch_Effict6_Green = LOC(4, 7),
	_Led_Switch_Effict7_Green = LOC(6, 7),
	_Led_Switch_Effict8_Green = LOC(8, 7),
	_Led_Switch_Effict9_Green = LOC(2, 8),
	_Led_Switch_Effict0_Green = LOC(4, 8),

	_Led_Push_Rod0 = LOC(1, 11),
	_Led_Push_Rod1 = LOC(2, 11),
	_Led_Push_Rod2 = LOC(3, 11),
	_Led_Push_Rod3 = LOC(4, 11),
	_Led_Push_Rod4 = LOC(5, 11),
	_Led_Push_Rod5 = LOC(6, 11),
	_Led_Push_Rod6 = LOC(7, 11),
	_Led_Push_Rod7 = LOC(8, 11),

	_Led_Push_Rod8 = LOC(1, 12),
	_Led_Push_Rod9 = LOC(2, 12),
	_Led_Push_Rod10 = LOC(3, 12),
	_Led_Push_Rod11 = LOC(4, 12),
	_Led_Push_Rod12 = LOC(5, 12),
	_Led_Push_Rod13 = LOC(6, 12),
	_Led_Push_Rod14 = LOC(7, 12),
	_Led_Push_Rod15 = LOC(8, 12),

	_Led_Push_Rod16 = LOC(1, 13),
	_Led_Push_Rod17 = LOC(2, 13),
	_Led_Push_Rod18 = LOC(3, 13),
	_Led_Push_Rod19 = LOC(4, 13),
	_Led_Push_Rod20 = LOC(5, 13),
	_Led_Push_Rod21 = LOC(6, 13),
	_Led_Push_Rod22 = LOC(7, 13),
	_Led_Push_Rod23 = LOC(8, 13),
	
	_Led_Time_Ten_a  = LOC(1, 16),
	_Led_Time_Ten_b  = LOC(2, 16),
	_Led_Time_Ten_c  = LOC(3, 16),
	_Led_Time_Ten_d  = LOC(4, 16),
	_Led_Time_Ten_e  = LOC(5, 16),
	_Led_Time_Ten_f  = LOC(6, 16),
	_Led_Time_Ten_g  = LOC(7, 16),
	_Led_Time_Ten_dp = LOC(8, 16),

	_Led_Time_Unit_a  = LOC(1, 15),
	_Led_Time_Unit_b  = LOC(2, 15),
	_Led_Time_Unit_c  = LOC(3, 15),
	_Led_Time_Unit_d  = LOC(4, 15),
	_Led_Time_Unit_e  = LOC(5, 15),
	_Led_Time_Unit_f  = LOC(6, 15),
	_Led_Time_Unit_g  = LOC(7, 15),
	_Led_Time_Unit_dp = LOC(8, 15),

	_Led_Video_Ctrl_Live = LOC(6, 1),
	_Led_Video_Ctrl_LiveStop = LOC(8, 1),
	_Led_Video_Ctrl_Record= LOC(6, 3),

	_Led_Video_Ctrl_RecordPause = LOC(7, 3),
	_Led_Video_Ctrl_RecordStop = LOC(8, 3),

	_Led_Cam_Ctrl_Num1_Red = LOC(3, 10),
	_Led_Cam_Ctrl_Num2_Red = LOC(3, 9),
	_Led_Cam_Ctrl_Num3_Red = LOC(5, 8),
	_Led_Cam_Ctrl_Num4_Red = LOC(1, 9),
	_Led_Cam_Ctrl_Num5_Red = LOC(7, 8),
	_Led_Cam_Ctrl_Num6_Red = LOC(5, 9),
	_Led_Cam_Ctrl_Num7_Red = LOC(1, 10),
	_Led_Cam_Ctrl_Num8_Red = LOC(7, 9),
	_Led_Cam_Ctrl_Num9_Red = LOC(5, 10),
	_Led_Cam_Ctrl_Num0_Red = LOC(7, 10),

	_Led_Cam_Ctrl_Num1_Green = LOC(4, 10),
	_Led_Cam_Ctrl_Num2_Green = LOC(4, 9),
	_Led_Cam_Ctrl_Num3_Green = LOC(6, 8),
	_Led_Cam_Ctrl_Num4_Green = LOC(2, 9),
	_Led_Cam_Ctrl_Num5_Green = LOC(8, 8),
	_Led_Cam_Ctrl_Num6_Green = LOC(6, 9),
	_Led_Cam_Ctrl_Num7_Green = LOC(2, 10),
	_Led_Cam_Ctrl_Num8_Green = LOC(8, 9),
	_Led_Cam_Ctrl_Num9_Green = LOC(6, 10),
	_Led_Cam_Ctrl_Num0_Green = LOC(8, 10),




	_Led_Cam_Ctrl_Call = LOC(3, 5),
	_Led_Cam_Ctrl_Set = LOC(1, 5),

	_Led_Cam_Ctrl_Tele_Most = LOC(6, 5),
	_Led_Cam_Ctrl_Noraml_Most = LOC(5, 5),
	_Led_Cam_Ctrl_Wide_Most = LOC(4, 5),

	_Led_Cam_Ctrl_Tele = LOC(8, 2),
	_Led_Cam_Ctrl_Wide = LOC(7, 1),

	_Led_Cam_Ctrl_Select_Bak = LOC(2, 5),

	_Led_Cam_Ctrl_Cam1 = LOC(1, 14),
	_Led_Cam_Ctrl_Cam2 = LOC(2, 14),
	_Led_Cam_Ctrl_Cam3 = LOC(3, 14),
	_Led_Cam_Ctrl_Cam4 = LOC(4, 14),
	_Led_Cam_Ctrl_Cam5 = LOC(5, 14),
	_Led_Cam_Ctrl_Cam6 = LOC(6, 14),

	_Led_Speed_Ten_a  = LOC(1, 18),
	_Led_Speed_Ten_b  = LOC(2, 18),
	_Led_Speed_Ten_c  = LOC(3, 18),
	_Led_Speed_Ten_d  = LOC(4, 18),
	_Led_Speed_Ten_e  = LOC(5, 18),
	_Led_Speed_Ten_f  = LOC(6, 18),
	_Led_Speed_Ten_g  = LOC(7, 18),
	_Led_Speed_Ten_dp = LOC(8, 18),
	
	_Led_Speed_Unit_a = LOC(1, 17), 
	_Led_Speed_Unit_b = LOC(2, 17), 
	_Led_Speed_Unit_c = LOC(3, 17), 
	_Led_Speed_Unit_d = LOC(4, 17), 
	_Led_Speed_Unit_e = LOC(5, 17), 
	_Led_Speed_Unit_f = LOC(6, 17), 
	_Led_Speed_Unit_g = LOC(7, 17), 
	_Led_Speed_Unit_dp= LOC(8, 17), 

};

extern const u16 g_u16PushRodLoc[24];
			 
extern const u16 g_u16CaptionTextLoc[4];
extern const u16 g_u16CaptionPicLoc[4];
			 
extern const u16 g_u16EffictNumLoc[20];
extern const u16 g_u16SwitchVideoLoc[6];
extern const u16 g_u16SwitchVideoBackLoc[6];
extern const u8 g_u8LED7Code[];
extern const u16 g_u16SpeedNixieTubeLoc[16];
extern const u16 g_u16TimeNixieTubeLoc[16];
extern const u16 g_u16PresetNumLoc[20];	/* 高十个元素, 为红灯 */
extern const u16 g_u16CamAddrLoc[6];
extern const u16 g_u16ZoomScenceLoc[3];

#endif

