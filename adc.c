/*
 * adc.c
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void ADCInit(uint8_t pin, uint8_t isrEn) {
    cli();
    ADMUX  |= (0     << REFS1) | (1     << REFS0) | // voltage ref = AVCC 
              pin;                                  // select pin for ADC
    ADCSRA |= (1     << ADEN) |                     // enable ADC
              (isrEn << ADIE) |                     // ADC interrupt enable
              (isrEn << ADSC);						// start a new conversion if interrupt is enabled
    DDRC &= ~(1 << pin);                                // set ADC pin as input
    rawADC = 0;
    sei();
}

uint16_t ADCRead() {
    ADCSRA |= (1<<ADSC);                            // Start conversion
    while (ADCSRA & (1<<ADSC));                     // wait for conversion to complete
    return ADC;                                     // Store ADC value	
}

ISR(ADC_vect) {
    rawADC = ADC;                                   // save ADC value in global variable
    ADCSRA |= (1<<ADSC);                            // start a new conversion
}