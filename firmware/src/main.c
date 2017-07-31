#include"r232lc.h"
#include"queue.h"
#include"uart.h"
#include"spi.h"
#include"anim.h"
#include"pwm.h"
#include"protocol.h"
#include<avr/wdt.h>

#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/fuse.h>
#include<avr/pgmspace.h>
#include<avr/sleep.h>
#include<stdio.h>
#include<avr/lock.h>
#include<avr/cpufunc.h>

/**
 *
 */
const uint8_t PROGMEM statepin0 = PB6;
const uint8_t PROGMEM statepin1 = PB7;
const uint8_t PROGMEM sckpin = PB5;
const uint8_t PROGMEM mosipin = PB4;
const uint8_t PROGMEM misopin = PB3;
const uint8_t PROGMEM rxpin = PD0;
const uint8_t PROGMEM txpin = PD1;
const uint8_t PROGMEM ledserpin = PD2;
const uint8_t PROGMEM leddripin = PD3;
const uint8_t PROGMEM pwmpin = PB2;

/**
 *	Define global variable.
 */
volatile transmit_callback g_state_cb = NULL;
volatile struct queue_t rx_queue = {
	.size = 64,
};
volatile struct queue_t tx_queue = {
	.size = 16,
};
volatile struct queue_t led_queue = {
	.size = 32,
};
volatile struct animation_playback_t g_anim = {0};

volatile struct r232_state_t g_state = {
	.hstate = 0,
	.lstate = 0,
};

/**
 *	Fuses for the state of the microntroller through out
 *	the life time.
 */
FUSES =
{
	.low = LFUSE_DEFAULT,
	.high = HFUSE_DEFAULT,
};

/**
 *	Lock
 */
unsigned char __lock __attribute__((section (".lock"))) =
        (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);



/*	TODO MOVE.	*/
void transmit_rgb_w2811(uint8_t r, uint8_t g, uint8_t b){
	spi_putchar(r);
	spi_putchar(g);
	spi_putchar(b);
}
void transmit_rgb_spidata(uint8_t r, uint8_t g, uint8_t b){
	spi_putchar(r);
	spi_putchar(g);
	spi_putchar(b);
}

/**
 *
 */
ISR(TIMER0_OVF_vect){

	/*	Check if SPI is ready.	*/
	if(spi_ready())
		return;

	/*	requires three bytes.	*/
	if(queue_size(&led_queue) < 3)
		return;

	uint8_t r,g,b;

	if(g_state.lstate & STATE_ANIM){
		/*	Load RGB from animation playback.	*/
		animation_get_next_rgb(&g_anim, &r, &g, &b);
	}else{
		/*	Load RGB from LED data queue.	*/
		r = queue_dequ(&led_queue);
		g = queue_dequ(&led_queue);
		b = queue_dequ(&led_queue);
	}

	/*	transmit.	*/
	g_state_cb(r,g,b);
}

/**
 *
 */
ISR(SPI_STC_vect){
	uint8_t de = queue_dequ(&led_queue);
	spi_directwrite(de);
}

ISR(USART_TXC_vect){
	/*	*/
	if(!queue_empty(&tx_queue)){
		uart_putchar( queue_dequ(&tx_queue) );
	}
}
ISR(USART_RXC_vect){

	/*	Recv next byte.	*/
	queue_enqu(&rx_queue, uart_direct_getchar());
	sleep_disable();
}

ISR(USART_UDRE_vect){

}


ISR(INT0_vect){
	g_state.hstate = STATE_USEW2811;
	g_state_cb = transmit_rgb_w2811;
}

ISR(INT1_vect){
	g_state.hstate = STATE_LED_DATA;
	g_state_cb = transmit_rgb_spidata;
}

int main(void){

	/*	Disable global interrupt.	*/
	cli();

	/*	Disable Watchdog timer.	*/
	wdt_disable();

	/*	Enable UART.	*/
	uart_init();
	uart_enable_interrupt();
	PORTD |= (1 << rxpin) | (1 << txpin);
	DDRD |= (1 << rxpin) | (1 << txpin);

	/*	Enable SPI.	*/
	spi_init();
	spi_enable_interrupt();
	PORTB |= (1 << sckpin) | (1 << mosipin) | (1 << misopin);
	DDRB |= (1 << sckpin) | (1 << mosipin) | (1 << misopin);

	/*	initialize queue.	*/
	init_queue(&rx_queue);
	init_queue(&tx_queue);
	init_queue(&led_queue);

	/*	state.	*/
	PORTD |= (1 << statepin0) | (1 << statepin1);
	DDRD &= ~((1 << statepin0) | (1 << statepin1));
	if(PIND & ( 1 << statepin0) ||
			PIND & ( 1 << statepin1)){
		g_state_cb = transmit_rgb_spidata;
	}else{
		g_state_cb = transmit_rgb_w2811;
	}

	/*	Enable external interrupt.	*/
	MCUCR |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	GIFR |= (1 << INTF0) | (1 << INTF1);


	/*	Timer interrupt.	*/
	TCCR0 |= (0 << CS02) | (0 << CS01) | (1 << CS02);
	TIMSK |= (1 << TOIE0);

	/*	Create default animation.	*/
	animation_create(&g_anim, 0);

	/*	PWM.	*/
	pwm_enable();
	PORTB |= ( 1 << pwmpin);
	DDRB |= ( 1 << pwmpin);

	/*	LED drive.	*/
	PORTC = (1 << leddripin) | (1 << ledserpin);

	/*	Watchdog for preventing the device from getting stuck.	*/
	wdt_enable( ((1 << WDP2) | (1 << WDP1) | (1 << WDP0)) );

	/*	Enable global interrupt.	*/
	sei();

	/*	Main loop.	*/
	while(1){
		/*	Sleep intill needed.	*/
		set_sleep_mode(SLEEP_MODE_PWR_SAVE);
		sleep_cpu();

		/*	Process command from RX UART.	*/
		while(!queue_empty(&rx_queue)){
			uint8_t buf = queue_dequ(&rx_queue);
			uint8_t com = get_command(buf);
			call_command(com, buf);
		}
	}

	return 0;
}
