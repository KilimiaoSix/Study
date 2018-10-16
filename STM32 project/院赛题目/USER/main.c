#include "key.h"
#include "exti.h"
#include "pwm.h"
#include "led.h"
#include "adc.h"
#include "sys.h"
#include "usart.h"
#include "tim.h"
#include "oled.h"
int main(void)
{
   float cycle=0;
   u8 tbuf[40];
   float Duty_cycle1,Duty_cycle2;
   u16 adc1=0,adc2=0;
   double temp1,temp2;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   delay_init(168);
   uart_init(115200);
   LED_Init();  
   OLED_Init();
   delay_ms(1000);
   EXTIX_Init();
   My_ADC1_Init();
   My_ADC2_Init();
   TIM4_Init(9999,8399);
   TIM5_Init(99,8399);
   PWM1_Init(10000-1,84-1);
   PWM2_Init(10000-1,168-1);
   LED_Change_Init(500-1,168-1);
   arr1=10000;
   arr2=10000;
   led_arr=500;
   TIM_SetCompare1(TIM14,0);
   TIM_SetCompare1(TIM11,0);
   frequency1=1000000/arr1;
   frequency2=1000000/arr2;
   OLED_ShowString(8,0,"Init Test");
   delay_ms(1000);
   OLED_Clear();
   while(1)
   {
      adc1=Get_Adc1_Average(ADC_Channel_5,20);
      adc2=Get_Adc2_Average(ADC_Channel_6,20);
      temp1=(float)adc1*(3.3/4096);
      temp2=(float)adc2*(3.3/4096);
      ADC_Compare(temp1,temp2); 
      cycle=led_arr*10*0.001;
      Duty_cycle1=((float)pwm1val/arr1)*100;
      Duty_cycle2=((float)pwm2val/arr2)*100;
      delay_ms(10);
      switch(i)
      {
         case 1:
         {
            sprintf((char*)tbuf,"PWM1 %dHz %d%%",0,0);
            OLED_ShowString(8,0,tbuf);
            sprintf((char*)tbuf,"PWM2 %dHz %d%%",0,0);
            OLED_ShowString(8,2,tbuf);
         }break;
         case 2:
         {
            sprintf((char*)tbuf,"PWM1 %dHz %0.2f%%",frequency1,Duty_cycle1);
            OLED_ShowString(8,0,tbuf);
            sprintf((char*)tbuf,"PWM2 %dHz %0.2f%%",0,0.0);
            OLED_ShowString(8,2,tbuf);
         }break;                                                           
         case 3:
         {
            sprintf((char*)tbuf,"PWM1 %dHz %0.2f%%",0,0.0);
            OLED_ShowString(8,0,tbuf);
            sprintf((char*)tbuf,"PWM2 %dHz %0.2f%%",frequency2,Duty_cycle2);
            OLED_ShowString(8,2,tbuf);

         }break;
         case 0:
         {
            sprintf((char*)tbuf,"PWM1 %dHz %d%%",frequency1,(int)Duty_cycle1);
            OLED_ShowString(8,0,tbuf);
            sprintf((char*)tbuf,"PWM2 %dHz %d%%",frequency2,(int)Duty_cycle2);
            OLED_ShowString(8,2,tbuf);

         }break;
         
      }
      sprintf((char*)tbuf,"cycle:%0.1fs",cycle);
      OLED_ShowString(8,4,tbuf);
      LED0=!LED0;
   }
}




