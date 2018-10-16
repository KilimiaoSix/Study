#include "pwm.h"
void PWM_Init(u32 arr,u32 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   TIM_OCInitTypeDef  TIM_OCInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��

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
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //С�ڱȽ�ֵʱΪ��Ч��ƽ������Ϊ��Ч��ƽ
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;  //����ߵ�ƽΪ��Ч��ƽ
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_Pulse=0;
   
   TIM_OC1Init(TIM3,&TIM_OCInitStructure);
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);
   TIM_OC3Init(TIM3,&TIM_OCInitStructure);
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);
   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
   TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
   TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
   
   TIM_SetCompare1(TIM3,EM_Disable);  
   TIM_SetCompare2(TIM3,EM_Disable);
   TIM_SetCompare3(TIM3,EM_Disable);
   TIM_SetCompare4(TIM3,EM_Disable);
   
   printf("PWM��ʼ����ϣ�����\r\n");
   
}


















