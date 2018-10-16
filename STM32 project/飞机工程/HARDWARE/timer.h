#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "delay.h"
#include "Echo.h"
#include "LED.h"
extern u8  TIM5CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);


#endif


