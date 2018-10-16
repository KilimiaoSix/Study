#include "exti.h"
#include "key.h"
#include "delay.h"
#include "pwm.h"
int i=0;
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
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
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	delay_ms(10);	//����
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
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY1==0)	 
	{
      pwm_change=!pwm_change;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	delay_ms(10);	//����
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
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}




