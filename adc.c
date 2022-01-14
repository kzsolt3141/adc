/*
 * adc.c
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#include "adc.h"

#include <stddef.h>

#include <avr/io.h>
#include <avr/interrupt.h>

static ADC_isr_cb  ADC_cb_     = NULL;
static void       *ADC_cb_ctx_ = NULL;

void regiter_ADC_isr_cb(ADC_isr_cb cb, void* ctx) {
    ADC_cb_ = cb;
    ADC_cb_ctx_ = ctx;
}

void ADC_init(
    ADC_clock_source clk_src,
    uint8_t          en_free_run
) {
    cli();

    ADMUX  |= (0 << REFS1) |
              (1 << REFS0);  // voltage ref = AVCC
    ADCSRA |= (1 << ADEN) |  // enable ADC
              (1 << ADSC) |   //start conversion
              (en_free_run << ADFR) |   // free running mode
              clk_src;

    if (ADC_cb_) {
        ADCSRA |= (1     << ADIE);   // enable ADC interrup
    }

    sei();
}

uint16_t ADC_read() {
    ADCSRA |= (1 << ADSC);               // start a conversion
    if (ADCSRA & (1 << ADIE)) return 0;  // value will be delivered in ISR

    while (ADCSRA & (1 << ADSC));  // wait for conversion to complete
    return ADC;                    // Store ADC value
}

ISR(ADC_vect) {
    ADC_cb_(ADC_cb_ctx_, ADC);
}