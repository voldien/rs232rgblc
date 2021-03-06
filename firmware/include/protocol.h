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
#ifndef _R232_LEDC_PROTOCOL_H_
#define _R232_LEDC_PROTOCOL_H_ 1
#include<stdio.h>
#include<avr/pgmspace.h>

/**
 *	Supported baud rates.
 */
extern const uint32_t PROGMEM suppbaud[];

/**
 *	Protocol.
 */
struct protocol_header_t{
	uint8_t command;	/*	*/
	uint8_t data;		/*	*/
};

struct protocol_header_data_t{
	uint8_t command;
	uint8_t len;
	/*	Rest.	*/
};

/**
 *	Protocol command.
 */
#define R232LCP_SET_STATEL		0x0	/*	Set state in low byte.	*/
#define R232LCP_SET_STATEH		0x1	/*	Set state in high byte.	*/
#define R232LCP_SET_LEDD		0x2	/*	Set current LED data.	*/
#define R232LCP_SET_ANIM		0x3	/*	Set internal animation sequence.	*/
#define R232LCP_SET_PWM			0x4	/*	Set PWM for the LED.	*/
#define R232LCP_SET_BAUD		0x5	/*	Set Baud rate.	*/
#define R232LCP_GET_BAUD		0xD	/*	Get Baud rate.	*/
#define R232LCP_GET_STATE		0xE	/*	Get current state.	*/
#define R232LCP_GET_VERSION		0xF	/*	Get version in string format.	*/

/**
 *	Protocol callback function data type.
 */
typedef void (*protocol_callback)(const uint8_t value);

/**
 *	protocol callback function array. Maps protocol
 *	command 1:1.
 */
extern const protocol_callback const PROGMEM protocol_cmd[16];

/**
 *
 *	@Returns
 */
extern uint8_t get_command(const uint8_t buf);
extern uint8_t get_value(const uint8_t buf);
extern void call_command(const uint8_t command, const uint8_t value);


/**
 *	Protocol command function.
 */
extern void protocol_setstateL(uint8_t value);
extern void protocol_setstateH(uint8_t value);

/**
 *
 */
extern void protocol_setledd(uint8_t value);

/**
 *
 */
extern void protocol_setanim(uint8_t value);
extern void protocol_getanim(uint8_t value);

/**
 *
 */
extern void protocol_setpwm(uint8_t value);
extern void protocol_getpwm(uint8_t value);

/**
 *
 */
extern void protocol_setbaud(uint8_t value);
extern void protocol_getbaud(uint8_t value);

/**
 *
 */
extern void protocol_getversion(uint8_t value);
extern void protocol_getstate(uint8_t value);


#endif
