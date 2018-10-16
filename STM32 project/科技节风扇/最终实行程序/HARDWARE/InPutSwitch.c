#include "InPutSwitch.h"
#include "PWM.h"
int16_t Fan_MODE_SW=1;//����ģʽ������Ĭ��Ϊ�ֶ�ģʽ
int16_t Humidifier_MODE_SW=1;//��ʪ��ģʽ������Ĭ��Ϊ�ֶ�ģʽ
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��0.

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //�����ж�ӳ�䵽PB.3

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY3
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//����Ϊ�����ش����ж�
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //KEY4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//�����ж�ӳ�䵽PB.4
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���+
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);//�����ж�ӳ�䵽PB.4
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���+
  
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);//�����ж�ӳ�䵽PB.5
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);//�����ж�ӳ�䵽PB.6
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
   
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);//�����ж�ӳ�䵽PB.7
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
   
/***********************
���Ϻ���Ϊ�����ⲿ�ж���
************************/
 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
 
 NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
}
void EXTI9_5_IRQHandler(void)
      {
   delay_ms(10);
//   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)//�жϰ�ť�Ƿ���
//   {
//      Fan_MODE_SW=!Fan_MODE_SW;//ģʽ�л�
//      LED0=!LED0;
//      EXTI_ClearITPendingBit(EXTI_Line5);
//   }
//   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1)//�ٴ��жϰ�ť�Ƿ���
//   {
//      Humidifier_MODE_SW=!Humidifier_MODE_SW;//�л���ʪ������ģʽ
//      LED4=!LED4;
//      EXTI_ClearITPendingBit(EXTI_Line6);//����жϱ�־λ
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
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)//�жϰ�ť�Ƿ���
   {
      Fan_MODE_SW=!Fan_MODE_SW;//ģʽ�л�
      LED0=!LED0;
   }
   EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void)
{
   delay_ms(10);
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)//�ٴ��жϰ�ť�Ƿ���
   {
      Humidifier_MODE_SW=!Humidifier_MODE_SW;//�л���ʪ������ģʽ
      LED4=!LED4;
   }
    EXTI_ClearITPendingBit(EXTI_Line1);//����жϱ�־λ
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
���϶��жϺ���������
************************************************************************/













