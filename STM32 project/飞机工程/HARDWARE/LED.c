#include "led.h"


void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOF,&GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
   GPIO_Init(GPIOF,&GPIO_InitStructure);
   
   PFout(9)=0;
   PFout(10)=0;
   
   
}


