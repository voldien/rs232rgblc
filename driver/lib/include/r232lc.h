/**
    rs232 RGB LED controller library interface.
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
#define _RS232_LC_H_ 1
#include"r232lcdef.h"
#include<stdio.h>
#include<stdlib.h>

/**
 *	RS232 RGB LED controller.
 */
typedef struct rs232lc_t{
	int fd;				/*	file descriptor with */
	unsigned int state;	/*	Current flag states.	*/
	unsigned int pwm;	/*	Current pulse with modulation.	*/
	unsigned int anim;	/*	Currant animation index.	*/
	unsigned int baud;	/*	Baud rate mode currently used.	*/
}RS232LC;

/**
 *	Create RGB value.
 */
#define R232LC_RGB(r, g, b) ((( ( r ) & 0xff) << 0) | (( ( g ) & 0xff) << 8) | (( ( b ) & 0xff) << 16) )

/**
 *	States.
 */
#define STATE_ANIM      0x8	/*	*/


/**
 *	rs232 rgb led controller protocol command.
 */
#define R232LCP_SET_STATEL      0x0	/*	Set state in low byte.	*/
#define R232LCP_SET_STATEH      0x1	/*	Set state in high byte.	*/
#define R232LCP_SET_LEDD        0x2	/*	Set current LED data.	*/
#define R232LCP_SET_ANIM        0x3	/*	Set internal animation sequence.	*/
#define R232LCP_SET_PWM         0x4	/*	Set PWM for the LED.	*/
#define R232LCP_SET_BAUD        0x5	/*	Set Baud rate.	*/
#define R232LCP_GET_BAUD        0xD	/*	Get Baud rate.	*/
#define R232LCP_GET_STATE       0xE	/*	Get current state.	*/
#define R232LCP_GET_VERSION     0xF	/*	Get version in string format.	*/

/**
 *	Baud rate.
 */
#define BAUD1200    0x0	/*	1200 bps.	*/
#define BAUD2400    0x1	/*	2400 bps.	*/
#define BAUD4800    0x2	/*	4800 bps.	*/
#define BAUD9600    0x3	/*	9600 bps.	*/
#define BAUD19200   0x4	/*	19200 bps.	*/
#define BAUD38400   0x5	/*	38400 bps.	*/
#define BAUD57600   0x6	/*	57600 bps.	*/
#define BAUD115200  0x7	/*	115200 bps.	*/

/**
 *	Buad rates.
 */
const uint32_t baudrates[] = {
		110, 300, 600, 1200, 2400, 4800, 9600,
		14400, 19200, 38400, 57600, 115200, 128000, 256000
};


#ifdef __cplusplus
extern "C"{
#endif

/**
 *	Initialize driver. This function must be
 *	invoked before using the functions in this
 *	library.
 *
 *	@Return non zero if successfully.
 */
extern R232LCDS int rs232lc_init(RS232LC* state, int fd);

/**
 *
 */
extern R232LCDS int rs232lc_close(RS232LC* state);

/**
 *	Set/Get PWM for the LED intensity.
 *
 *	@Return
 */
extern R232LCDS void rs232lc_set_pwm(RS232LC* state, uint8_t pwm);
extern R232LCDS uint8_t rs232lc_get_pwm(RS232LC* state);

/**
 *	Set/Get baud rate.
 *
 *	@Return status.
 */
extern R232LCDS int rs232lc_set_baud(RS232LC* state, uint8_t baud);
extern R232LCDS uint8_t rs232lc_get_baud(RS232LC* state);

/**
 *	Write rgb.
 *	\state
 *
 *	\rgb use R232LC_RGB for assigning rgb
 *
 *	@Return status
 */
extern R232LCDS int rs232lc_set_rgb(RS232LC* state, uint32_t rgb);

/**
 *	Set/Get animation.
 */
extern R232LCDS void rs232lc_set_anim(RS232LC* state, uint32_t anim);
extern R232LCDS uint32_t rs232lc_get_anim(const RS232LC* state);

/**
 *	Set/Get bitwise state.
 */
extern R232LCDS void r232lc_set_state(RS232LC* state, unsigned int state);
extern R232LCDS uint32_t r232lc_get_state(const RS232LC* state);

/**
 *	Get version of the firmware on the r232 LED controller.
 *
 *	\state
 *
 *	\pversion character pointer.
 */
extern R232LCDS void rs232lc_get_version(const RS232LC* __restrict__ state,
        char* __restrict__ pversion, int len);

/**
 *	Get version of driver.
 *
 *	@Return non-null terminated string.
 */
extern R232LCDS const char* rs232lc_version(void);


#ifdef __cplusplus
};
#endif

#endif 
