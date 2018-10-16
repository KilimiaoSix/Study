#include"LED.h"
#include"stm32f4xx.h"
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_8;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_Initstructure);
	GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_8);
}
