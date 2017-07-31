#include"pwm.h"
#include<avr/io.h>

void pwm_enable(void){
	TCCR2 = (1 << WGM20) | (0 << WGM21);
}

void pwm_set_value(const uint8_t value){
	OCR2 = value;
}
