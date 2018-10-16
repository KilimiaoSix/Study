#include "led.h"
void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructre;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
   
   GPIO_InitStructre.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStructre.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructre.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
   GPIO_InitStructre.GPIO_PuPd=GPIO_PuPd_DOWN;
   GPIO_InitStructre.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOF,&GPIO_InitStructre);
   
   LED0=0;
   LED1=0;
   delay_ms(100);
   LED0=1;
   LED1=1;
   
   
}






