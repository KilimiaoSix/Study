#include "PWM.h"
#include "usart.h"

//TIM4 PWM部分初始化
//PWM?出初始化
//arr:自?重??值
//psc：???分?系?
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定?器3??
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外?
	    
 
   //?出功能，?出TIM4 CH3的pwm??波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽?出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //3?那??‘TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //?置自?重??值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //?置???分?系?
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //?置??分割：TDTS=Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上??模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化定?器4
	
	//初始化TIM4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //??定?器模式?定?器模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比??出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //?出极性：TIM?出比?极性高
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的??初始化外?TIM_OC3

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的???寄存器
 
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
	

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






