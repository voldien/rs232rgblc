#include"protocol.h"
#include"uart.h"
#include"queue.h"
#include"r232lc.h"
#include"anim.h"
#include"pwm.h"
#include<avr/eeprom.h>
#include<avr/pgmspace.h>

const uint32_t PROGMEM suppbaud[] = {
		110, 300, 600, 1200, 2400, 4800, 9600,
		14400, 19200, 38400, 57600, 115200, 128000, 256000
};

const protocol_callback const PROGMEM protocol_cmd[16] = {
		protocol_setstateL,
		protocol_setstateH,
		protocol_setledd,
		protocol_setanim,
		protocol_setpwm,
		protocol_setbaud,
		protocol_getbaud,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		protocol_getstate,
		protocol_getversion,
};


uint8_t get_command(const uint8_t buf){
	return (buf & 0xF0) >> 4;
}
uint8_t get_value(const uint8_t buf){
	return (buf & 0xF0);
}

void call_command(const uint8_t command, const uint8_t value){

	protocol_callback cb;

	/*	Get function pointer.	*/
	cb = pgm_read_ptr(&protocol_cmd[command]);

	/*	call function.	*/
	cb(get_value(value));
}



void protocol_setstateL(uint8_t value){
	g_state.lstate = value;
}

void protocol_setstateH(uint8_t value){
	g_state.hstate = value;
}
void protocol_setledd(uint8_t value){
	queue_enqu(&led_queue, value);
}
void protocol_setanim(uint8_t value){
	animation_create(&g_anim, value);
}
void protocol_setpwm(uint8_t value){
	pwm_set_value(value);
}


void protocol_setbaud(uint8_t value){

	/*	Load buad from program memory.	*/
	uint32_t vbuad = pgm_read_dword(&suppbaud[value]);

	/*	Update buad rate.	*/
	uart_setbaud(vbuad);

	/*	update	*/
	g_state.baud = value;
}

void protocol_getbaud(uint8_t value){
	uart_putchar(g_state.baud);
}


#define VERSION ""
const uint8_t* const PROGMEM version = (const uint8_t*)VERSION;
void protocol_getversion(uint8_t value){

	const uint8_t* pver = pgm_read_ptr(version);

	queue_enqustr(&tx_queue, pver);
}

void protocol_getstate(uint8_t value){
	queue_enqu(&tx_queue, g_state.lstate);
	queue_enqu(&tx_queue, g_state.hstate);
}
