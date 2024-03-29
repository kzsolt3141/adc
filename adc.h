/*
 * adc.h
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#ifndef ADC_TOOLS_H_
#define ADC_TOOLS_H_

#include <stdint.h>

typedef enum ADC_clock_source_t {
    ADC_PS_DEFAULT_2 = 0 ,
    ADC_PS_2,
    ADC_PS_4,
    ADC_PS_8,
    ADC_PS_16,
    ADC_PS_32,
    ADC_PS_64,
    ADC_PS_128
} ADC_clock_source;

/**
 * ADC interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs ADC_isr_cb will be called with ctx as parameter
 */
typedef void (*ADC_isr_cb)(void* ctx, uint16_t adc);

/**
 * Register callback and context for ADC interrupt
 * @param[in] cb   callback for isr; must not be NULL
 * @param[in] ctx  user defined callback context; must not be NULL
 * 
 */
void regiter_ADC_isr_cb(ADC_isr_cb cb, void* ctx);

/**
 * Initialize ADC for voltage ref AVCC, connect AREF to GND with C=100nF
 * this mode will use one ADC pin for single run conversion
 * ISR callback must be set before initialization
 * @param[in] clk_src     select clock prescaler, see ADC_clock_source_t
 * @param[in] en_free_run ADC vill measure in continious mode
 * 
 * @remark User must set ADC pin direction as input in application.
 */
void ADC_init(
    ADC_clock_source clk_src,
    uint8_t          en_free_run
);

/**
 * Initialize or read one ADV value.
 * This starts an ADC conversion.
 * @return 0 - when ISR is active -> ADC value will be delivered in ISR
 *         wait and return ADC value when conversion is finished
 */
uint16_t ADC_read();

#endif /* ADC_TOOLS_H_ */