#include "Echo.h"
float high;
void Echo_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
}
void Sonic_Trig(void)
{
   TRIG_Low;
   delay_us(10);
   TRIG_High;
   delay_us(10);
   TRIG_High;
}




