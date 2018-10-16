#include "led.h"
void LED_Init(void)
{
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能端口时钟
}