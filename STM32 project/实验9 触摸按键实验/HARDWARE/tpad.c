#include "tpad.h"
vu16 tpad_default_val=0;
void TIM2_CH1_Cap_Init(u32 arr,u16 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStructure;
   TIM_ICInitTypeDef TIM_ICInitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
   
   TIM2_TimeBaseInitStructure.TIM_Period=arr;
   TIM2_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM2_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   TIM2_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseInitStructure);
   
   TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
   TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter=0x00;
   TIM_ICInit(TIM2,&TIM_ICInitStructure);
   
   TIM_Cmd(TIM2,ENABLE);

   
   
   
}

u8 TPAD_Init(u8 psc)
{
   u16 buf[10],temp;
   u8 i,j;
   TIM2_CH1_Cap_Init(TPAD_ARR_MAX_VAL,psc-1);
   for(i=0;i<10;i++)
   {
      buf[i]=TPAD_Get_Val();
   }
   for(i=0;i<9;i++)
   {
      for(j=i+1;j<10;j++)
      {
         if(buf[i]>buf[j])
         {
            temp=buf[i];
            buf[i]=buf[j];
            buf[j]=temp;
         }
      }
   }
   temp=0;
   for(i=2;i<8;i++)
      temp+=buf[i];
   tpad_default_val=temp/6;
   printf("tpad_default_val:%d\r\n",tpad_default_val);
   if((u32)tpad_default_val>(TPAD_ARR_MAX_VAL/2))
      return 1;
   else
      return 0;
   
}
u16 TPAD_Get_Val(void)
{
   TPAD_Reset();
   while(TIM_GetFlagStatus(TIM2,TIM_IT_CC1)==RESET)
   {
      if(TIM_GetCounter(TIM2)>TPAD_ARR_MAX_VAL-500)
         return TIM_GetCounter(TIM2);
   }
   return TIM_GetCounter(TIM2);
}
void TPAD_Reset(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   PAout(5)=0;
   delay_ms(5);
   TIM_ClearITPendingBit(TIM2,TIM_IT_CC1|TIM_IT_Update);
   TIM_SetCounter(TIM2,0);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   
}
u16 TPAD_Get_MAXVAL(u8 n)
{
   u16 temp=0,res=0;
   while(n--)
   {
      temp=TPAD_Get_Val();
      if(temp>res)
         res=temp;
   }
   return res;
}
u8 TPAD_Scan(u8 mode)
{
   static u8 keyen=0;
   u8 res=0,sample=3;
   u16 rval;
   if(mode)//mode为1时支持连按，mode为0时不支持连按
   {
      sample=6;
      keyen=0;
   }
   rval=TPAD_Get_MAXVAL(sample);
   if(rval>tpad_default_val+TPAD_GATE_VAL&&rval<(tpad_default_val*10))
   {
      if((keyen==0)&&(rval>tpad_default_val+TPAD_GATE_VAL))
      {
         res=1;
      }
      keyen=3;
   }
   if(keyen)
      keyen--;
   return res;
}

