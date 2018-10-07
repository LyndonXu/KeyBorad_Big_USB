#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f10x_conf.h"
#include "user_conf.h"
#include "user_init.h"
#include "user_api.h"
#include "app_port.h"
#include "IOCtrl.h"
#include "io_buf_ctrl.h"
	
#include "key_led.h"
#include "adc_ctrl.h"
#include "code_switch.h"
#include "key_led_ctrl.h"
#include "key_led_table.h"
#include "protocol.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"

#include "pc_key.h"

const static u8 c_s_u8PCKeyValue[] =  
{
	0,
	
	PC_KEY_T,				//_Key_Global_Auto = 1,

	PC_KEY_U,				//	_Key_Trace_Auto, 

	0,						//	_Key_Switch_Time,		/* 特殊性, 没有按下抬起 */

	0,						//	_Key_Cam_Ctrl_Speed,	/* 特殊性, 没有按下抬起 */

	PC_KEY_ONLY_MINUS,			//	_Key_Cam_Ctrl_Set,	/* 特殊性, 没有按下抬起 */
		//	
	PC_KEY_F5,	//	_Key_Caption_Lock,
	PC_KEY_F1,	//	_Key_Caption_Text1,
	PC_KEY_F2,	//	_Key_Caption_Text2,
	PC_KEY_F3,	//	_Key_Caption_Text3,
	PC_KEY_F4,	//	_Key_Caption_Text4,

	PC_KEY_F10,	//	_Key_Caption_EN,
	PC_KEY_F6,	//	_Key_Caption_Pic1,
	PC_KEY_F7,	//	_Key_Caption_Pic2,
	PC_KEY_F8,	//	_Key_Caption_Pic3,
	PC_KEY_F9,	//	_Key_Caption_Pic4,

	0,			//	_Key_Caption_Reserved,



	PC_KEY_P,	//	_Key_Switch_Tack,

	PC_KEY_1,	//	_Key_Switch_Video1,
	PC_KEY_2,	//	_Key_Switch_Video2,
	PC_KEY_3,	//	_Key_Switch_Video3,
	PC_KEY_4,	//	_Key_Switch_Video4,
	PC_KEY_5,	//	_Key_Switch_Video5,
	PC_KEY_6,	//	_Key_Switch_Video6,

	PC_KEY_7,	//	_Key_Switch_Video_Bak1,
	PC_KEY_8,	//	_Key_Switch_Video_Bak2,
	PC_KEY_9,	//	_Key_Switch_Video_Bak3,
	PC_KEY_0,	//	_Key_Switch_Video_Bak4,
	PC_KEY_MINUS,	//	_Key_Switch_Video_Bak5,
	PC_KEY_PLUSE,	//	_Key_Switch_Video_Bak6,

	PC_KEY_N,	// 	_Key_Switch_Effict0,
	PC_KEY_D,	// 	_Key_Switch_Effict1,
	PC_KEY_E,	//	_Key_Switch_Effict2,
	PC_KEY_F,	//	_Key_Switch_Effict3,
	PC_KEY_G,	//	_Key_Switch_Effict4,
	PC_KEY_H,	//	_Key_Switch_Effict5,
	PC_KEY_I,	//	_Key_Switch_Effict6,
	PC_KEY_J,	//	_Key_Switch_Effict7,
	PC_KEY_K,	//	_Key_Switch_Effict8,
	PC_KEY_L,	//	_Key_Switch_Effict9,
           
	PC_KEY_M,	//	_Key_Switch_Cut,

	PC_KEY_O,	//	_Key_Switch_Mix,

	0,	//	_Key_Switch_Reserved,



	PC_KEY_F11,	//	_Key_Video_Ctrl_Live,
	PC_KEY_F12,	//	_Key_Video_Ctrl_LiveStop,

	PC_KEY_A,	//	_Key_Video_Ctrl_Record,
	PC_KEY_B,	//	_Key_Video_Ctrl_RecordPause,
	PC_KEY_C,	//	_Key_Video_Ctrl_RecordStop,
	0,	//	_Key_Video_Ctrl_Reserved,


	PC_KEY_0_INSERT,	//	_Key_Cam_Ctrl_Num0,
	PC_KEY_1_END	,	//	_Key_Cam_Ctrl_Num1,
	PC_KEY_2_DOWN	,	//	_Key_Cam_Ctrl_Num2,
	PC_KEY_3_PGDN	,	//	_Key_Cam_Ctrl_Num3,
	PC_KEY_4_LEFT	,	//	_Key_Cam_Ctrl_Num4,
	PC_KEY_5_LITTLE,	//	_Key_Cam_Ctrl_Num5,
	PC_KEY_6_RIGHT	,	//	_Key_Cam_Ctrl_Num6,
	PC_KEY_7_HOME	,	//	_Key_Cam_Ctrl_Num7,
	PC_KEY_8_UP		,	//	_Key_Cam_Ctrl_Num8,
	PC_KEY_9_PGUP	,	//	_Key_Cam_Ctrl_Num9,

	PC_KEY_ONLY_PLUSE,	//	_Key_Cam_Ctrl_Call,

	PC_KEY_COMMA,	//	_Key_Cam_Ctrl_Wide_Most,
	PC_KEY_PERIOD,	//	_Key_Cam_Ctrl_Noraml_Most,
	PC_KEY_SLASH,	//	_Key_Cam_Ctrl_Tele_Most,

	PC_KEY_S,	//	_Key_Cam_Ctrl_Tele,
	PC_KEY_R,	//	_Key_Cam_Ctrl_Wide,

	PC_KEY_Z,	//	_Key_Cam_Ctrl_Select,
	PC_KEY_Q,	//	_Key_Cam_Ctrl_Select_Bak,

	0,	//	_Key_Cam_Ctrl_Reserved,
};
static void TurnOffLedArray(const u16 *pLed, u16 u16Cnt)
{
	u16 i;
	for ( i = 0; i < u16Cnt; i++)
	{
		ChangeLedState(GET_XY(pLed[i]), false);
	}
}
static void ABusLedCtrl(u8 u8KeyValue)
{
	static u8 u8IndexBackUp = 0;
	const u16 u16Led[] = 
	{
		_Led_Switch_Video1, _Led_Switch_Video2, _Led_Switch_Video3, _Led_Switch_Video4,
		_Led_Switch_Video5, _Led_Switch_Video6
	};
	const u16 u16LedCam[] = 
	{
		_Led_Cam_Ctrl_Cam1, _Led_Cam_Ctrl_Cam2, _Led_Cam_Ctrl_Cam3, _Led_Cam_Ctrl_Cam4,
		_Led_Cam_Ctrl_Cam5, _Led_Cam_Ctrl_Cam6
	};
	if (u8KeyValue != 0xFF)
	{
		u8IndexBackUp = u8KeyValue - _Key_Switch_Video1;
	}
	else
	{
		u8IndexBackUp++;
		if (u8IndexBackUp >= 6)
		{
			u8IndexBackUp = 0;
		}
	}
	TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
	TurnOffLedArray(u16LedCam, sizeof(u16LedCam) / sizeof(u16));
	ChangeLedState(GET_XY(u16Led[u8IndexBackUp]), true);		
	ChangeLedState(GET_XY(u16LedCam[u8IndexBackUp]), true);		

}


