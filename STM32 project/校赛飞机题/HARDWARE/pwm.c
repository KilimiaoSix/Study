#include "pwm.h"
void TIM3_PWM_Init(u32 arr,u32 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM_CH2
   GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
   
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   
   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //小于比较值时为有效电平，否则为无效电平
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;  //定义高电平为有效电平
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
   TIM_OCInitStructure.TIM_Pulse=0;
   
   TIM_OC1Init(TIM3,&TIM_OCInitStructure);
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);
   TIM_OC3Init(TIM3,&TIM_OCInitStructure);
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);
   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
   TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
   TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
   
   PITCH=PITCH_MIDDLE;
   ROLL=ROLL_MIDDLE;
   YAW=YAW_MIDDLE;
   THROTTLE=THROTTLE_MIN;

}
void TIM1_PWM_Init(u32 arr,u32 psc)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO , ENABLE);  //使能GPIO外设时钟使能
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
   
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

   TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能
   TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
   
   TIM_SetCompare4(TIM1,EM_Disable);
   TIM_SetCompare4(TIM1,MODE_MIDDLE);  //将模式设置成为姿态模式
}

















