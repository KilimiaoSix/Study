#include "Echo.h"
float high;
void Echo_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
}
void Sonic_Trig(void)
{
   TRIG_Low;
   delay_us(10);
   TRIG_High;
   delay_us(10);
   TRIG_High;
}




