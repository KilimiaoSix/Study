#include "exti.h"

void My_EXTI_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
   
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB2

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);

}

void EXTI9_5_IRQHandler(void)//紧急停止系统
{
   delay_us(10);//消抖
   if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)
      Stop();
   EXTI_ClearITPendingBit(EXTI_Line5);
   
}
//注：只有在紧急情况下方可使用，因为如果调用了只有重新初始化才能再次启动飞机
   
   


