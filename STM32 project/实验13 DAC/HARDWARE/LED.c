#include "LED.h"
#include "delay.h"
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//??GPIOF??

  //GPIOF9,F10?????
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0?LED1??IO?
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOF, &GPIO_InitStructure);//???GPIO
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10???,??
   
   LED0=0;
   LED1=0;
   delay_ms(100);
   LED0=1;
   LED1=1;  
   

}











