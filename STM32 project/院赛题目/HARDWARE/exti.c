#include "exti.h"
#include "key.h"
#include "delay.h"
#include "pwm.h"
int i=0;
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	 
	{
      if(i==0)
      {
         TIM_Cmd(TIM14,DISABLE);
         TIM_Cmd(TIM11,DISABLE);
         i++;
      }
      else if(i==1)
      {
         TIM_Cmd(TIM14,ENABLE);
         TIM_Cmd(TIM11,DISABLE);
         i++;
      }
      else if(i==2)
      {
         TIM_Cmd(TIM14,DISABLE);
         TIM_Cmd(TIM11,ENABLE);
         i++;
      }
      else if(i==3)
      {
         TIM_Cmd(TIM14,ENABLE);
         TIM_Cmd(TIM11,ENABLE);
         i=0;
      }
      
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	delay_ms(10);	//消抖
	if(KEY2==0)	  
	{
      if(pwm_change==0)
      {
         frequency1-=100;
         arr1=1000000/frequency1;
         TIM_TimeBaseInitStructure.TIM_Period=arr1-1;
         TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;
         TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
         TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
         TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);
      }
      else
      {
         frequency2-=100;
         arr2=1000000/(frequency2);
         TIM_TimeBaseInitStructure.TIM_Period=arr2-1;
         TIM_TimeBaseInitStructure.TIM_Prescaler=168-1;
         TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
         TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
         TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);
      }
   }		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0)	 
	{
      pwm_change=!pwm_change;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	delay_ms(10);	//消抖
	if(KEY0==0)	 
	{			
       if(pwm_change==0)
       {
             frequency1+=100;
             arr1=1000000/(frequency1);
             TIM_TimeBaseInitStructure.TIM_Period=arr1-1;
             TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;
             TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
             TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
             TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);
       }
       else
       {
          frequency2+=100;
          arr2=1000000/(frequency2);
          TIM_TimeBaseInitStructure.TIM_Period=arr2-1;
          TIM_TimeBaseInitStructure.TIM_Prescaler=168-1;
          TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
          TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
          TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);
       }
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}




