#ifndef __PID_H
#define __PID_H
typedef struct
{
   float Kp;
   float Ki;
   float Kd;
   float Goal;
   float Last_Err;
   float integral;
}PIDTypeDef;
int PID_Controller(PIDTypeDef *PIDStructure,float realval);

void PID_Init(PIDTypeDef *P,float Kp,float Kd,float Ki,float goalval,float realval);
#endif






