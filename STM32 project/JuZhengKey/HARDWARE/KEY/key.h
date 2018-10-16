#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"




#define  PortF   (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)

#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)//��ȡ����2  
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)//��ȡ����0
#define KEY4  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)//��ȡ����1
#define KEY5  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)//��ȡ����2 
#define KEY6  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)//��ȡ����0
#define KEY7  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)//��ȡ����1
//#define KEY8  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)//��ȡ����1

 

#define KEY0_PRES 1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����
#define KEY3_PRES 4	//KEY3����
#define KEY4_PRES	5	//KEY4����
#define KEY5_PRES	6	//KEY5����
#define KEY6_PRES 7	//KEY6����
#define KEY7_PRES	8	//KEY7����


void KEY_Init(void);
u8 keyscan(void);
u8 keychuli(void);

#endif


