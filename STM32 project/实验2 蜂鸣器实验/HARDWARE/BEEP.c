#include"BEEP.h"
#include"stm32f4xx.h"
void BEEP_Init()
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Speed=0x03;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOF,&GPIO_Initstructure);
	GPIO_SetBits(GPIOF,GPIO_Pin_All);


}




