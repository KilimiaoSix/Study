#ifndef __PWM_H
#define __PWM_H


#define Psc_PWM 72     //PWM的预分频系数为720
#define Arr_PWM 20000  //PWM的预定重装载值为2000
//PWM频率为(72M/72)/20000=50Hz
#define EM_Disable 0

#define CCR_MAX 2000
#define CCR_MIN 1000
#define Motor_reference_value 1200
#define Motor_MAX 1600
#define Motor_MIN 1000

#include "sys.h"
#include "usart.h"
void PWM_Init(u32 arr,u32 psc);

#endif









