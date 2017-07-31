/**
    rs232 RGB LED controller firmware.
    Copyright (C) 2017  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _R232_LC_H_
#define _R232_LC_H_ 1
#include<stdio.h>
#include<avr/pgmspace.h>

/**
 *	State enumerators.
 */
#define STATE_		0x0		/**/
#define STATE_ANIM	0x8		/*	Use animation.	*/

/**
 *
 */
#define STATE_USEW2811	0x1	/*	Use W2811.	*/
#define STATE_LED_DATA	0x2	/*	Use LED data.	*/

/**
 * LED transmit function.
 */
typedef void (*transmit_callback)(uint8_t r, uint8_t g, uint8_t b);
extern void transmit_rgb_w2811(uint8_t r, uint8_t g, uint8_t b);
extern void transmit_rgb_spidata(uint8_t r, uint8_t g, uint8_t b);

/**
 *	State of the controller.
 */
struct r232_state_t{
	uint8_t hstate;		/*	*/
	uint8_t lstate;		/*	*/
	uint8_t pwm;		/*	PWM value.	*/
	uint8_t baud;		/*	*/
};

/**
 *	Constant pins values.
 */
extern const uint8_t PROGMEM statepin0;
extern const uint8_t PROGMEM statepin1;
extern const uint8_t PROGMEM sckpin;
extern const uint8_t PROGMEM mosipin;
extern const uint8_t PROGMEM misopin;
extern const uint8_t PROGMEM rxpin;
extern const uint8_t PROGMEM txpin;
extern const uint8_t PROGMEM ledserpin;
extern const uint8_t PROGMEM leddripin;
extern const uint8_t PROGMEM pwmpin;

/**
 *	Declared global variable.
 *	Volatile memory on RAM.
 */
extern volatile transmit_callback g_state_cb;
extern volatile struct queue_t rx_queue;
extern volatile struct queue_t tx_queue;
extern volatile struct queue_t led_queue;
extern volatile struct animation_playback_t g_anim;
extern volatile struct r232_state_t g_state;

#endif
