#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f10x_conf.h"
#include "user_conf.h"
#include "io_buf_ctrl.h"
#include "app_port.h"
#include "pwm.h"


#include "key_led.h"
#include "adc_ctrl.h"
#include "code_switch.h"
#include "key_led_ctrl.h"

#include "buzzer.h"

#include "user_init.h"
#include "user_api.h"

#include "key_led_table.h"

#include "protocol.h"
#include "message.h"
#include "message_2.h"
#include "flash_ctrl.h"
#include "extern_io_ctrl.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "pc_key.h"

int main()
{
	u32 u32MsgSentTime;
	u32 u32SyncCnt = 0;


	KeyBufInit();
	GlobalStateInit();
	
	PeripheralPinClkEnable();
	OpenSpecialGPIO();

	ReadSaveData();
	MessageUartInit();

#if 1	
	KeyLedInit();
	ChangeAllLedState(false);
	RockPushRodInit();
	CodeSwitchInit();
	BuzzerInit();
	
	
	//PWMCtrlInit();
#endif

	SysTickInit();
	
	Set_USBPort(DISABLE); 	//USB先断开
	u32MsgSentTime = g_u32SysTickCnt;
	while(SysTimeDiff(u32MsgSentTime, g_u32SysTickCnt) < 100);/* 延时100ms */
	Set_USBPort(ENABLE);	//USB再次连接
	
	USB_Interrupts_Config();

	Set_USBClock();

	USB_Init();	
	
	
	ChangeAllLedState(true);
	u32MsgSentTime = g_u32SysTickCnt;
	while(SysTimeDiff(u32MsgSentTime, g_u32SysTickCnt) < 1500);/* 延时1.5S */
	ChangeAllLedState(false);


	ChangeEncodeState();
	do
	{
		u32 u32Cnt = 0;	
		StIOFIFO *pFIFO;
		StKeyMixIn *pKeyIn;
		while(u32Cnt < 10)
		{
			
			u32Cnt++;
			u32MsgSentTime = g_u32SysTickCnt;
			while(SysTimeDiff(u32MsgSentTime, g_u32SysTickCnt) < 150);/* ??150ms */

			pFIFO = KeyBufGetBuf();
			if (pFIFO == NULL)
			{
				continue;
			}
			
			pKeyIn = (StKeyMixIn *)pFIFO->pData;

			if (pKeyIn == NULL)
			{
				KeyBufGetEnd(pFIFO);
				continue;
			}
			if (pKeyIn->emKeyType == _Key_Board)
			{
				u8 u8Value = pKeyIn->unKeyMixIn.stKeyState[0].u8KeyValue;
				if (u8Value == _Key_Caption_EN)
				{
					KeyBufGetEnd(pFIFO);
					RedressPushRodLimit();
					break;
				}
			}
			KeyBufGetEnd(pFIFO);
		}
		if (u32Cnt >= 10)
		{
			break;
		}
		
		ChangeAllLedState(false);
		u32MsgSentTime = g_u32SysTickCnt;
		while(SysTimeDiff(u32MsgSentTime, g_u32SysTickCnt) < 100);
		ChangeAllLedState(true);
	}while(0);

	u32SyncCnt = 0;

	while (u32SyncCnt < 3)
	{
		u8 u8Buf[PROTOCOL_YNA_ENCODE_LENGTH];
		u8 *pBuf = NULL;
		void *pMsgIn = NULL; 

		u32MsgSentTime = g_u32SysTickCnt;

		pBuf = u8Buf;
		memset(pBuf, 0, PROTOCOL_YNA_ENCODE_LENGTH);

		pBuf[_YNA_Sync] = 0xAA;
		pBuf[_YNA_Mix] = 0x07;
		pBuf[_YNA_Cmd] = 0xC0;

		YNAGetCheckSum(pBuf);
		CopyToUartMessage(pBuf, PROTOCOL_YNA_DECODE_LENGTH);
		
		pMsgIn = MessageUartFlush(false);
		if (pMsgIn != NULL)
		{
			MessageUartRelease(pMsgIn);
			break;
		}
		u32SyncCnt++;		
		while(SysTimeDiff(u32MsgSentTime, g_u32SysTickCnt) < 1000);/* 延时1S */
	}

	ChangeAllLedState(false);
	GlobalStateInit();
	do 
	{
		void *pFIFO = KeyBufGetBuf();
		if (pFIFO == NULL)
		{
			break;
		}
		KeyBufGetEnd(pFIFO);
	}while(1);

	while (1)
	{
		void *pMsgIn = MessageUartFlush(false);
		void *pKeyIn = KeyBufGetBuf();

		if (pKeyIn != NULL)
		{
			KeyProcess(pKeyIn);
			PCKeyProcess(pKeyIn);
		}	
		if (pMsgIn != NULL)
		{
			if (BaseCmdProcess(pMsgIn, &c_stUartIOTCB) != 0)			
			{
				PCEchoProcess(pMsgIn);
			}
		}
		KeyBufGetEnd(pKeyIn);				
		MessageUartRelease(pMsgIn);	
		
		FlushPCKeyStopCmd();
		FlushPresetBlink();
	}
}
