#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "delay.h"
void My_ADC_Init(void);
u16 Get_ADC(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);







#endif



