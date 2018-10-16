#include "PWM.h"
#include "usart.h"

//TIM4 PWM������l��
//PWM?�X��l��
//arr:��?��??��
//psc�G???��?�t?
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//�ϯ�w?��3??
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //�ϯ�GPIO�~?
	    
 
   //?�X�\��A?�XTIM4 CH3��pwm??�i��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�`�α���?�X
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��l��GPIO
 
   //3?��??��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //?�m��?��??��
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //?�m???��?�t?
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //?�m??���ΡGTDTS=Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM�V�W??�Ҧ�
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��l�Ʃw?��4
	
	//��l��TIM4 PWM�Ҧ�	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //??�w?���Ҧ�?�w?���Ҧ�2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //��??�X�ϯ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //?�X��ʡGTIM?�X��?��ʰ�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //���uT���w��??��l�ƥ~?TIM_OC3

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //�ϯ�TIM4�bCCR2�W��???�H�s��
 
	TIM_Cmd(TIM4, ENABLE);  //�ϯ�TIM4
	

}
void Set_PWM(u16 pwminput)
{
	TIM_SetCompare3(TIM4,pwminput);
   if(pwminput==GEAR_1)
   {
      LED1=1;   
      LED2=0;
      LED3=0;
   }
   if(pwminput==GEAR_2)
   {
      LED2=1;
         LED1=0;
         LED3=0;
      
   }
   if(pwminput==GEAR_3)
   {
      LED3=1;
         LED2=0;
         LED1=0;
      
      
   }
}






