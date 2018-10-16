#include "InPutSwitch.h"
#include "PWM.h"
int16_t Fan_MODE_SW=1;//风扇模式参数，默认为手动模式
int16_t Humidifier_MODE_SW=1;//加湿器模式参数，默认为手动模式
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化0.

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //复用中断映射到PB.3

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY3
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//设置为上升沿触发中断
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //KEY4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//复用中断映射到PB.4
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器+
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);//复用中断映射到PB.4
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器+
  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);//复用中断映射到PB.5
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);//复用中断映射到PB.6
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);//复用中断映射到PB.7
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
   
/***********************
以上函数为配置外部中断线
************************/
 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
 
 NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
}
void EXTI9_5_IRQHandler(void)
      {
   delay_ms(10);
//   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)//判断按钮是否按下
//   {
//      Fan_MODE_SW=!Fan_MODE_SW;//模式切换
//      LED0=!LED0;
//      EXTI_ClearITPendingBit(EXTI_Line5);
//   }
//   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1)//再次判断按钮是否按下
//   {
//      Humidifier_MODE_SW=!Humidifier_MODE_SW;//切换加湿器控制模式
//      LED4=!LED4;
//      EXTI_ClearITPendingBit(EXTI_Line6);//清除中断标志位
//   }
                                                         if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)
   {
      if(Fan_MODE_SW==0)
      {
         Set_PWM(GEAR_1);
      };
   }
   if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==1)
   {
      if(Fan_MODE_SW==0)
      {
         Set_PWM(GEAR_2);
         
      }
   }
   if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1)
   {
      if(Fan_MODE_SW==0)
      {
         Set_PWM(GEAR_3);
         
      }
   }
    EXTI_ClearITPendingBit(EXTI_Line5);
   EXTI_ClearITPendingBit(EXTI_Line6);
   EXTI_ClearITPendingBit(EXTI_Line7);
//   if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1)
//   {
//      if(Humidifier_MODE_SW==0)
//      {
//         Humidifier=!Humidifier;
//      }
//      
//     EXTI_ClearITPendingBit(EXTI_Line9);
//   }
   
}
void EXTI0_IRQHandler(void)
{
      delay_ms(10);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)//判断按钮是否按下
   {
      Fan_MODE_SW=!Fan_MODE_SW;//模式切换
      LED0=!LED0;
   }
   EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void)
{
   delay_ms(10);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)//再次判断按钮是否按下
   {
      Humidifier_MODE_SW=!Humidifier_MODE_SW;//切换加湿器控制模式
      LED4=!LED4;
   }
    EXTI_ClearITPendingBit(EXTI_Line1);//清除中断标志位
}
void EXTI2_IRQHandler(void)
{
   delay_ms(10);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==1)
   {
      if(Humidifier_MODE_SW==0)
      {
         Humidifier=!Humidifier;
      }
      
   }
   EXTI_ClearITPendingBit(EXTI_Line2);
}



/***********************************************************************
以上对中断函数的配置
************************************************************************/













