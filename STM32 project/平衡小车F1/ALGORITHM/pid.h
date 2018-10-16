#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "math.h"

//PID�������ṹ��
typedef struct{
   float Kp,Ki,Kd;
}PIDTypeDef;

void PID_Init(PIDTypeDef *P,float Kp,float Ki,float Kd);

#endif



