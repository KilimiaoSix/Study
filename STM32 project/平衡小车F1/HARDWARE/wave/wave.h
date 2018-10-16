#ifndef __WAVE_H
#define __WAVE_H

#include "sys.h"
#include "delay.h"

#define TRIG_HIGH GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define TRIG_LOW  GPIO_ResetBits(GPIOB,GPIO_Pin_1)
void TIM3_Cap_Init(u16 arr,u16 psc);
void Get_Distane(u32 *Distance);



#endif


