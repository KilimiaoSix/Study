#ifndef __PWM_H
#define __PWM_H

#include "sys.h"

#define EM_Disable 0

#define PITCH     TIM3->CCR3
#define ROLL      TIM3->CCR4
#define YAW       TIM3->CCR1
#define THROTTLE  TIM3->CCR2
#define MODE      TIM1->CCR4
//#define CCR_MIN    1000
//#define CCR_MIDDLE 1500
//#define CCR_MAX    2000

#define YAW_MAX    2000
#define YAW_MIN    1000
#define YAW_MIDDLE 1500

#define PITCH_MAX  2020
#define PITCH_MIN  1020
#define PITCH_MIDDLE 1520

#define ROLL_MAX   2000
#define ROLL_MIN   1000
#define ROLL_MIDDLE 1500

#define THROTTLE_MAX 2020
#define THROTTLE_MIN 1020
#define THROTTLE_MIDDLE 1520

#define MODE_MAX 2030
#define MODE_MIN 1030
#define MODE_MIDDLE 1530  //вкл╛дёй╫

#define Standard_VAL 1600

void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM1_PWM_Init(u32 arr,u32 psc);
#endif




