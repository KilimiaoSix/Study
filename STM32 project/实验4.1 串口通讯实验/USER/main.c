#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
char x[200],y[200];
int flag;
int i=0,j=0;
int x0,y0;
 void My_USART1_Init(void)
 {
	 USART_InitTypeDef USART_InitStructure;//����ṹ�����USART_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;//����ṹ�����NVIC_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ�ܴ���1ʱ�ӣ�
	 
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ�ӣ�
	 
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);//��GPIOA9,GPIOA10ӳ�䵽����1

	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;//��Pin9��Pin10���ã�
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//����ģʽΪ����ģʽ��
	 GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//��������
	 GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//����Ϊ�������ģʽ
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//����Ƶ��Ϊ100MHz
	 GPIO_Init(GPIOA,&GPIO_InitStructure);//���ó�ʼ������
	 
	 USART_InitStructure.USART_BaudRate=115200;//���ò�����Ϊ115200
	 USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	 USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//����ģʽΪ���������
	 USART_InitStructure.USART_Parity=USART_Parity_No;//���ò�������żУ��
	 USART_InitStructure.USART_StopBits=USART_StopBits_1;//����ֹͣλΪ1��
	 USART_InitStructure.USART_WordLength=USART_WordLength_8b;//�������ֳ�Ϊ��λ
	 USART_Init(USART1,&USART_InitStructure);//���ó�ʼ������
	 
	 USART_Cmd(USART1,ENABLE);//ʹ�ܴ���1
	 
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ʹ���ж�
	 
	 NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//����ͨ��Ϊ����1
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ��
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//������ռ���ȼ�Ϊ1
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//������Ӧ���ȼ�Ϊ1
	 NVIC_Init(&NVIC_InitStructure);//���ó�ʼ������
 }
 void USART1_IRQHandler(void)
 {
	 u8 res;
	 if(USART_GetITStatus(USART1,USART_IT_RXNE))//����������ж�
	 {
		 res=USART_ReceiveData(USART1);//���ܴ���1������
       if(res=='(')
       {
          flag=1;
          i=0;
       }
       else if(flag==1&&res!=','&&res!=')')
       {
          x[i]=res;
          i++;
       }
       else if(res==',')
       {
          flag=2;
          j=0;
       }
       else if(flag==2&&res!=')')
       {
          y[j]=res;
          j++;
       }
       else if(res==')')
       {
          flag=0;
       }
		 USART_SendData(USART1,res);//������1��������
	 }
	 
 }
 int main()
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����жϷ���
	 My_USART1_Init();//��ʼ������1
	 while(1)
    {
       if(flag==0)
       {
          switch(i+1)
          {
             case 1:
                x0=x[0];break;
             case 2:
                x0=x[0]*10+x[1];break;
             case 3:
                x0=x[0]*100+x[1]*10+x[2];break;
             case 4:
                x0=x[0]*1000+x[1]*100+x[2]*10+x[3];break;
             default:break;
          }
          switch(j+1)
          {
             case 1:
                y0=y[0];break;
             case 2:
                y0=y[0]*10+y[1];break;
             case 3:
                y0=y[0]*100+y[1]*10+y[2];break;
             case 4:
                y0=y[0]*1000+y[1]*100+y[2]*10+y[3];break;
             default:break;
          }
          printf("%d,%d\r\n",x0,y0);
       }
    }
 }
 


