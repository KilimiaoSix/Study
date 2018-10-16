#ifndef __ECHO_H
#define __ECHO_H
#include "sys.h"
#include "delay.h"
#include "timer.h"
#define TRIG_High GPIO_SetBits(GPIOC,GPIO_Pin_15)
#define TRIG_Low GPIO_ResetBits(GPIOC,GPIO_Pin_15)
void Echo_Init(u16 arr,u16 psc);
void Sonic_Trig(void);
void ECHO_Update(void);

extern float high;
void Get_High(void);
extern u8  TIM5CH2_CAPTURE_STA;	// ‰»Î≤∂ªÒ◊¥Ã¨		    				
extern u16	TIM5CH2_CAPTURE_VAL;	// ‰»Î≤∂ªÒ÷

#endif






