#include "PID.h"
#include "function.h"
#include "math.h"
//本文件为PID控制的各个模块函数
//分别为高度PID，偏航角外环PID，偏航角内环PID
//旋转角外环PID，旋转角内环PID
//翻滚角外环PID
float PID_controller(PIDTypeDef *PIDStructure,float realval)
{
   float Output;
   PIDStructure->err=PIDStructure->goal-realval;
   PIDStructure->intergral+=PIDStructure->err;
   Output=PIDStructure->Kp*PIDStructure->err+PIDStructure->Ki*PIDStructure->intergral+PIDStructure->Kd*(PIDStructure->err-PIDStructure->last_err);
   //执行公式Output=Kp*Err+Ki*Intergral+Kd*(Err-Last_Err)
   PIDStructure->last_err=PIDStructure->err;
   return Output;
}
float PID_Angel_controller(PIDTypeDef *ExAngel,PIDTypeDef *InAngel,float angel,float Avelocity)
{
   float ExOutput,InOutput;
   ExOutput=PID_controller(ExAngel,angel);
   InAngel->goal=ExOutput;
   InOutput=PID_controller(InAngel,Avelocity);
   return InOutput;
}
void Drive_Motor(PIDTypeDef *ExRoll,PIDTypeDef *InRoll,PIDTypeDef *ExPitch,PIDTypeDef *InPitch,PIDTypeDef *ExYaw,PIDTypeDef *InYaw,PIDTypeDef *H,float pitch,float roll,float yaw,short *gx,short *gy,short *gz)
{
   float Xout=0,Yout=0,Zout=0,Hout=0;
   front_val=0;
   reat_val=0;
   left_val=0;
   right_val=0;
   Xout=PID_Angel_controller(ExRoll,InRoll,roll,(float)(*gx));
   Yout=PID_Angel_controller(ExPitch,InPitch,pitch,(float)(*gy));
   Zout=PID_Angel_controller(ExYaw,InYaw,yaw,(float)(*gz));
   Hout=PID_controller(H,high);
   front_val=Xout-Yout+Zout+Hout;
   reat_val=-Xout+Yout+Zout+Hout;
   left_val=Xout-Yout-Zout+Hout;
   right_val=-Xout+Yout-Zout+Hout;
   Front_motor_control(front_val);
   Reat_motor_control(reat_val);
   left_motor_control(left_val);
   right_motor_control(right_val);
}
void PID_Init(PIDTypeDef *ExRoll,PIDTypeDef *InRoll,PIDTypeDef *ExPitch,PIDTypeDef *InPitch,PIDTypeDef *ExYaw,PIDTypeDef *InYaw,PIDTypeDef *H,float *pitch,float *roll,float *yaw,short *gx,short *gy,short *gz,short *ax,short *ay,short *az,Filterspace *pPitch,Filterspace *pRoll,Filterspace *pYaw,Filterspace *pgx,Filterspace *pgy,Filterspace *pgz,Filterspace *pH)
{
   datelist_init(pitch,roll,yaw,H,gx,gy,gz,ax,ay,az,pPitch,pRoll,pYaw,pgx,pgy,pgz,pH);
   //以上为传感器初始化
   ExRoll->Kd=0;//关闭外环微分调节
   ExPitch->Kd=0;
   ExYaw->Kd=0;
   InRoll->Ki=0;//关闭内环积分调节
   InPitch->Ki=0;
   InYaw->Ki=0;
   ExRoll->goal=AveDate(pRoll);
   ExPitch->goal=AveDate(pPitch);
   ExYaw->goal=AveDate(pYaw);
   InRoll->goal=AveDate(pgx);
   InRoll->goal=AveDate(pgy);
   InRoll->goal=AveDate(pgz);//角度PID控制器的参量初始化//将放平时的量设为初始量，消除静态误差
   ExRoll->Kp=0;
   ExRoll->Ki=0;
   InRoll->Kp=0;
   InRoll->Kd=0;
   ExPitch->Kp=0;
   ExPitch->Ki=0;
   InPitch->Kp=5;
   InPitch->Kd=0;
   ExYaw->Kp=0;
   ExYaw->Ki=0;
   InYaw->Kp=0;
   InYaw->Kd=0;
   //本程序角度PID调节采用外环PI控制，内环PD控制
   //高度PID采用单一PID控制器
   H->goal=AveDate(pH);
   H->Kp=0;
   H->Ki=0;
   H->Kd=0;  //初始化高度PID控制器相关参数，默认设定初始高度为最开始的高度
   DelateSpace(pgx);DelateSpace(pgy);DelateSpace(pgz);
}