typedef struct _tagStPresetMix
{
	u32 u32Preset;
	u32 u32LastPressTime;
}StPresetMix;

static StPresetMix s_stPresetMix = {~0, 0};

static void TurnOffZoomScence()
{
	const u16 u16Led[] = 
	{
		_Led_Cam_Ctrl_Wide_Most, _Led_Cam_Ctrl_Noraml_Most, _Led_Cam_Ctrl_Tele_Most
	};
	TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));	
}


static void TurnOffPreset(void)
{
	u32 i;
	for (i = 0; i < 20; i++)
	{
		ChangeLedState(GET_XY(g_u16PresetNumLoc[i]), false);
		ChangeLedBlinkState(GET_XY(g_u16PresetNumLoc[i]), false);
	}

}

static void TurnOnPreset(u8 u8Num, bool boIsBlink)
{
	u32 i;
	if (u8Num > 99)
	{
		return;
	}
	TurnOffPreset();
	
	i = u8Num / 10;
	if (i != 0)
	{
		if (boIsBlink)
		{
			ChangeLedBlinkState(GET_XY(g_u16PresetNumLoc[i + 10]), true);
		}
		else
		{
			ChangeLedState(GET_XY(g_u16PresetNumLoc[i + 10]), true);
		}
	}
	
	i = u8Num % 10;
	if (boIsBlink)
	{
		ChangeLedBlinkState(GET_XY(g_u16PresetNumLoc[i]), true);
	}
	else
	{
		ChangeLedState(GET_XY(g_u16PresetNumLoc[i]), true);
	}
	
}

