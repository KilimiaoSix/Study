#include "led.h"
#include "delay.h"
void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStrucutre;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
   
   GPIO_InitStrucutre.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStrucutre.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStrucutre.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStrucutre.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStrucutre.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
   GPIO_Init(GPIOF,&GPIO_InitStrucutre);
   
   LED0=0;
   LED1=0;
   delay_ms(100);
   LED0=1;
   LED1=1;
}





