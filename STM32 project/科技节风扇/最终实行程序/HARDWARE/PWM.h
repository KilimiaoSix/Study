#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#include "led.h"

#define GEAR_1 1000
#define GEAR_2 4000
#define GEAR_3 7000




void TIM4_PWM_Init(u16 arr,u16 psc);
void Set_PWM(u16 pwminput);



#endif





