#ifndef __ECHO_H
#define __ECHO_H
#include "sys.h"
#include "delay.h"

#define TRIG_High GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define TRIG_Low GPIO_ResetBits(GPIOB,GPIO_Pin_8)
void Echo_Init(u32 arr,u32 psc);
void Sonic_Trig(void);
void ECHO_Update(void);
extern u8  TIM4CH4_CAPTURE_STA;	//���벶��״̬		    				
extern u32	TIM4CH4_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
extern float high;


#endif






