#include "pwm.h"
void PWM_Init(u32 arr,u32 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   TIM_OCInitTypeDef  TIM_OCInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟	
   
   GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
   
   GPIO_Init(GPIOF,&GPIO_InitStructure);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   
   TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
   TIM_OCInitStructure.TIM_Pulse=0;
   
   TIM_OC1Init(TIM14,&TIM_OCInitStructure);
   
   TIM_OC2PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
 
   TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM14, ENABLE);  //使能TIM14
   
   
   
   
   
}
