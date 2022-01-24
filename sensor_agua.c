/*
TFG
*/

#include "sensor_agua.h"
#include <math.h>

uint16_t AlturaAguaADC_NoCallback(ADC_HandleTypeDef *h)
{
	uint16_t value_adc[10]={0};
	uint32_t sum = 0;
	uint16_t mean = 0;
	  //read sensor
	  HAL_ADC_Start_DMA(h, (uint32_t*)&value_adc, 10);
	  for(int i=0;i<10;i++){
		  HAL_ADC_Start(h); //start ADC para cada medida
		  HAL_Delay(100); //DElay para separar medidas
		  sum += value_adc[i];
	  }
	  mean = sum/10;
	  return mean;
}

uint16_t AlturaAguaADC_enCallback(uint16_t* vDMA)
{
	uint16_t sum = 0;
	for(int i=0;i<10;i++){
		sum += vDMA[i];
	}
	return sum/10;
}

int ADC2cm(uint16_t *adc_value, uint16_t *altsensor, int *vref)
{
	float div = *vref/4096.0;
	float alturaV = (*adc_value * div)/1000;
	int alturaCm = (int)1.0155*pow(alturaV, -2.457);
	return alturaCm + *altsensor;
}

//----- Sensor de ultrasonidos
uint16_t millvolt2cm_ultrasound(int *adc_value)
{
	return *adc_value * 0.3175;
}


//----funciones viejas

uint16_t AlturaAguaADC_2(ADC_HandleTypeDef *h)
{
	uint16_t value_adc = 0;
	float mean = 0;
	  //read sensor
	  HAL_ADC_Start_DMA(h, (uint32_t*)&value_adc, 1);
	  for(int i=0;i<100;i++){
		  HAL_ADC_Start(h);
		  HAL_Delay(10);//without delay it seems not to work
		  //increased cycles might work now without delay
		  mean = (mean * i + value_adc)/(i+1);//wont work dividing uint32_t
	  }
	  return mean;
}


uint16_t ADC2cm_2(int *adc_value, uint16_t *altsensor, uint16_t *vref)
{
	uint8_t size = 16;
	uint16_t v[16] = {1038, 863, 685, 582, 523, 491, 466, 439, 427, 408, 395, 376,
						363, 351, 336, 327};
	uint16_t mvolts = ADCtomillvolt(*adc_value, *vref);
	for(int i=0; i<size-1; i++)
	{
		if(mvolts > ((v[i]+v[i+1])/2))
		{
			return i+1 + *altsensor;
		}
	}
	return size + *altsensor;
}


uint16_t ADCtomillvolt(int *adc_value, int *vref)
{
	float div = *vref/4096.0;
	uint16_t result = *adc_value * div;//can not divide uint16_t/float
	return result;
}