static void PresetReset(void)
{
	//s_stPresetMix.u32LastPressTime = g_u32SysTickCnt;
	s_stPresetMix.u32Preset = ~0;	
}

static u8 GetMixPreset(void)
{
	return  s_stPresetMix.u32Preset;
}

void FlushPresetBlink(void)
{
	if (SysTimeDiff(s_stPresetMix.u32LastPressTime, g_u32SysTickCnt) > 5000)
	{
		if (s_stPresetMix.u32Preset != ~0)
		{
			PresetReset();
			TurnOffPreset();
		}
	}
}


static void PresetAddAnumber(u8 u8Num)
{
	if (u8Num >= 10)
	{
		return;
	}
	s_stPresetMix.u32LastPressTime = g_u32SysTickCnt;
	if (s_stPresetMix.u32Preset == ~0)
	{
		s_stPresetMix.u32Preset = u8Num;
	}
	else
	{
		s_stPresetMix.u32Preset = s_stPresetMix.u32Preset * 10 + u8Num;
		s_stPresetMix.u32Preset %= 100;
//		if (s_stPresetMix.u32Preset > 99)
//		{
//			s_stPresetMix.u32Preset = 99;
//		}
	}
//	if (s_stPresetMix.u32Preset == 0)
//	{
//		PresetReset();
//		TurnOffPreset();
//		return;
//	}
	
	TurnOnPreset(s_stPresetMix.u32Preset, true);
}


