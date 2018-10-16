#include "pid.h"
int PID_Controller(PIDTypeDef *PIDStructure,float realval)
{
   float Err=0,Derivative=0;  //偏差值，微分值
   int Output=0;  //输出
   Err=PIDStructure->Goal-realval;  //计算偏差值
   Derivative=Err-PIDStructure->Last_Err;  //计算微分值
   PIDStructure->integral+=Err;  //计算积分值
   Output=PIDStructure->Kp*Err+PIDStructure->Ki*PIDStructure->integral+PIDStructure->Kd*Derivative;  //PID控制运算
   PIDStructure->Last_Err=Err;  //把这次的偏差值存储，为下次微分运算做准备
   return Output;
}
void PID_Init(PIDTypeDef *P,float Kp,float Kd,float Ki,float goalval,float realval)
{
   P->integral = 0;
   P->Goal = goalval;
   P->Kd = Kd;
   P->Kp = Kp;
   P->Ki = Ki;
   P->Last_Err=0;
   PID_Controller(P,realval);
}














