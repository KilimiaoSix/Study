#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
extern u32 arr1,arr2,led_arr;
extern u16 pwm1val,pwm2val;
extern u16 ledchange_val;
extern int frequency1,frequency2;
void PWM1_Init(u32 arr,u32 prc);
void PWM2_Init(u32 arr,u32 prc);
void LED_Change_Init(u32 arr,u32 prc);












#endif



















