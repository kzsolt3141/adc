/*
 * adc.h
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#ifndef ADC_TOOLS_H_
#define ADC_TOOLS_H_

#include <stdint.h>

/**
 * Initialize ADC for voltage ref AVCC, connect AREF to GND with C=100nF
 * @param [in] pin   select which pin of port C to be used for ADC
 * @param [in] isrEn enable ADC read by ISR, value is saved in rawADC
 */
void ADCInit(uint8_t pin, uint8_t isrEn);

/**
 * Read ADC output register
 * @return ADC value (10 bit precision)
 */
uint16_t ADCRead();

/**
 * Global variable to store ADC from ISR.
 */
uint16_t rawADC;

#endif /* ADC_TOOLS_H_ */