static void KeyBoardLedProcess(StKeyState *pState)
{
	u8 u8KeyValue = pState->u8KeyValue;
	bool boIsDown = pState->u8KeyState == KEY_DOWN ? true : false;
	if (!boIsDown)
	{
		if ((u8KeyValue != _Key_Switch_Cut) &&
			(u8KeyValue != _Key_Switch_Mix) &&
			(u8KeyValue != _Key_Switch_Tack) &&
			(u8KeyValue != _Key_Cam_Ctrl_Select_Bak) &&
			(u8KeyValue != _Key_Cam_Ctrl_Wide) &&
			(u8KeyValue != _Key_Cam_Ctrl_Tele) &&		
			(u8KeyValue != _Key_Cam_Ctrl_Set) && 
			(u8KeyValue != _Key_Cam_Ctrl_Call))
		{
			return;		
		}
	}
	
	if (u8KeyValue == _Key_Global_Auto)
	{
		static bool boIsLight = false;
		ChangeLedState(GET_XY(_Led_Global_Auto), !boIsLight);
		boIsLight = !boIsLight;
	}
	else if (u8KeyValue == _Key_Trace_Auto)
	{
		static bool boIsLight = false;
		ChangeLedState(GET_XY(_Led_Trace_Auto), !boIsLight);
		boIsLight = !boIsLight;
	}
	
	else if (u8KeyValue >= _Key_Caption_Text1 && u8KeyValue <= _Key_Caption_Text4)
	{
		const u16 u16Led[] = 
		{
			_Led_Caption_Text1, _Led_Caption_Text2, _Led_Caption_Text3, _Led_Caption_Text4
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Caption_Text1]), true);		
	}
	else if (u8KeyValue >= _Key_Caption_Pic1 && u8KeyValue <= _Key_Caption_Pic4)
	{
		const u16 u16Led[] = 
		{
			_Led_Caption_Pic1, _Led_Caption_Pic2, _Led_Caption_Pic3, _Led_Caption_Pic4
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Caption_Pic1]), true);		
	}
	
	else if (u8KeyValue == _Key_Caption_Lock)
	{
		static bool boIsLight = false;
		ChangeLedState(GET_XY(_Led_Caption_Lock), !boIsLight);
		boIsLight = !boIsLight;
	}
	else if (u8KeyValue == _Key_Caption_EN)
	{
		static bool boIsLight = false;
		ChangeLedState(GET_XY(_Led_Caption_EN), !boIsLight);
		boIsLight = !boIsLight;
	}

	else if (u8KeyValue >= _Key_Switch_Video1 && u8KeyValue <= _Key_Switch_Video6)
	{
		ABusLedCtrl(u8KeyValue);
	}
	else if (u8KeyValue >= _Key_Switch_Video_Bak1 && u8KeyValue <= _Key_Switch_Video_Bak6)
	{
		const u16 u16Led[] = 
		{
			_Led_Switch_Video_Bak1, _Led_Switch_Video_Bak2, _Led_Switch_Video_Bak3,
			_Led_Switch_Video_Bak4, _Led_Switch_Video_Bak5, _Led_Switch_Video_Bak6
		};

		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Switch_Video_Bak1]), true);		
	}

	else if (u8KeyValue >= _Key_Video_Ctrl_Live && u8KeyValue <= _Key_Video_Ctrl_LiveStop)
	{
		const u16 u16Led[] = 
		{
			_Led_Video_Ctrl_Live, _Led_Video_Ctrl_LiveStop
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Video_Ctrl_Live]), true);		
	}
	else if (u8KeyValue >= _Key_Video_Ctrl_Record && u8KeyValue <= _Key_Video_Ctrl_RecordStop)
	{
		const u16 u16Led[] = 
		{
			_Led_Video_Ctrl_Record, _Led_Video_Ctrl_RecordPause, _Led_Video_Ctrl_RecordStop
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Video_Ctrl_Record]), true);		
	}
	
	
	else if (u8KeyValue >= _Key_Switch_Effict0 && u8KeyValue <= _Key_Switch_Effict9)
	{
		const u16 u16Led[] = 
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
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Switch_Effict0]), true);		
	}
	else if (u8KeyValue == _Key_Switch_Cut)
	{
		ChangeLedState(GET_XY(_Led_Switch_Cut), boIsDown);
	}
	else if (u8KeyValue == _Key_Switch_Mix)
	{
		ChangeLedState(GET_XY(_Led_Switch_Mix), boIsDown);
	}
	else if (u8KeyValue == _Key_Switch_Tack)
	{
		ChangeLedState(GET_XY(_Led_Switch_Tack), boIsDown);
	}
	
	else if (u8KeyValue == _Key_Cam_Ctrl_Tele)
	{
		ChangeLedState(GET_XY(_Led_Cam_Ctrl_Tele), boIsDown);
		PresetReset();
		TurnOffPreset();
		TurnOffZoomScence();
	}
	else if (u8KeyValue == _Key_Cam_Ctrl_Wide)
	{
		ChangeLedState(GET_XY(_Led_Cam_Ctrl_Wide), boIsDown);
		PresetReset();
		TurnOffPreset();
		TurnOffZoomScence();
	}
	
	else if (u8KeyValue >= _Key_Cam_Ctrl_Wide_Most && u8KeyValue <= _Key_Cam_Ctrl_Tele_Most)
	{
		const u16 u16Led[] = 
		{
			_Led_Cam_Ctrl_Wide_Most, _Led_Cam_Ctrl_Noraml_Most, _Led_Cam_Ctrl_Tele_Most
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Cam_Ctrl_Wide_Most]), true);	
		PresetReset();
		TurnOffPreset();
	}
	
	
	else if (u8KeyValue >= _Key_Cam_Ctrl_Num0 && u8KeyValue <= _Key_Cam_Ctrl_Num9)
	{
#if 0
		const u16 u16Led[] = 
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
		};
		TurnOffLedArray(u16Led, sizeof(u16Led) / sizeof(u16));
		ChangeLedState(GET_XY(u16Led[u8KeyValue - _Key_Cam_Ctrl_Num0]), true);	
