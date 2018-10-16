#include "led.h"
/**************************************************************************
函数功能：LED接口初始化
入口参数：无 
返回  值：无
**************************************************************************/
void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能端口时钟
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;	          //端口配置
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
   GPIO_Init(GPIOA, &GPIO_InitStructure);		
   
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭JTAG 使PA15可以被正常的使用
   
   LED0=1;
   LED1=1;
   delay_ms(1000);
   LED0=0;
   LED1=0;
   delay_ms(1000);
   //板子上显示为两个灯闪烁,之后一盏灯亮，一盏灯灭，说明初始化完毕
   LED0=1;
   LED1=0;
}



