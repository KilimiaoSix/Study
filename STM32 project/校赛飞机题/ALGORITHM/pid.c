#include "pid.h"
int PID_Controller(PIDTypeDef *PIDStructure,float realval)
{
   float Err=0,Derivative=0;  //ƫ��ֵ��΢��ֵ
   int Output=0;  //���
   Err=PIDStructure->Goal-realval;  //����ƫ��ֵ
   Derivative=Err-PIDStructure->Last_Err;  //����΢��ֵ
   PIDStructure->integral+=Err;  //�������ֵ
   Output=PIDStructure->Kp*Err+PIDStructure->Ki*PIDStructure->integral+PIDStructure->Kd*Derivative;  //PID��������
   PIDStructure->Last_Err=Err;  //����ε�ƫ��ֵ�洢��Ϊ�´�΢��������׼��
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














