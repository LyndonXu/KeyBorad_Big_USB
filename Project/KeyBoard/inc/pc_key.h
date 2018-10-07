#ifndef _PC_KEY_H_
#define _PC_KEY_H_
#include "IOCtrl.h"

#define PC_KEY_F1			0x3A
#define PC_KEY_F2			0x3B
#define PC_KEY_F3			0x3C
#define PC_KEY_F4			0x3D
#define PC_KEY_F5			0x3E
#define PC_KEY_F6			0x3f
#define PC_KEY_F7			0x40
#define PC_KEY_F8			0x41
#define PC_KEY_F9			0x42
#define PC_KEY_F10			0x43
#define PC_KEY_F11			0x44
#define PC_KEY_F12			0x45

#define PC_KEY_1			0x1E
#define PC_KEY_2			0x1F
#define PC_KEY_3			0x20
#define PC_KEY_4			0x21
#define PC_KEY_5			0x22
#define PC_KEY_6			0x23
#define PC_KEY_7			0x24
#define PC_KEY_8			0x25
#define PC_KEY_9			0x26
#define PC_KEY_0			0x27

#define PC_KEY_A			0x04
#define PC_KEY_B			0x05
#define PC_KEY_C			0x06
#define PC_KEY_D			0x07
#define PC_KEY_E			0x08
#define PC_KEY_F			0x09
#define PC_KEY_G			0x0A
#define PC_KEY_H			0x0B
#define PC_KEY_I			0x0C
#define PC_KEY_J			0x0D
#define PC_KEY_K			0x0E
#define PC_KEY_L			0x0F
#define PC_KEY_M			0x10
#define PC_KEY_N			0x11
#define PC_KEY_O			0x12
#define PC_KEY_P			0x13
#define PC_KEY_Q			0x14
#define PC_KEY_R			0x15
#define PC_KEY_S			0x16
#define PC_KEY_T			0x17
#define PC_KEY_U			0x18
#define PC_KEY_V			0x19
#define PC_KEY_W			0x1A
#define PC_KEY_X			0x1B
#define PC_KEY_Y			0x1C
#define PC_KEY_Z			0x1D


#define PC_KEY_PRINT		0x46
#define PC_KEY_PAUSE		0x48
#define PC_KEY_INSERT		0x49
#define PC_KEY_HOME			0x4A
#define PC_KEY_PGUP			0x4B
#define PC_KEY_DEL			0x4C
#define PC_KEY_END			0x4D
#define PC_KEY_PGDN			0x4E
#define PC_KEY_RIGHT		0x4F
#define PC_KEY_LEFT			0x50
#define PC_KEY_DOWN			0x51
#define PC_KEY_UP			0x52
#define PC_KEY_NUMLOCK		0x53


#define PC_KEY_ENTER		0x28
#define PC_KEY_ESC			0x29
#define PC_KEY_BACKSPACE	0x2A
#define PC_KEY_TAB			0x2B
#define PC_KEY_SPACE		0x2C
#define PC_KEY_MINUS		0x2D	/* - _ */
#define PC_KEY_PLUSE		0x2E	/* + = */
#define PC_KEY_LBRACKETS	0x2F	/* [ { */
#define PC_KEY_RBRACKETS	0x30	/* ] } */
#define PC_KEY_BACKSLASH	0x31	/* \ | */

#define PC_KEY_SEMICOLON	0x33	/* ; : */
#define PC_KEY_QUOTATION	0x34	/* ' " */
#define PC_KEY_TILDE		0x35	/* ~ ` */
#define PC_KEY_COMMA		0x36	/* , < */
#define PC_KEY_PERIOD		0x37	/* . > */
#define PC_KEY_SLASH		0x38	/* / ? */
#define PC_KEY_CAPSLOCK		0x39	/* caps lock */


#define PC_KEY_DIVIDE		0x54	/* / */
#define PC_KEY_MULTIPLY		0x55	/* * */
#define PC_KEY_ONLY_MINUS	0x56	/* - */
#define PC_KEY_ONLY_PLUSE	0x57	/* + */

#define PC_KEY_1_END		0x59
#define PC_KEY_2_DOWN		0x5A
#define PC_KEY_3_PGDN		0x5B
#define PC_KEY_4_LEFT		0x5C
#define PC_KEY_5_LITTLE		0x5D
#define PC_KEY_6_RIGHT		0x5E
#define PC_KEY_7_HOME		0x5F
#define PC_KEY_8_UP			0x60
#define PC_KEY_9_PGUP		0x61
#define PC_KEY_0_INSERT		0x62


#define PC_KEY_LCTRL		0xE0
#define PC_KEY_LSHIFT		0xE1
#define PC_KEY_LALT			0xE2
#define PC_KEY_LGUI			0xE3
#define PC_KEY_RCTRL		0xE4
#define PC_KEY_RSHIFT		0xE5
#define PC_KEY_RALT			0xE6

#define PC_KEY_MENU			0x65

#define PC_MOUSE_LEFT		0xF0
#define PC_MOUSE_RIGHT		0xF1

bool PCKeyProcess(StIOFIFO *pFIFO);
void TouchedOffPCKeyStopCmd(void);
void FlushPCKeyStopCmd(void);
void FlushPresetBlink(void);

#endif