#else
		PresetAddAnumber(u8KeyValue - _Key_Cam_Ctrl_Num0);		
#endif
	}
	else if (u8KeyValue == _Key_Cam_Ctrl_Set)
	{
		ChangeLedState(GET_XY(_Led_Cam_Ctrl_Set), boIsDown);
		PresetReset();
		TurnOffPreset();
		TurnOffZoomScence();
	}
	else if (u8KeyValue == _Key_Cam_Ctrl_Call)
	{
		u8 u8Preset = GetMixPreset();
		PresetReset();
		TurnOnPreset(u8Preset, false);		
		TurnOffZoomScence();
		ChangeLedState(GET_XY(_Led_Cam_Ctrl_Call), boIsDown);
	}	
	
	else if (u8KeyValue == _Key_Cam_Ctrl_Select_Bak)
	{
		ChangeLedState(GET_XY(_Led_Cam_Ctrl_Select_Bak), boIsDown);	
		if (boIsDown)
		{
			ABusLedCtrl(0xFF);
		}
	}
	else if (u8KeyValue == _Key_Cam_Ctrl_Select)
	{
		ABusLedCtrl(0xFF);	
	}
	
}

static bool KeyBoardProcess(StKeyMixIn *pKeyIn)
{
	u32 i;
	bool boIsKeyChanged = false;
	
	for (i = 0; i < pKeyIn->u32Cnt; i++)
	{
		StKeyState *pState = pKeyIn->unKeyMixIn.stKeyState + i;
		if (pState->u8KeyState != KEY_KEEP)
		{
			boIsKeyChanged = true;
		}
	}
	if (!boIsKeyChanged)
	{
		return false;
	}
	
	if(bDeviceState == CONFIGURED)
	{
		u8 u8Buf[12] = {1, 0};
		u32 u32Cnt = 3;
		u32 u32KeyCnt = 0;
		u8 u8Value, u8Tmp;
				
		boIsKeyChanged = false;
		for (i = 0; i < pKeyIn->u32Cnt; i++)
		{
			StKeyState *pState = pKeyIn->unKeyMixIn.stKeyState + i;
			u8Tmp = pState->u8KeyValue; 
			if ((u8Tmp == 0) || (u8Tmp >= _Key_Cam_Ctrl_Reserved))
			{
				continue;
			}
			u8Value = c_s_u8PCKeyValue[u8Tmp];
			if (u8Value == 0)
			{
				continue;
			}
			u32KeyCnt++;
			if(pState->u8KeyState != KEY_UP)
			{
				if((u8Value >= PC_KEY_LCTRL) && (u8Value <= PC_KEY_RALT))
				{
					u8Buf[1] |= (1 << (u8Value - PC_KEY_LCTRL) );
				}
				else
				{
					u8Buf[u32Cnt++] = u8Value;
				}
				if (pState->u8KeyState == KEY_DOWN)
				{
					//ChangeLedState(c_u16Led[u8Tmp] >> 8, c_u16Led[u8Tmp] & 0xFF, true);
				}
			}
			else
			{
				//ChangeLedState(c_u16Led[u8Tmp] >> 8, c_u16Led[u8Tmp] & 0xFF, false);
			}
			KeyBoardLedProcess(pState);
		}
		if (u32KeyCnt != 0)
		{
			USB_SIL_Write(EP1_IN, u8Buf, 9);
			SetEPTxValid(ENDP1);
		}
	}
	
	if (!boIsKeyChanged)
	{
		return false;
	}
	
	return true;

}

