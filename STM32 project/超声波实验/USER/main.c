#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LED.h"
#include "pwm.h"
#include "timer.h"
#include "Echo.h"
//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{
   float temp=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   delay_init(168);
   uart_init(115200);
   TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1);
   PWM_Init(500-1,84-1);
   Echo_Init();
   while(1)
   {
      delay_ms(10);
      Sonic_Trig();
      TIM_SetCompare1(TIM14,TIM_GetCapture1(TIM14)+1);
      if(TIM_GetCapture1(TIM14)==300)
      {
         TIM_SetCompare1(TIM14,0);
      }
//   if(TIM4CH4_CAPTURE_STA&0x80)
//      { 
//         temp=TIM4CH4_CAPTURE_STA&0x3F;
//         temp*=0xFFFFFFFF;
//         temp+=TIM4CH4_CAPTURE_VAL;

//         printf("high=%lld\r\n",temp);

//         TIM4CH4_CAPTURE_STA=0;
//       }
      if(TIM5CH1_CAPTURE_STA&0X80)        //???????????
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F; 
			temp*=0XFFFFFFFF;		 		         //??????
			temp+=TIM5CH1_CAPTURE_VAL;		   //?????????
         temp=((temp*0.000001)/2.0)*340.0;
			printf("HIGH:%0.2f m\r\n",temp); //?????????
			TIM5CH1_CAPTURE_STA=0;			     //???????
		}
}
}



