#include "commands.h"

#include "api_codes.h"

#include "lib/uart/uart.h"
#include "lib/glcd/glcd.h"

#include "beeper.h"
#include "keyboard.h"

#define CHAR_WIDTH		5
#define DELTA_Y			9

void_proc_t cmd_handlers[API_MAX_CODE+1];

extern volatile bool uartError;

uint8_t uartWaitNextChar();
uint8_t cmd_x, cmd_y, cmd_string_interval;


void cmd_sync() {
	uint8_t c = uartWaitNextChar();
	if (!uartError) {
		uart_putc(c);
	}
	uartError = false;
}

void cmd_lcdSetContrast() {
	uint8_t contrast = uartWaitNextChar();
	if (!uartError) {
		glcd_set_contrast(contrast);
	}
}

void cmd_lcdClear() {
	glcd_clear_buffer();
	cmd_string_interval = 1;
	cmd_x = 0;
	cmd_y = 0;
}

void cmd_drawPixel_1() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	if (!uartError) {
		glcd_set_pixel(x, y, 1);
	}
}

void cmd_drawPixel_0() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	if (!uartError) {
		glcd_set_pixel(x, y, 0);
	}
}

void cmd_invertPixel() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	if (!uartError) {
		glcd_invert_pixel(x, y);
	}
}

void cmd_drawLine_1() {
	uint8_t x1 = uartWaitNextChar();
	uint8_t y1 = uartWaitNextChar();
	uint8_t x2 = uartWaitNextChar();
	uint8_t y2 = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_line(x1, y1, x2, y2, 1);
	}
}

void cmd_drawLine_0() {
	uint8_t x1 = uartWaitNextChar();
	uint8_t y1 = uartWaitNextChar();
	uint8_t x2 = uartWaitNextChar();
	uint8_t y2 = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_line(x1, y1, x2, y2, 1);
	}
}

void cmd_fillRect_1() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t w = uartWaitNextChar();
	uint8_t h = uartWaitNextChar();
	if (!uartError) {
		glcd_fill_rect(x, y, w, h, 1);
	}
}

void cmd_fillRect_0() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t w = uartWaitNextChar();
	uint8_t h = uartWaitNextChar();
	if (!uartError) {
		glcd_fill_rect(x, y, w, h, 0);
	}
}

void cmd_drawRect_1() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t w = uartWaitNextChar();
	uint8_t h = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_rect(x, y, w, h, 1);
	}
}

void cmd_drawRect_0() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t w = uartWaitNextChar();
	uint8_t h = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_rect(x, y, w, h, 0);
	}
}


void cmd_drawCircle_1() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t r = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_circle(x, y, r, 1);
	}
}


void cmd_drawCircle_0() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t r = uartWaitNextChar();
	if (!uartError) {
		glcd_draw_circle(x, y, r, 0);
	}
}

void cmd_fillCircle_1() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t r = uartWaitNextChar();
	if (!uartError) {
		glcd_fill_circle(x, y, r, 1);
	}
}


void cmd_fillCircle_0() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t r = uartWaitNextChar();
	if (!uartError) {
		glcd_fill_circle(x, y, r, 0);
	}
}

void cmd_invertArea() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t w = uartWaitNextChar();
	uint8_t h = uartWaitNextChar();	
	if (!uartError) {
		glcd_invert_area(x, y, w, h);
	}
}


void cmd_drawCharXY() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t ch = uartWaitNextChar();	
	if (!uartError) {
		cmd_x = x + glcd_draw_char_xy(x, y, ch);
		cmd_y = y;
	}	
}


void cmd_drawChar() {
	uint8_t ch = uartWaitNextChar();
	if (!uartError) {
		cmd_x += glcd_draw_char_xy(cmd_x, cmd_y, ch) + cmd_string_interval;
	}	
}


void cmd_drawCharXYOver() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	uint8_t ch = uartWaitNextChar();	
	if (!uartError) {
		cmd_x = x + glcd_draw_char_xy_ex(x, y, ch, false);
		cmd_y = y;
	}	
}


void cmd_drawCharOver() {
	uint8_t ch = uartWaitNextChar();
	if (!uartError) {
		cmd_x += glcd_draw_char_xy_ex(cmd_x, cmd_y, ch, false) + cmd_string_interval;
	}	
}


void cmd_drawStringXY() {
	uint8_t x = uartWaitNextChar();
	uint8_t y = uartWaitNextChar();
	if (!uartError) {
		cmd_x = x;
		cmd_y = y;
	}
	while (true) {
		uint8_t ch = uartWaitNextChar();
		if (uartError) {
			return;
		}
		if (ch == 0) {
			break;
		}
		cmd_x += glcd_draw_char_xy(cmd_x, cmd_y, ch) + cmd_string_interval;
		if (cmd_x + CHAR_WIDTH > GLCD_LCD_WIDTH) {
			cmd_y += DELTA_Y;
			cmd_x = x;
		}
	}
}

void cmd_drawString() {
	while (true) {
		uint8_t ch = uartWaitNextChar();
		if (uartError) {
			return;
		}
		if (ch == 0) {
			break;
		}
		cmd_x += glcd_draw_char_xy(cmd_x, cmd_y, ch) + cmd_string_interval;
		if (cmd_x + CHAR_WIDTH > GLCD_LCD_WIDTH) {
			cmd_y += DELTA_Y;
			cmd_x = 0;
		}
	}
}


