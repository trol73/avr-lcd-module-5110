#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>

#include <util/delay.h>

#include "lib/glcd/glcd.h"
#include "lib/glcd/fonts/font5x7.h"

#include "lib/uart/uart.h"
#include "keyboard.h"
#include "beeper.h"
#include "api_codes.h"
#include "commands.h"
#include "config.h"



#define TIMER2_DELTA_COUNT	(F_CPU/1024/100)		// 100 Hz

uint8_t displayContrast = DEFAULT_DISPLAY_CONTRAST;



extern volatile uint8_t beeper_duration;


// 100 Hz
ISR(TIMER2_COMP_vect) {
	OCR2 += TIMER2_DELTA_COUNT;
	
	if (beeper_duration) {
		beeper_duration--;
		if (!beeper_duration) {
			BeeperStop();
		}
	}
	KeyboardCheck();
	if (screenHighlightCounter != 0) {
		if (screenHighlightCounter != 0xffff) {
			screenHighlightCounter--;
			if (screenHighlightCounter == 0) {
				HighlightDisable();
			}		
		}
	}	
}



void InitDisplay() {
	GLCD_SELECT();
	glcd_init();
	glcd_set_contrast(displayContrast);
	glcd_clear();
	glcd_clear();
	glcd_tiny_set_font(Font5x7, 5, 7, 32, 0xff);
}

volatile bool uartError;

void uart_putc_hex(uint8_t b) {
	// upper nibble
	if ((b >> 4) < 0x0a)
		uart_putc((b >> 4) + '0');
	else
		uart_putc((b >> 4) - 0x0a + 'a');

	// lower nibble
	if ((b & 0x0f) < 0x0a)
		uart_putc((b & 0x0f) + '0');
	else
		uart_putc((b & 0x0f) - 0x0a + 'a');
}

uint8_t uartWaitNextChar() {
	while (true) {
		uint16_t c = uart_getc();
		if (c & UART_NO_DATA) {
			continue;
		} else {
			if (c & UART_FRAME_ERROR) {
				// Framing Error detected, i.e no stop bit detected
				uart_puts_P("UART Frame Error: ");
				uartError = true;
				return 0xff;
			}
			if (c & UART_OVERRUN_ERROR) {
				// Overrun, a character already present in the UART UDR register was 
				// not read by the interrupt handler before the next character arrived,
				// one or more received characters have been dropped
				uart_puts_P("UART Overrun Error: ");
				uartError = true;
				return 0xff;
			}
			if (c & UART_BUFFER_OVERFLOW) {
				// We are not reading the receive buffer fast enough,
				// one or more received character have been dropped 
				uart_puts_P("Buffer overflow error: ");
				uartError = true;
				return 0xff;
			}
		}
		return (uint8_t)c;
	}
}
	


void main() {
//	uart_init();
//	uart_puts("init");
	KeyboardInit();
	BeeperInit();
	KeyboardBeep(true);
	
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU)); 

	InitDisplay(65);
//	receivedCommandPos = 0;
	
	
//	uart_puts_P("Display unit init\n");
	
	
	// TC2
	TCCR2 |= _BV(CS22) | _BV(CS21) | _BV(CS20);
	TIMSK |= _BV(OCIE2);	
	
	
	sei();
	CmdInit();
	uartError = false;

	while (true) {
//		KeyboardCheck();

//		glcd_clear_buffer();

//		glcd_fill_rect(x, y, 30, 30, 1);
//		glcd_write();
		
		uint8_t cmd = uartWaitNextChar();
		CmdExec(cmd);
	}
}

//extern volatile uint8_t data[10];
//extern volatile uint8_t pos;


//void onKeyPressed(uint8_t key) {
//}
