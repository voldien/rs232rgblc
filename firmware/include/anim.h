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
#ifndef _R232_LEDC_ANIM_H_
#define _R232_LEDC_ANIM_H_ 1
#include<stdio.h>
#include<avr/pgmspace.h>
#include<avr/eeprom.h>

/**
 *	Animation constants.
 *	Recommanded to be a power of two.
 */
#define ANIM_NUM 8		/*	Number of animation.	*/
#define ANIM_SIZE 64	/*	Number of key animation value.	*/

/**
 *	Animation array. Each animation consist
 *	of an array of three values.
 */
extern const uint8_t const PROGMEM animarray[ANIM_NUM][ANIM_SIZE][3];

/**
 *	Animation playback state.
 */
struct animation_playback_t{
	uint8_t pos;				/*	Position in animation.	*/
	const uint8_t const* pbuf;	/*	Animation buffer.	*/
};

/**
 *	Create animation based from animarray .
 *
 *	\anim
 *
 *	\i index of global animation structure, needs to be smaller than
 *	ANIM_NUM
 */
extern void animation_create(volatile struct animation_playback_t* anim,
        uint8_t i);

/**
 *	Get next RGB value from animation playback.
 */
extern void animation_get_next_rgb(volatile struct animation_playback_t* anim,
        uint8_t* __restrict__ r, uint8_t* __restrict__ g,
        uint8_t* __restrict__ b);

#endif