void cmd_drawCenteredString() {
	uint8_t y = uartWaitNextChar();

	char str[16];
	str[sizeof(str)-1] = 0;
	uint8_t width = 0;
	uint8_t i = 0;
	for (;;) {
		char ch = uartWaitNextChar();
		if (uartError) {
			return;
		}
		if (i < sizeof(str)) {
			str[i] = ch;
		}
		i++;
		if (!ch) {
			break;
		} else {
			width += CHAR_WIDTH + cmd_string_interval;
		}
	}
	
	width -= cmd_string_interval;
	if (width > GLCD_LCD_WIDTH) {
		width = GLCD_LCD_WIDTH;
	}
	uint8_t x = (GLCD_LCD_WIDTH - width)/2;
	i = 0;
	while (1) {
		char ch = str[i++];
		if (!ch) {
			break;
		}
		x += glcd_draw_char_xy(x, y, ch) + cmd_string_interval;
		if (x >= GLCD_LCD_WIDTH) {
			break;
		}
	}
}



void cmd_lcdWrite() {
	glcd_write();
}

void cmd_checkKeyboard() {
	uint8_t mask = 0;
	uint8_t codes[5];
	for (uint8_t key = 0; key < 5; key++) {
		uint8_t cnt = KeyboardGetRepeatCount(key);
		if (cnt) {
			mask |= _BV(key);
		}
		codes[key] = cnt;
	}
	uart_putc(mask);
	if (mask) {
		for (uint8_t key = 0; key < 5; key++) {
			uint8_t cnt = codes[key];
			if (cnt) {
				uart_putc(cnt);
			}
		}
	}
}


void cmd_setHighlight() {
	uint8_t th = uartWaitNextChar();
	uint8_t tl = uartWaitNextChar();
	if (!uartError) {
		keyboardAutoHighlightTime = (th << 8) + tl;
		if (keyboardAutoHighlightTime == 0) {
			HighlightDisable();
		} else if (keyboardAutoHighlightTime == 0xffff) {
			HighlightEnable();
		} else {
			screenHighlightCounter = keyboardAutoHighlightTime;
		}
	}
}

void cmd_setStringInterval() {
	uint8_t dx = uartWaitNextChar();
	if (!uartError) {
		cmd_string_interval = dx;
	}
}


void cmd_beep() {
	uint8_t fh = uartWaitNextChar();
	uint8_t fl = uartWaitNextChar();
	uint8_t d = uartWaitNextChar();
	if (!uartError) {
		BeeperStart((fh << 8) + fl, d);
	}
}

void cmd_setKeyboardBeep() {
	uint8_t enable = uartWaitNextChar();
	if (!uartError) {
		KeyboardBeep(enable);
	}
}

void CmdInit() {
	cmd_handlers[CMD_SYNC] = &cmd_sync;
	cmd_handlers[LCD_SET_CONTRAST] = &cmd_lcdSetContrast;
	cmd_handlers[LCD_CLEAR] = &cmd_lcdClear;
	cmd_handlers[DRAW_PIXEL_1] = &cmd_drawPixel_1;
	cmd_handlers[DRAW_PIXEL_0] = &cmd_drawPixel_0;
	cmd_handlers[INVERT_PIXEL] = &cmd_invertPixel;
	cmd_handlers[DRAW_LINE_1] = &cmd_drawLine_1;
	cmd_handlers[DRAW_LINE_0] = &cmd_drawLine_0;
	cmd_handlers[FILL_RECT_1] = &cmd_fillRect_1;
	cmd_handlers[FILL_RECT_0] = &cmd_fillRect_0;
	cmd_handlers[DRAW_RECT_1] = &cmd_drawRect_1;
	cmd_handlers[DRAW_RECT_0] = &cmd_drawRect_0;
	cmd_handlers[DRAW_CIRCLE_1] = &cmd_drawCircle_1;
	cmd_handlers[DRAW_CIRCLE_0] = &cmd_drawCircle_0;
	cmd_handlers[FILL_CIRCLE_1] = &cmd_fillCircle_1;
	cmd_handlers[FILL_CIRCLE_0] = &cmd_fillCircle_0;	
	cmd_handlers[INVERT_AREA] = &cmd_invertArea;	
	cmd_handlers[DRAW_CHAR_XY] = &cmd_drawCharXY;
	cmd_handlers[DRAW_CHAR] = &cmd_drawChar;
	cmd_handlers[DRAW_CHAR_XY_OVER] = &cmd_drawCharXYOver;
	cmd_handlers[DRAW_CHAR_OVER] = &cmd_drawCharOver;
	cmd_handlers[DRAW_STRING_XY] = &cmd_drawStringXY;
	cmd_handlers[DRAW_STRING] = &cmd_drawString;
	cmd_handlers[LCD_WRITE] = &cmd_lcdWrite;
	cmd_handlers[READ_KEYBOARD] = &cmd_checkKeyboard;
	cmd_handlers[SET_HIGHLIGHT] = &cmd_setHighlight;
	cmd_handlers[BEEP] = &cmd_beep;
	cmd_handlers[DRAW_CENTERED_STRING] = &cmd_drawCenteredString;
	cmd_handlers[SET_STRING_INTERVAL] = &cmd_setStringInterval;
	cmd_handlers[SET_KEYBOARD_BEEP] = &cmd_setKeyboardBeep;
}


void CmdExec(uint8_t code) {
	if (code <= API_MAX_CODE) {
		cmd_handlers[code]();
	}
}