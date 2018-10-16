#include "Echo.h"
#include "usart.h"
float high=0;
void Echo_Init(u16 arr,u16 psc)
{
   TIM_ICInitTypeDef  TIM2_ICInitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA0 下拉
   
//   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
//   
//	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
// 	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
// 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// 	EXTI_Init(&EXTI_InitStructure);
//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
   
   //初始化TIM5输入捕获参数
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
  
   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;	
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;				
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
 	NVIC_Init(&NVIC_InitStructure); 
   
   TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
   	TIM_Cmd(TIM2,ENABLE ); 	//使能定时器5
      printf("超声波模块初始化完毕！！!\r\n");
}
void Sonic_Trig(void)
{
   TRIG_Low;
   delay_us(10);
   TRIG_High;
   delay_us(10);
   TRIG_Low;
}
void Get_High(void)
{
   long long temp;
   Sonic_Trig();
   delay_ms(10);
   if(TIM5CH1_CAPTURE_STA&0X80)
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;
			temp+=TIM5CH1_CAPTURE_VAL;
         high=((temp/2.0)/1000000.0)*380.0;
			TIM5CH1_CAPTURE_STA=0;
		}
}
//void EXTI0_IRQHandler(void)
//{
//   GPIO_InitTypeDef GPIO_InitStructure;
//   if(EXTI_GetITStatus(EXTI_Line0) != RESET)
//   {
//      
//      TIM_SetCounter(TIM4,0);
//      TIM_Cmd(TIM4,ENABLE);
//      GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//      GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
//      GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//   
//      GPIO_Init(GPIOA,&GPIO_InitStructure);
//      while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)!=RESET);
//      TIM_Cmd(TIM4,DISABLE);
//      high=TIM_GetCounter(TIM4)*5.0*34.0/100.0;
//      TIM_SetCounter(TIM4,0);
//      GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
//      GPIO_Init(GPIOA,&GPIO_InitStructure);
//   }
//   EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
//}
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值

void TIM2_IRQHandler(void)
{
   
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获2发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture2(TIM2);
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
 
}
