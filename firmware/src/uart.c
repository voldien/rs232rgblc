#define BAUD 9600	/*	Default buad.	*/
#include"uart.h"
#include<util/setbaud.h>
#include<avr/io.h>

void uart_init(void){

	/*	8 bit payload.	*/
	UCSRC |= (0 << UCSZ2) | (1 << UCSZ1) | (1 << UCSZ2);

	/*	Set defaut baud rate.	*/
	uart_setbaud(BAUD);
}

void uart_enable_interrupt(void){
	/*	Enable transmition and transmitt complete interrupt.	*/
	UCSRB |= _BV(TXEN) | _BV(TXCIE);

	/*	Enable recive and reciving complete interrupt.	*/
	UCSRB |= _BV(RXEN) | _BV(RXCIE);
}

void uart_setbaud(const uint32_t baud){

	/*	Compute buad.	*/
	const uint16_t rbaud = (((F_CPU) + 4UL * (BAUD)) / (8UL * (baud)) -1UL);

	/*	Disable UART. */


	/*		Set baud rate register.	*/
	UBRRH = (rbaud >> 8);
	UBRRL = (rbaud & 0xff);


	/*	Re-enable UART.	*/
}

void uart_putchar(const uint8_t c) {
	loop_until_bit_is_set(UCSRA, UDRE); /* Wait until data register empty. */
	UDR = c;
}

void uart_putchar_direct(const uint8_t c){
	UDR = c;
}

void uart_putstr(const uint8_t* st){
	while(*st != '\0'){
		uart_putchar(*st);
		st++;
	}
}

uint8_t uart_getchar(void) {
    loop_until_bit_is_set(UCSRA, RXC); /* Wait until data exists. */
    return UDR;
}

uint8_t uart_direct_getchar(void){
    return UDR;
}
