#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "dma.h"
#include "key.h"

//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
#define SEND_BUF_SIZE 8200	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
const u8 TEXT_TO_SEND[]={"ALIENTEK Explorer STM32F4 DMA ����ʵ��"};	 

  
int main(void)
{
   u16 i;
   u8 t=0;
   u8 j,mask=0;
   float pro=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   delay_init(168);
   uart_init(115200);
   LED_Init();
   LCD_Init();
   KEY_Init();
   My_DMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);
   POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"DMA TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	LCD_ShowString(30,130,200,16,16,"KEY0:Start");	 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ  
   j=sizeof(TEXT_TO_SEND);
   for(i=0;i<SEND_BUF_SIZE;i++)
   {
      if(t>=j)
      {
         if(mask)
         {
            SendBuff[i]=0x0a;
            t=0;
         }else
         {
            SendBuff[i]=0x0d;
            mask++;
         }
      }else
      {
         mask=0;
         SendBuff[i]=TEXT_TO_SEND[t];
         t++;
      }
   }
   POINT_COLOR=BLUE;
   i=0;
   while(1)
   {
      t=KEY_Scan(0);
      if(t==KEY0_PRES)
      {
         printf("\r\nDMA DATA:\r\n");
         LCD_ShowString(30,150,200,16,16,"Start Transimit...");
         LCD_ShowString(30,170,200,16,16,"   %");
         USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
         MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);
         while(1)
         {
            if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET)
            {
               DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
               break;
            }
            pro=DMA_GetCurrDataCounter(DMA2_Stream7);
            pro=1-pro/SEND_BUF_SIZE;
            pro*=100;
            LCD_ShowNum(30,170,pro,3,16);
         }
         LCD_ShowNum(30,170,100,3,16);//��ʾ100%	  
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");//��ʾ�������
      }
         i++;
         delay_ms(10);
         if(i==20)
         {
            LED0=!LED0;   
            i=0;
         }
         
   }
      

}

/*
�ֲ��н��⵽����15��ʱ���main.cԴ�����£�
#include "stm32f4xx.h"

//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
  
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while(1){
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
	
	}
}
*/


