#include <avr/interrupt.h>

#include "keyboard.h"

#include "beeper.h"
#include "ui.h"
#include "config.h"



uint8_t keyRepeatCount[5];

bool keyboardBeep;

// управляет подсветкой при нажатии клавиши. содержит время (в сотых долях секунды), которое будет подсвечиваться экран 
// после последнего нажатия на кнопку
volatile uint16_t keyboardAutoHighlightTime = 100;

// счётчик обратного отсчёта подсветки экрана
uint16_t screenHighlightCounter;


static void beepKey() {
	BeeperStart(KEYBOARD_BEEP_FREQUENCY, KEYBOARD_BEEP_DURATION);
}

void KeyboardCheck() {
	bool needHighlight = false;
	if (key_left_pressed()) {
		if (keyRepeatCount[KEY_LEFT] < 0xff) {
			keyRepeatCount[KEY_LEFT]++;
		}
		needHighlight = true;
	} else {
		keyRepeatCount[KEY_LEFT] = 0;
	}
	
	if (key_right_pressed()) {
		if (keyRepeatCount[KEY_RIGHT] < 0xff) {
			keyRepeatCount[KEY_RIGHT]++;
		}
		needHighlight = true;
	} else {
		keyRepeatCount[KEY_RIGHT] = 0;
	}
	
	if (key_up_pressed()) {
		if (keyRepeatCount[KEY_UP] < 0xff) {
			keyRepeatCount[KEY_UP]++;
		}
		needHighlight = true;
	} else {
		keyRepeatCount[KEY_UP] = 0;
	}
	
	if (key_down_pressed()) {
		if (keyRepeatCount[KEY_DOWN] < 0xff) {
			keyRepeatCount[KEY_DOWN]++;
		}
		needHighlight = true;
	} else {
		keyRepeatCount[KEY_DOWN] = 0;
	}
	
	if (key_enter_pressed()) {
		if (keyRepeatCount[KEY_ENTER] < 0xff) {
			keyRepeatCount[KEY_ENTER]++;
		}
		needHighlight = true;
	} else {
		keyRepeatCount[KEY_ENTER] = 0;
	}
	if (needHighlight) {
		screenHighlightCounter = keyboardAutoHighlightTime;
		if (keyboardAutoHighlightTime != 0) {
			HighlightEnable();
		}
	}
	
	bool beep = keyboardBeep;
	
	if (keyRepeatCount[KEY_LEFT] == KEY_PRESS_TIME) {
		onKeyPressed(KEY_LEFT);
		if (beep) {
			beepKey();
			beep = false;
		}
	}
	if (keyRepeatCount[KEY_RIGHT] == KEY_PRESS_TIME) {
		onKeyPressed(KEY_RIGHT);
		if (beep) {
			beepKey();
			beep = false;
		}
	}
	if (keyRepeatCount[KEY_UP] == KEY_PRESS_TIME) {
		onKeyPressed(KEY_UP);
		if (beep) {
			beepKey();
			beep = false;
		}
	}
	if (keyRepeatCount[KEY_DOWN] == KEY_PRESS_TIME) {
		onKeyPressed(KEY_DOWN);
		if (beep) {
			beepKey();
			beep = false;
		}
	}
	if (keyRepeatCount[KEY_ENTER] == KEY_PRESS_TIME) {
		onKeyPressed(KEY_ENTER);		
		if (beep) {
			beepKey();
			beep = false;
		}
	}

}



void KeyboardInit() {
	DDRD |= ~(_BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7));
	DDRB |= _BV(4);	// highlight
	PORTD |= _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7);
	keyRepeatCount[KEY_LEFT] = 0;
	keyRepeatCount[KEY_RIGHT] = 0;
	keyRepeatCount[KEY_UP] = 0;
	keyRepeatCount[KEY_DOWN] = 0;
	keyRepeatCount[KEY_ENTER] = 0;
	keyboardAutoHighlightTime = DEFAULT_HIGHLIGHT_TIME;
	screenHighlightCounter = keyboardAutoHighlightTime;
}


bool KeyboardRepeated(uint8_t key) {
	return keyRepeatCount[key] > KEY_REPEAT_TIME;
}

void KeyboardBeep(bool beep) {
	keyboardBeep = beep;
}


bool IsKeyboardBeep() {
	return keyboardBeep;			  
}

uint8_t KeyboardGetRepeatCount(uint8_t key) {
	return keyRepeatCount[key];
}

void HighlightDisable() {
	PORTB |= _BV(4);
}

void HighlightEnable() {
	PORTB &= ~_BV(4);
}