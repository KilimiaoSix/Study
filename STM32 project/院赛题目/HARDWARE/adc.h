#ifndef __ADC_H
#define __ADC_H

#include "sys.h"
#include "delay.h"
#include "key.h"




void My_ADC1_Init(void);
void My_ADC2_Init(void);
u16 Get_ADC1(u8 ch);
u16 Get_ADC2(u8 ch);
u16 Get_Adc1_Average(u8 ch,u8 times);
u16 Get_Adc2_Average(u8 ch,u8 times);
void ADC_Compare(double temp1,double temp2);





#endif


