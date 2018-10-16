#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "beep.h"
#include "key.h"
int main(void)
{
	u8 key;
	delay_init(168);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	while(1)
	{
		if(key)
		{
			switch(key)
			{
				case (KEY0_PRES):
					LED1=!LED1;break;
				case (KEY1_PRES):
					LED2=!LED2;break;
				case (KEY2_PRES):
				{
					LED1=!LED1;
					LED2=!LED2;
				}break;
				case	(WKUP_PRES):
					BEEP=!BEEP;break;
			}
		}
		else
			delay_ms(10);
	}
		
}