#include "main.h"
int main(void)
{
   uart_init(115200);
   SHT21_Init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   SW_Init();
   EXTIX_Init();
   TIM3_Int_Init(9999,7199);
   TIM4_PWM_Init(7199,0);
   delay_init();
   LED_Init();
   //¶Ô¸÷Ïî²ÎÊý½øÐÐ³õÊ¼»¯£¬¸÷¸öIO¿ÚºÍÍâÉè³õÊ¼»
   LED0=1;
   LED1=1;
   LED2=1;
   LED3=1;
   LED4=1;
   delay_ms(500);
   LED0=0;
   LED1=0;
   LED2=0;
   LED3=0;
   LED4=0;
   Set_PWM(GEAR_3);
   Humidifier=1;
   LED0=1;
   LED4=1;
   while(1)
   {
      UART1_CommandRoute();
      Sleep_Judge();
      if(Fan_MODE_SW)
         Fan_Mode_Auto();
      if(Humidifier_MODE_SW)
         Humidifier_Mode_Auto();
      printf("%f",yaw);
   }
   
   
   
   
   
   
   
   
   
   
   
}