static void TurnOFFAllPushRod(void)
{
	u32 i;
	for (i = 0; i < 24; i++)
	{
		u16 u16Loc = g_u16PushRodLoc[i];
		ChangeLedState(GET_XY(u16Loc), false);
	}
}

static void TurnOnPushRod(u8 u8Value)
{
	u16 u16Loc;
	if (u8Value > PUSH_ROD_MAX_VALUE)
	{
		u8Value = PUSH_ROD_MAX_VALUE;
	}
	
	TurnOFFAllPushRod();
	
	{
		u8Value /= PUSH_ROD_DIFF;
		u16Loc = g_u16PushRodLoc[u8Value];
		ChangeLedState(GET_XY(u16Loc), true);
	}
}

static bool PushPodProcess(StKeyMixIn *pKeyIn)
{
	static int s32States = 0;
	bool boNeedSend = false;
	u32 u32Value = pKeyIn->unKeyMixIn.u32PushRodValue;
	
	if (s32States == 0)
	{
		if (u32Value < 25)
		{
			s32States = 1;	/* low */
			boNeedSend = true;
		}
		else if (u32Value > 95)
		{
			s32States = 2;	/* high */
			boNeedSend = true;
		}
		else
		{
			boNeedSend = false;
		}
	}
	else if (s32States == 1)
	{
		if ((u32Value <= 10) || (u32Value > 40))
		{
			s32States = 4;
		}
		boNeedSend = true;
	}
	else if (s32States == 2)
	{
		if ((u32Value <= 80) || (u32Value > 110))
		{
			s32States = 3;
		}
		boNeedSend = true;		
	}
	else 
	{
		if (u32Value >= 50 && u32Value < 70)
		{
			s32States = 0;
		}
		boNeedSend = false;
	}
	
	if (boNeedSend && bDeviceState == CONFIGURED && s32States != 0)
	{
		u8 u8Buf[12] = {1, 0};
		u32 u32Cnt = 3;
		if (s32States == 1)
		{
			u8Buf[u32Cnt] = PC_KEY_RBRACKETS;
		}
		else if (s32States == 2)
		{
			u8Buf[u32Cnt] = PC_KEY_LBRACKETS;
		}
		
		USB_SIL_Write(EP1_IN, u8Buf, 9);
		SetEPTxValid(ENDP1);
	}
	
	if (u32Value >= 50 && u32Value < 70)
	{
		s32States = 0;
	}

	TurnOnPushRod(u32Value);

	
	return true;
}


static u32 s_u32KeySendStopState = 0;
static u32 s_u32KeySendStopTimeBegin = 0;
static u32 s_u32KeySendStopTimeAfter = 100;

void TouchedOffPCKeyStopCmd(void)
{
	s_u32KeySendStopTimeBegin = g_u32SysTickCnt;
	s_u32KeySendStopState = 1;
}

