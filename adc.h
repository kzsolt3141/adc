/*
 * adc.h
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 

#ifndef ADC_TOOLS_H_
#define ADC_TOOLS_H_

#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>

void ADCInit(bool isrEn);
uint16_t ADCRead();

int16_t rawADC;

#endif /* ADC_TOOLS_H_ */