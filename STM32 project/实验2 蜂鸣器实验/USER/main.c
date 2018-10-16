#include<BEEP.h>
#include<sys.h>
#include<delay.h>
int main()
{
	BEEP_Init();
	delay_init(168);
	while(1)
	{
		BEEP=1;
		LED1=1;
		LED2=1;
		delay_ms(500);
		BEEP=0;
		LED1=0;
		LED2=0;
		delay_ms(500);
	}
	return 0;
}

