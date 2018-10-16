#include "tim.h"
#include "lcd.h"
#include "led.h"
#include "pwm.h"
void TIM4_Init(u32 arr,u32 psc)
{
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x05; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x05; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
   
   
   
}
void TIM4_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
      LED1=!LED1;
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
   
   
}
void TIM5_Init(u32 arr,u32 psc)
{
      TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x06; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x06; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
   
   
}
void TIM5_IRQHandler(void)
{
     if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
      ledchange_val++;
      TIM_SetCompare4(TIM3,ledchange_val);
      if(ledchange_val>led_arr)
         ledchange_val=0;
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
   
}
