#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "ADC.h"
#include "DAC.h"
#include "LCD.h"
#include "key.h"
#include "LED.h"
int main(void)
{
   u16 adcx;
   float temp;
   u8 t=0,key;
   u16 dacval=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   delay_init(168);
   uart_init(115200);
   LED_Init();
   LCD_Init();
   My_ADC_Init();
   DAC1_Init();
   POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	LCD_ShowString(30,130,200,16,16,"WK_UP:+  KEY1:-");	 
	POINT_COLOR=BLUE;//设置字体为蓝色      	 
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");
   	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(dacval<4000)dacval+=200;
			DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//设置DAC值
		}else if(key==2)	
		{
			if(dacval>200)dacval-=200;
			else dacval=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//设置DAC值
		}	 
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
		{	  
 			adcx=DAC_GetDataOutputValue(DAC_Channel_1);//读取前面设置DAC的值
			LCD_ShowxNum(94,150,adcx,4,16,0);     	   //显示DAC寄存器值
			temp=(float)adcx*(3.3/4096);			         //得到DAC电压值
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	   //显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0X80); 	   //显示电压值的小数部分
 			adcx=Get_Adc_Average(ADC_Channel_5,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			        //得到ADC电压值
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	  //显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0X80); 	  //显示电压值的小数部分
			LED0=!LED0;	   
			t=0;
		}	    
		delay_ms(10);	 
	}	
   
}




