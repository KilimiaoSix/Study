#include "adc.h"
void My_ADC_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   ADC_CommonInitTypeDef ADC_CommonInitStructure;
   ADC_InitTypeDef ADC_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
   ADC_CommonInitStructure.ADC_Mode=ADC_Mode_Independent;
   ADC_CommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4;
   ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
   
   ADC_CommonInit(&ADC_CommonInitStructure);
   
   ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;
   
   ADC_Init(ADC1,&ADC_InitStructure);
   
   
   
   
}




