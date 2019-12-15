/*
 * adc.c
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#include "adc.h"

int16_t rawADC = 0;

void ADCInit(bool isrEn) {
	ADMUX |= (1 << REFS0) ; // voltage ref = AVCC (also ADC0 channel selected)
	ADCSRA |= (1 << ADEN) | // enable ADC
	          (1 << ADSC) | // start conversion
		      (isrEn << ADIE) | // ADC interrupt enable
			  (1 << ADPS2)| // sample prescaler
			  (1 << ADPS1)| // sample prescaler
			  (1 << ADPS0) ;// sample prescaler
}

uint16_t ADCRead() {
	ADCSRA |= (1<<ADSC);        // Start conversion
    while (ADCSRA & (1<<ADSC)); // wait for conversion to complete
    return ADC;                 //Store ADC value	
}

ISR(ADC_vect) {
	rawADC = ADC;        // save ADC value in global variable
	ADCSRA |= (1<<ADSC); // start a new conversion
}