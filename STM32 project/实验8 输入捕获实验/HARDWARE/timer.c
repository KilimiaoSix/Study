#include "timer.h"
   TIM_ICInitTypeDef TIM_ICInitStructure;
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); 
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   
   TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
   
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
   
   TIM_ICInit(TIM5,&TIM_ICInitStructure);
   
   TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);
   
   TIM_Cmd(TIM5,ENABLE);
   
   NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
   NVIC_Init(&NVIC_InitStructure);
   
   
   
     
}
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
void TIM5_IRQHandler(void)
{
   if((TIM5CH1_CAPTURE_STA&0x80)==0)
   {
      if((TIM_GetFlagStatus(TIM5,TIM_IT_Update))!=RESET)
      {
         if(TIM5CH1_CAPTURE_STA&0x40)
         {
            
            if((TIM5CH1_CAPTURE_STA&0x3F)==0x3F)
            {
               TIM5CH1_CAPTURE_STA|=0x80;
               TIM5CH1_CAPTURE_VAL=0xFFFFFFFF;
            }
            else
            TIM5CH1_CAPTURE_STA++;
         }
      }
      if(TIM_GetFlagStatus(TIM5,TIM_IT_CC1)!=RESET )
      { 
         if(TIM5CH1_CAPTURE_STA&0x40)
         {
            TIM5CH1_CAPTURE_STA|=0x80;
            TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
            TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
         }
         else
         {
            TIM5CH1_CAPTURE_STA=0;
            TIM5CH1_CAPTURE_VAL=0;
            TIM5CH1_CAPTURE_STA|=0x40;
            TIM_Cmd(TIM5,DISABLE);
            TIM_SetCounter(TIM5,0);
            TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
            TIM_Cmd(TIM5,ENABLE);
         }
      }  
   }  
   TIM_ClearITPendingBit(TIM5,TIM_IT_Update|TIM_IT_CC1);
   
}



