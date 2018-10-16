#ifndef __PWM_H
#define __PWM_H


#define Psc_PWM 720     //PWM��Ԥ��Ƶϵ��Ϊ720
#define Arr_PWM 2000  //PWM��Ԥ����װ��ֵΪ2000
//PWMƵ��Ϊ(72M/720)/2000=50Hz
#define EM_Disable 0

#define CCR_MAX 200
#define CCR_MIN 100
#define Motor_reference_value 120
#define Motor_MAX 160
#define Motor_MIN 100

#include "sys.h"
#include "usart.h"
void PWM_Init(u32 arr,u32 psc);

#endif









