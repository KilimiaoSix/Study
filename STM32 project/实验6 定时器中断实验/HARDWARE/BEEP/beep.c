#include "beep.h"
void BEEP_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
}
