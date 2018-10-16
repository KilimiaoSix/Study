#ifndef __PID_H
#define __PID_H

#include "Echo.h"
#include "IMU.h"
#include "sys.h"


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

//高度PID参数
typedef struct{
   float goal_high;  //目标高度
   float real_high;  //实际高度
   float err_high;   //高度误差
   float err_last_high;  //上一次的高度误差
   float Kp_high,Ki_high,Kd_high;  //PID参数
   float integral_high;  //高度误差积分
   int PWM_OutPut_high;  //高度相关的PWM输出
}PID_High;

//偏航角外环PID参数
typedef struct{
   float goaL_yaw;  //目标偏航角
   float real_yaw;  //实际偏航角
   float err_yaw;   //偏航角误差
   float Kp_external_yaw,Ki_external_yaw;  //外环PID参数
   float intergral_external_yaw;  //偏航角误差积分
   float External_OutPut_yaw;  //外环输出
}PID_external_Yaw;

//偏航角内环PID参数
typedef struct{
   float External_InPut_yaw;  //外环PID输入
   float real_angular_velocity_yaw;  //实际角速度
   float err_angular_velocity_yaw;  //角速度误差
   float err_last_angular_velocity_yaw;
   float Kp_inside_yaw,Ki_inside_yaw,Kd_inside_yaw;  //内环PID参数
   float intergral_inside_yaw;  //角速度误差积分
   int PWM_OutPut_yaw;  //偏航角相关的PWM输出
}PID_inside_Yaw;

//俯仰角外环PID参数
typedef struct{
   float goaL_pitch;  //目标俯仰角
   float real_pitch;  //实际俯仰角
   float err_pitch;   //俯仰角误差
   float Kp_external_pitch,Ki_external_pitch;  //外环PID参数
   float intergral_external_pitch;  //俯仰角误差积分
   float External_OutPut_pitch;  //外环输出
}PID_external_Pitch;

//俯仰角内环PID参数
typedef struct{
   float External_InPut_pitch;  //外环PID输入
   float real_angular_velocity_pitch;  //实际角速度
   float err_angular_velocity_pitch;  //角速度误差
   float Kp_inside_pitch,Ki_inside_pitch,Kd_inside_pitch;  //内环PID参数
   float intergral_inside_pitch;  //角速度误差积分
   float err_last_angular_velocity_pitch;
   int PWM_OutPut_pitch;  //俯仰角相关的PWM输出
}PID_inside_Pitch;

//翻滚角外环PID参数
typedef struct{
   float goaL_roll;  //目标翻滚角
   float real_roll;  //实际翻滚角
   float err_roll;   //翻滚角误差
   float Kp_external_roll,Ki_external_roll;  //外环PID参数
   float intergral_external_roll;  //翻滚角误差积分
   float External_OutPut_roll;  //外环输出
}PID_external_Roll;

//翻滚角内环PID参数
typedef struct{
   float External_InPut_roll;  //外环PID输入
   float real_angular_velocity_roll;  //实际角速度
   float err_angular_velocity_roll;  //角速度误差
   float Kp_inside_roll,Ki_inside_roll,Kd_inside_roll;  //内环PID参数
   float intergral_inside_roll;  //角速度误差积分
   float err_last_angular_velocity_roll;
   int PWM_OutPut_roll;  //偏航角相关的PWM输出
}PID_inside_Roll;


extern PID_High PID_HighStucutre;
extern PID_external_Yaw PID_external_YawStructure;
extern PID_external_Pitch PID_external_PitchStructure;
extern PID_external_Roll PID_external_RollStructure;
extern PID_inside_Pitch PID_inside_PitchStructure;
extern PID_inside_Roll PID_inside_RollStructure;
extern PID_inside_Yaw PID_inside_YawStructure;


void PID_Init(void);

int PID_Controller_High(PID_High *PID_HighStructure,float HIGH);
float PID_Controller_external_Yaw(PID_external_Yaw *PID_external_YawStructure,float YAW);
float PID_Controller_external_Pitch(PID_external_Pitch *PID_external_PitchStructure,float PITCH);
float PID_Controller_external_Roll(PID_external_Roll *PID_external_RollStructure,float ROLL);
int PID_Controller_inside_Yaw(PID_inside_Yaw *PID_inside_YawStructure,float External_OutPut_yaw,float AZ);
int PID_Controller_inside_Pitch(PID_inside_Pitch *PID_inside_PitchStructure,float External_OutPut_Pitch,float AY);
int PID_Controller_inside_Roll(PID_inside_Roll *PID_inside_RollStructure,float External_OutPut_Roll,float AX);

void highPID_Kpchange(float Kp);
void highPID_Kichange(float Ki);
void highPID_Kdchange(float Kd);
#endif


