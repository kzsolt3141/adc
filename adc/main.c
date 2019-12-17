/*
 * adc.c
 *
 * Created: 12/17/2019 12:09:35 AM
 * Author : Zsolt
 */ 

#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include <util/delay.h>

int main(void) {
	USARTInit();
	ADCInit(PC1,0);
	
	for (;;) {
		uint16_t value = ADCRead();
		printf("%04x\n", value);
		_delay_ms(300);
	}
}

