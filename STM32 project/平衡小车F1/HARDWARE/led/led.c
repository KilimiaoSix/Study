#include "led.h"
/**************************************************************************
�������ܣ�LED�ӿڳ�ʼ��
��ڲ������� 
����  ֵ����
**************************************************************************/
void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;	          //�˿�����
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
   GPIO_Init(GPIOA, &GPIO_InitStructure);		
   
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//�ر�JTAG ʹPA15���Ա�������ʹ��
   
   LED0=1;
   LED1=1;
   delay_ms(1000);
   LED0=0;
   LED1=0;
   delay_ms(1000);
   //��������ʾΪ��������˸,֮��һյ������һյ����˵����ʼ�����
   LED0=1;
   LED1=0;
}



