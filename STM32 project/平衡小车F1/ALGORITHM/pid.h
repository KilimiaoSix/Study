#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "math.h"

//PID控制器结构体
typedef struct{
   float Kp,Ki,Kd;
}PIDTypeDef;

void PID_Init(PIDTypeDef *P,float Kp,float Ki,float Kd);

#endif



