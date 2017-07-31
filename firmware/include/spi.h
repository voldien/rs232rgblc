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
#ifndef _R232_LEDC_SPI_H_
#define _R232_LEDC_SPI_H_ 1
#include<stdint.h>

/**
 *	Initalize SPI.
 */
extern void spi_init(void);

/**
 *	Enable interrupt callback.
 */
extern void spi_enable_interrupt(void);

/**
 *	Write directly to SPI data register.
 *	Used with SPI completey interrupt.
 */
extern void spi_directwrite(uint8_t c);

/**
 *	Write directly when the SPI data register
 *	is aviable and return instantly.
 */
extern void spi_fastwrite(uint8_t c);

/**
 *	@Return none zero if ready.
 */
extern uint8_t spi_ready(void);

/**
 *	Write directly when the SPI data register.
 */
extern uint8_t spi_putchar(uint8_t c);


#endif
