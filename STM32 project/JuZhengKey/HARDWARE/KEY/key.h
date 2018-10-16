#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"




#define  PortF   (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)

#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)//读取按键2  
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)//读取按键0
#define KEY4  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)//读取按键1
#define KEY5  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)//读取按键2 
#define KEY6  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)//读取按键0
#define KEY7  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)//读取按键1
//#define KEY8  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)//读取按键1

 

#define KEY0_PRES 1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define KEY3_PRES 4	//KEY3按下
#define KEY4_PRES	5	//KEY4按下
#define KEY5_PRES	6	//KEY5按下
#define KEY6_PRES 7	//KEY6按下
#define KEY7_PRES	8	//KEY7按下


void KEY_Init(void);
u8 keyscan(void);
u8 keychuli(void);

#endif


