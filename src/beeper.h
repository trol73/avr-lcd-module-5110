/* 
 * File:   beeper.h
 * Author: Trol
 *
 * Created on March 19, 2016, 5:00 PM
 */

#ifndef _BEEPER_H
#define	_BEEPER_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>


#define beeper_on()			PORTD |= _BV(2)
#define beeper_off()			PORTD &= ~_BV(2)

//#define beeper_init()		DDRD |= _BV(2); PORTD &= ~_BV(2)

void BeeperInit();
void BeeperStart(uint16_t f, uint8_t d);
void BeeperStop();


//void beep(uint16_t f, uint16_t d);
// f - frequency
// 100  Hz - 0x64
// 500 Hz - 0xe1
// 1000 Hz - 0xf1
// 2000 Hz - 0xf9
// 3000 Hz - 0xfb
// 5000 Hz - 0xfd
// d - duration in 0.01s
void beep(uint8_t f, uint8_t d);


#endif	// _BEEPER_H

