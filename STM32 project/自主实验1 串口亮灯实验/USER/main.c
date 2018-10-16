#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{
		res=USART_ReceiveData(USART1);
		switch(res)
		{
			case '1':
				LED0=!LED0;break;
			case '2':
				LED1=!LED1;break;
			case 'f':
			{
				LED0=0;
				LED1=0;
			}break;
			case 'o':
			{
				LED0=1;
				LED1=1;
			}break;
			case 's':
			{
				LED0=!LED0;
				LED1=!LED1;
				PFout(8)=1;
				delay_ms(100);
				PFout(8)=0;
			}break;
			default:
				break;
		}
		printf("\r\n÷¥––ÕÍ±œ£°\r\n");
	}
}
	
int main(void)
{
	u8 USART1_GetSavep[200]={0};
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	BEEP_Init();
	delay_init(168);
	uart_init(115200);
	while(1);
}



















