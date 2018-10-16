#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h" 
#include "beep.h" 
void EXTIX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	KEY_Init();
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line4|EXTI_Line3|EXTI_Line2;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(KEY0==0)
	{
		LED0=!LED0;
		LED1=!LED1;
		BEEP=1;
		delay_ms(1000);
		BEEP=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
void EXTI3_IRQHandler(void)
{
	delay_ms(10);
	if(KEY1==0)
	{
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}
void EXTI2_IRQHandler(void)
{
	delay_ms(10);
	if(KEY2==0)
	{
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}
void EXTI0_IRQHandler(void)
{
	delay_ms(10);
	if(WK_UP==1)
	{
		BEEP=!BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}