void FlushPCKeyStopCmd(void)
{
	if (s_u32KeySendStopState)
	{
		if (SysTimeDiff(s_u32KeySendStopTimeBegin, g_u32SysTickCnt) > 
			s_u32KeySendStopTimeAfter)
		{
			u8 u8Buf[12] = {1, 0};
	
			s_u32KeySendStopState = 0;
			
			if (bDeviceState == CONFIGURED)
			{
				USB_SIL_Write(EP1_IN, u8Buf, 9);
				SetEPTxValid(ENDP1);
			}
		}
	}
}

	
static void NixieTubeSetValue(u8 u8Index, u8 u8Value)
{
	u8 c_u8MaxValue[CODE_SWITCH_MAX] = {CODE_SWITCH1_MAX_VALUE, CODE_SWITCH2_MAX_VALUE};
	const u16 *c_pLed[CODE_SWITCH_MAX] = {g_u16TimeNixieTubeLoc, g_u16SpeedNixieTubeLoc};
	u8 u8Ten;
	u32 i;

	if (u8Index >= CODE_SWITCH_MAX)
	{
		return;
	}
	
	if (u8Value > (c_u8MaxValue[u8Index] - 1))
	{
		u8Value = g_u8LED7Code[16]; /* no dp */

		for (i = 0; i < 8; i++)
		{
			u16 u16Loc = c_pLed[u8Index][i];
			ChangeLedState(GET_XY(u16Loc), (u8Value >> i) & 0x01);
			u16Loc = c_pLed[u8Index][i + 8];
			ChangeLedState(GET_XY(u16Loc), (u8Value >> i) & 0x01);
		}
		return;
	}
	u8Ten = (u8Value / 10) % 10;
	u8Value %= 10;

	if (u8Ten > 0)
	{
		u8Ten = g_u8LED7Code[u8Ten]; /* no dp */
		for (i = 0; i < 8; i++)
		{
			u16 u16Loc = c_pLed[u8Index][i + 8];
			ChangeLedState(GET_XY(u16Loc), (u8Ten >> i) & 0x01);
		}
	}
	else
	{
		for (i = 0; i < 8; i++)
		{
			u16 u16Loc = c_pLed[u8Index][i + 8];
			ChangeLedState(GET_XY(u16Loc), false);
		}
	}
	u8Value = g_u8LED7Code[u8Value]; /* no dp */
	for (i = 0; i < 8; i++)
	{
		u16 u16Loc = c_pLed[u8Index][i];
		ChangeLedState(GET_XY(u16Loc), (u8Value >> i) & 0x01);
	}
}


static bool CodeSwitchProcess(StKeyMixIn *pKeyIn)
{
	u16 u16Index;
	u8 u8Buf[12] = {1, 0};
	u32 u32Cnt = 3;
	
	u16Index = pKeyIn->unKeyMixIn.stCodeSwitchState.u16Index;
	
	
	switch (u16Index)
	{
		case 0x00:
		{
			if (pKeyIn->unKeyMixIn.stCodeSwitchState.u16Dir)
			{
				u8Buf[u32Cnt] = PC_KEY_HOME;
			}
			else
			{
				u8Buf[u32Cnt] = PC_KEY_INSERT;
			}
			break;

		}
		case 0x01:
		{
			if (pKeyIn->unKeyMixIn.stCodeSwitchState.u16Dir)
			{
				u8Buf[u32Cnt] = PC_KEY_PGDN;
			}
			else
			{
				u8Buf[u32Cnt] = PC_KEY_PGUP;
			}
			break;
		}
		default:
			return false;

	}
	NixieTubeSetValue(u16Index, pKeyIn->unKeyMixIn.stCodeSwitchState.u16Cnt);
	
	if (bDeviceState == CONFIGURED)
	{
		USB_SIL_Write(EP1_IN, u8Buf, 9);
		SetEPTxValid(ENDP1);
		
		TouchedOffPCKeyStopCmd();
	}
	return true;
	
}

