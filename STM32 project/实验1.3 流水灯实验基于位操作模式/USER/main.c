#include "stm32f4xx.h"
#include "LED.h"
#include "delay.h"
int main()
{
	int i,j;
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	delay_init(168);
	LED_Init();
	while(1)
	{
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			    PFout(a[j])=0;
			PFout(a[i])=1;
			delay_ms(500);
	  }
  }
	return 0;
}

 