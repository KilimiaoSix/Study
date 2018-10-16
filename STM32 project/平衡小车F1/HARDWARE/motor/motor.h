#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#define PWMA   TIM1->CCR4  //PA11
#define AIN2   PBout(12)
#define AIN1   PBout(13)
#define BIN1   PBout(14)
#define BIN2   PBout(15)
#define PWMB   TIM1->CCR1  //PA8
#define LEFT_VAL PWMA
#define RIGHT_VAL PWMB
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);




#endif


