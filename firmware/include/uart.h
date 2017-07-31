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
#ifndef _R232_LEDC_UART_H_
#define _R232_LEDC_UART_H_ 1
#include<stdio.h>

/**
 * 	Initialize Serial.
 */
extern void uart_init(void);

/**
 *	Enable uart interrupts.
 */
extern void uart_enable_interrupt(void);

/**
 *	Enable UART.
 */
extern void uart_enable(void);

/**
 *	Disable UART.
 */
extern void uart_disable(void);

/**
 *	Set baud rate. Remark this function is slow because
 *	it uses 32 unsigned int for computing the buad value
 *	for assigning the UBRRH and UBRRL register.
 *
 *	\buad rate in decimal.
 */
extern void uart_setbaud(const uint32_t baud);

/**
 *	Assign character to UDR register once
 *	ready. This may cause the function to idle
 *	in this function for several cycles.
 */
extern void uart_putchar(const uint8_t c);

/**
 *	Assign character to UDR register without
 *	waiting if ready.
 *
 *	This function can be used with the ISR
 *	(Interrupt service routine).
 */
extern void uart_putchar_direct(const uint8_t c);

/**
 *
 */
extern void uart_putstr(const uint8_t* st);

/**
 *	Get character byte from UART
 *	recive buffer.
 *
 *	@Return
 */
extern uint8_t uart_getchar(void);

/**
 *
 */
extern uint8_t uart_direct_getchar(void);

#endif
