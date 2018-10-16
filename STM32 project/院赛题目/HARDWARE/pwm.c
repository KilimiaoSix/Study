#include "pwm.h"
#include "led.h"
#include "usart.h"
u32 arr1=0,arr2=0,led_arr=0;
u16 pwm1val=0,pwm2val=0;
u16 ledchange_val=0;
int frequency1=0,frequency2=0;
void PWM1_Init(u32 arr,u32 psc)
{
   TIM_OCInitTypeDef TIM_OCInitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
   TIM_OC1Init(TIM14,&TIM_OCInitStructure);
   
   
   TIM_OC1PreloadConfig(TIM14,TIM_OCPreload_Enable);
   
   TIM_ARRPreloadConfig(TIM14,ENABLE);
   
      TIM_Cmd(TIM14,ENABLE);
}
void PWM2_Init(u32 arr,u32 psc)
{
   TIM_OCInitTypeDef TIM_OCInitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
   
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
   TIM_OC1Init(TIM11,&TIM_OCInitStructure);
   
   
   TIM_OC1PreloadConfig(TIM11,TIM_OCPreload_Enable);
   
   TIM_ARRPreloadConfig(TIM11,ENABLE);
   
      TIM_Cmd(TIM11,ENABLE); 
}
void LED_Change_Init(u32 arr,u32 psc)
{
   TIM_OCInitTypeDef TIM_OCInitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
   
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_Low;
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);
   
   
   TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
   
   TIM_ARRPreloadConfig(TIM3,ENABLE);
   
      TIM_Cmd(TIM3,ENABLE);
}

