#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LED.h"
#include "pwm.h"
#include "timer.h"
//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{
   long long temp=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   delay_init(168);
   uart_init(115200);
   TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1);
   PWM_Init(500-1,84-1);
   while(1)
   {
      delay_ms(10);
      TIM_SetCompare1(TIM14,TIM_GetCapture1(TIM14)+1);
      if(TIM_GetCapture1(TIM14)==300)
      {
         TIM_SetCompare1(TIM14,0);
      }
      if(TIM5CH1_CAPTURE_STA&0x80)
      { 
         temp=TIM5CH1_CAPTURE_STA&0x3F;
         temp*=0xFFFFFFFF;
         temp+=TIM5CH1_CAPTURE_VAL;
         printf("HIGH:%lld us\r\n",temp);
         TIM5CH1_CAPTURE_STA=0;
      }
   }
}




/*
手册中讲解到步骤15的时候的main.c源码如下：
#include "stm32f4xx.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
  
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while(1){
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
	
	}
}
*/


