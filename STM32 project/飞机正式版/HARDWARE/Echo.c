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
   GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA0 ����
   
//   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
//   
//	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
// 	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
// 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// 	EXTI_Init(&EXTI_InitStructure);
//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
   
   //��ʼ��TIM5���벶�����
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
  
   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;	
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;				
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
 	NVIC_Init(&NVIC_InitStructure); 
   
   TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
   	TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��5
      printf("������ģ���ʼ����ϣ���!\r\n");
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
//   EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
//}
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ

void TIM2_IRQHandler(void)
{
   
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//����2���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture2(TIM2);
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
 
}
