#include "pwm.h"
void PWM_Init(u32 arr,u32 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   TIM_OCInitTypeDef  TIM_OCInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14时钟使能    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//使能PORTF时钟

   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
   TIM_OCInitStructure.TIM_Pulse=0;
   
   TIM_OC1Init(TIM3,&TIM_OCInitStructure);
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);
   TIM_OC3Init(TIM3,&TIM_OCInitStructure);
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);
   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
   TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
   TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM14
   
   
   
   
   
}
