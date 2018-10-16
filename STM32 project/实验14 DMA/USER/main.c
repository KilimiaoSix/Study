#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "dma.h"
#include "key.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
#define SEND_BUF_SIZE 8200	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

u8 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区
const u8 TEXT_TO_SEND[]={"ALIENTEK Explorer STM32F4 DMA 串口实验"};	 

  
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
	POINT_COLOR=BLUE;//设置字体为蓝色  
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
         LCD_ShowNum(30,170,100,3,16);//显示100%	  
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");//提示传送完成
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
手册中讲解到步骤15的时候的main.c源码如下：
#include "stm32f4xx.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
  
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