static bool RockProcess(StKeyMixIn *pKeyIn)
{
	enum
	{
		_TMP_UP = 1,	
		_TMP_DOWN,
		_TMP_LEFT,
		_TMP_RIGHT,
		_TMP_LU,		/* LU */		
		_TMP_LD,		/* LD */		
		_TMP_RU,		/* RU */		
		_TMP_RD,		/* RD */
		_TMP_TELE,		/* RU */		
		_TMP_WIDE,		/* RD */				
		
	};
	const u8 u8PCKeyValue[] = 
	{
		0,
		PC_KEY_UP,
		PC_KEY_DOWN,
		PC_KEY_LEFT,
		PC_KEY_RIGHT,
		PC_KEY_V,		/* LU */		
		PC_KEY_X,		/* LD */		
		PC_KEY_W,		/* RU */		
		PC_KEY_Y,		/* RD */		
		PC_KEY_MULTIPLY,	/* TELE */		
		PC_KEY_DIVIDE,		/* WIDE */		
	};
	static u8 u8OldPCKey = 0;
	static u8 u8ZoomOldPCKey = 0;

	
	u8 u8NewPCKey = 0;
	u8 u8ZoomNewPCKey = 0;
	u8 u8Dir = pKeyIn->unKeyMixIn.stRockState.u8RockDir << 1;

	PresetReset();
	TurnOffPreset();
	TurnOffZoomScence();


	if ((u8Dir & (PELCOD_LEFT | PELCOD_UP)) == (PELCOD_LEFT | PELCOD_UP))
	{
		u8NewPCKey = _TMP_LU;
	}
	else if ((u8Dir & (PELCOD_LEFT | PELCOD_DOWN)) == (PELCOD_LEFT | PELCOD_DOWN))
	{
		u8NewPCKey = _TMP_LD;
	}
	else if ((u8Dir & (PELCOD_RIGHT | PELCOD_UP)) == (PELCOD_RIGHT | PELCOD_UP))
	{
		u8NewPCKey = _TMP_RU;
	}
	else if ((u8Dir & (PELCOD_RIGHT | PELCOD_DOWN)) == (PELCOD_RIGHT | PELCOD_DOWN))
	{
		u8NewPCKey = _TMP_RD;
	}
	else if ((u8Dir & PELCOD_UP) == PELCOD_UP)
	{
		u8NewPCKey = _TMP_UP;
	}
	else if ((u8Dir & PELCOD_DOWN) == PELCOD_DOWN)
	{
		u8NewPCKey = _TMP_DOWN;
	}
	else if ((u8Dir & PELCOD_LEFT) == PELCOD_LEFT)
	{
		u8NewPCKey = _TMP_LEFT;
	}
	else if ((u8Dir & PELCOD_RIGHT) == PELCOD_RIGHT)
	{
		u8NewPCKey = _TMP_RIGHT;
	}
	else
	{
		u8NewPCKey = 0;
	}
	
	if ((u8Dir & PELCOD_ZOOM_TELE) == PELCOD_ZOOM_TELE)
	{
		u8ZoomNewPCKey = _TMP_TELE;
	}
	else if ((u8Dir & PELCOD_ZOOM_WIDE) == PELCOD_ZOOM_WIDE)
	{
		u8ZoomNewPCKey = _TMP_WIDE;
	}
	else
	{
		u8ZoomNewPCKey = 0;
	}
	
	{
		u8 u8Buf[12] = {1, 0};
		u32 u32Cnt = 3;
		bool boHasNew = false;
		if (u8NewPCKey != u8OldPCKey)
		{
			if (u8NewPCKey != 0)
			{
				u8Buf[u32Cnt++] = u8PCKeyValue[u8NewPCKey];
			}
			u8OldPCKey = u8NewPCKey;
			boHasNew = true;
		}
		if (u8ZoomNewPCKey != u8ZoomOldPCKey)
		{
			if (u8ZoomNewPCKey != 0)
			{
				u8Buf[u32Cnt++] = u8PCKeyValue[u8ZoomNewPCKey];
			}
			u8ZoomOldPCKey = u8ZoomNewPCKey;
			boHasNew = true;
		}
		if (boHasNew && (bDeviceState == CONFIGURED))
		{		
			USB_SIL_Write(EP1_IN, u8Buf, 9);
			SetEPTxValid(ENDP1);		
		}
	
	}
	return true;
}

static PFun_KeyProcess s_KeyProcessArr[_Key_Reserved] = 
{
	PushPodProcess, KeyBoardProcess, RockProcess,
	NULL, CodeSwitchProcess, 
};

bool PCKeyProcess(StIOFIFO *pFIFO)
{
	StKeyMixIn *pKeyIn = pFIFO->pData;
	
	if (pKeyIn->emKeyType >= _Key_Reserved)
	{
		return false;
	}
	if (s_KeyProcessArr[pKeyIn->emKeyType] != NULL)
	{
		return s_KeyProcessArr[pKeyIn->emKeyType](pKeyIn);	
	}
	return false;
}
