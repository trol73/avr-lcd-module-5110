/* 
 * File:   api_codes.h
 * Author: Trol
 *
 * Created on 27 марта 2016 г., 22:15
 */

#ifndef _API_CODES_H
#define _API_CODES_H

#define CMD_SYNC					0			// 1 bytes

#define LCD_SET_CONTRAST		1			// 1 bytes
#define LCD_CLEAR					2			// 0 bytes
#define DRAW_PIXEL_1				3			// 2 bytes
#define DRAW_PIXEL_0				4			// 2 bytes
#define INVERT_PIXEL				5			// 2 bytes
#define DRAW_LINE_1				6			// 4 bytes
#define DRAW_LINE_0				7			// 4 bytes
#define FILL_RECT_1				8			// 4 bytes
#define FILL_RECT_0				9			// 4 bytes
#define DRAW_RECT_1				10			// 4 bytes
#define DRAW_RECT_0				11			// 4 bytes
#define DRAW_CIRCLE_1			12			// 3 bytes
#define DRAW_CIRCLE_0			13			// 3 bytes
#define FILL_CIRCLE_1			14			// 3 bytes
#define FILL_CIRCLE_0			15			// 3 bytes
#define INVERT_AREA				16			// 4 bytes
#define DRAW_CHAR_XY				17			// 3 bytes
#define DRAW_CHAR					18			// 1 bytes
#define DRAW_STRING_XY			19			// variable
#define DRAW_STRING				20			// variable
//#define DRAW_BYTE_XY				21			// 3 bytes
//#define DRAW_BYTE					22			// 1 bytes
//#define DRAW_WORD_XY				23			// 4 bytes
//#define DRAW_WORD					24			// 2 bytes

#define LCD_WRITE					21			// 0 bytes
#define READ_KEYBOARD			22			// 0 bytes
#define SET_HIGHLIGHT			23			// 2 bytes
#define BEEP						24			// 3 bytes

#define DRAW_CENTERED_STRING	25			// variable
#define SET_STRING_INTERVAL	26			// 1 bytes
#define DRAW_CHAR_XY_OVER		27
#define DRAW_CHAR_OVER			28
#define SET_KEYBOARD_BEEP		29			// 1 bytes


#define API_MAX_CODE				29


#endif	// _API_CODES_H

