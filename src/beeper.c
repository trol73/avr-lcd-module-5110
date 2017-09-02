#include "beeper.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t beeper_timer1value; 
volatile uint8_t beeper_duration;

ISR(TIMER1_COMPA_vect) {
	OCR1A += beeper_timer1value;
	
	if (beeper_duration) {
		PORTD ^= _BV(2);
	}
}


void BeeperInit() {
	DDRD |= _BV(2); 
	PORTD &= ~_BV(2);
	
	TCCR1A = 0;
	TCCR1B = _BV(CS11) | _BV(CS10);	// divider for TC1 = 64
}

void BeeperStart(uint16_t f, uint8_t d) {
	beeper_timer1value = F_CPU/64/f;
	beeper_duration = d;
	TCNT1 = 0;
	OCR1A = beeper_timer1value;
	TIMSK |= _BV(OCIE1A);
}

void BeeperStop() {
	beeper_duration = 0;
	TIMSK &= ~_BV(OCIE1A);
	PORTD &= ~_BV(2);
}
