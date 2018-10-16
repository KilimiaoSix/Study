#include "beep.h"
#include "delay.h"
void BEEP_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_Init(GPIOF,&GPIO_InitStructure);
   BEEP=1;
   delay_ms(100);
   BEEP=0;
   
}

