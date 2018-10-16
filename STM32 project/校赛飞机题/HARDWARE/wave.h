#ifndef __ECHO_H
#define __ECHO_H
#include "sys.h"
#include "delay.h"

#define TRIG_High GPIO_SetBits(GPIOC,GPIO_Pin_15)
#define TRIG_Low  GPIO_ResetBits(GPIOC,GPIO_Pin_15)
void Wave_Init(u16 arr,u16 psc);
void Sonic_Trig(void);
void Get_High(void);
extern u8  TIM2CH2_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH2_CAPTURE_VAL;	//输入捕获值
extern float high;
#endif






 
 
 
 

