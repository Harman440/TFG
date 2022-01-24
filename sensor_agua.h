#ifndef __SENSOR_AGUA_H
#define __SENSOR_AGUA_H

#include "main.h"

uint16_t AlturaAguaADC_noCallback(ADC_HandleTypeDef *h);
uint16_t AlturaAguaADC_enCallback(uint16_t* vDMA);
int ADC2cm(uint16_t *adc_value, uint16_t *altsensor, int *vref);
//------
uint16_t millvolt2cm_ultrasound(int *mvolts);
//------
uint16_t AlturaAguaADC_2(ADC_HandleTypeDef *h);
uint16_t ADC2cm_2(int *adc_value, uint16_t *altsensor, uint16_t *vref);
uint16_t ADCtomillvolt(int *adc_value, int *vref);

#endif
