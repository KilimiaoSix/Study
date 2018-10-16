#ifndef __PID_H
#define __PID_H

#include "Echo.h"
#include "IMU.h"
#include "sys.h"
#include "Avefiltering.h"
/*float 	yaw,  //偏航角
		pitch,//俯仰
		roll, //滚转
		alt,  //高度
		tempr,//温度
		press;//气压
int16_t ax, ay, az;//加速度计
int16_t gx, gy, gz;//陀螺仪
int16_t hx, hy, hz;//磁力计
------------------------------------
*/
//PID控制器参数结构体
typedef struct{
   float goal;
   float err;
   float last_err;
   float Kp,Ki,Kd;
   float intergral;
}PIDTypeDef;


float PID_controller(PIDTypeDef *PIDStructure,float realval);
float PID_Angel_controller(PIDTypeDef *ExAngel,PIDTypeDef *InAngel,float angel,float Avelocity);
void Drive_Motor(PIDTypeDef *ExRoll,PIDTypeDef *InRoll,PIDTypeDef *ExPitch,PIDTypeDef *InPitch,PIDTypeDef *ExYaw,PIDTypeDef *InYaw,PIDTypeDef *H,float pitch,float roll,float yaw,short *gx,short *gy,short *gz);
void PID_Init(PIDTypeDef *ExRoll,PIDTypeDef *InRoll,PIDTypeDef *ExPitch,PIDTypeDef *InPitch,PIDTypeDef *ExYaw,PIDTypeDef *InYaw,PIDTypeDef *H,float *pitch,float *roll,float *yaw,short *gx,short *gy,short *gz,short *ax,short *ay,short *az,Filterspace *pPitch,Filterspace *pRoll,Filterspace *pYaw,Filterspace *pgx,Filterspace *pgy,Filterspace *pgz,Filterspace *pH);
#endif



