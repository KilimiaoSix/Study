#include "stm32f10x.h"
#include "usart.h"
#include "sys.h"
#include "MiniMIU.h"
#include "delay.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	
    delay_init();
    uart_init1(115200);
    while(1)
    {
       UART2_CommandRoute();
       printf("\t\nax=%d\t\n",ax);
       printf("\t\nay=%d\t\n",ay);
       printf("\t\naz=%d\t\n",az);
    }
 }

 
 
 
 
 
 