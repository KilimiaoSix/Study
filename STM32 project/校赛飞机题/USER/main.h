#ifndef __MAIN_H
#define __MAIN_H


#include "sys.h"
#include "wave.h"
#include "pwm.h"
#include "pid.h"
#include "usart.h"
#include "timer.h"
#include "io.h"
#include "control.h"
#include "DateUpdate.h"
#define XMiddle 80
#define YMiddle 60
extern int Find_flag;
extern int subject_flag;
extern PIDTypeDef XStruct,YStruct,ZStruct,HStruct;
extern int Take_flag;
extern int Land_flag;
extern int Forward_Flag,Back_Flag,Left_Flag,Right_Flag;
extern int Rise_Flag,Down_Flag;
extern int LeftHand_Flag,RightHand_Flag;
extern int Reset_Flag;
extern int Stop_Flag;
extern int Unlock_Flag;
#endif











