#include "PID.h"
#include "function.h"
#include "math.h"
//本文件为PID控制的各个模块函数
//分别为高度PID，偏航角外环PID，偏航角内环PID
//旋转角外环PID，旋转角内环PID
//翻滚角外环PID

//将PID控制器相关系数全局化方便调用
PID_High PID_HighStucutre;
PID_external_Yaw PID_external_YawStructure;
PID_external_Pitch PID_external_PitchStructure;
PID_external_Roll PID_external_RollStructure;
PID_inside_Pitch PID_inside_PitchStructure;
PID_inside_Roll PID_inside_RollStructure;
PID_inside_Yaw PID_inside_YawStructure;






//高度PID控制器
int PID_Controller_High(PID_High *PID_HighStructure,float HIGH)
{
   PID_HighStructure->real_high=HIGH;
   PID_HighStructure->err_high=PID_HighStructure->goal_high-PID_HighStructure->real_high;
   PID_HighStructure->integral_high+=PID_HighStructure->err_high;
   PID_HighStructure->PWM_OutPut_high=PID_HighStructure->Kp_high*PID_HighStructure->err_high+PID_HighStructure->Ki_high*PID_HighStructure->integral_high+PID_HighStructure->Kd_high*(PID_HighStructure->err_high-PID_HighStructure->err_last_high);
   PID_HighStructure->err_last_high=PID_HighStructure->err_high;
   return PID_HighStructure->PWM_OutPut_high;
}

//外环偏航角PID控制
float PID_Controller_external_Yaw(PID_external_Yaw *PID_external_YawStructure,float YAW)
{
   float index=0;
   PID_external_YawStructure->real_yaw=YAW;
   PID_external_YawStructure->err_yaw=PID_external_YawStructure->goaL_yaw-PID_external_YawStructure->real_yaw;
   if(fabs(PID_external_YawStructure->err_yaw)<10)
   {
      PID_external_YawStructure->intergral_external_yaw+=PID_external_YawStructure->err_yaw;
      index=1;
   }
   PID_external_YawStructure->External_OutPut_yaw=PID_external_YawStructure->Kp_external_yaw*PID_external_YawStructure->err_yaw+PID_external_YawStructure->Ki_external_yaw*PID_external_YawStructure->intergral_external_yaw*index;
   return PID_external_YawStructure->External_OutPut_yaw;
}

//内环偏航角PID控制器
int PID_Controller_inside_Yaw(PID_inside_Yaw *PID_inside_YawStructure,float External_OutPut_yaw,float GZ)
{
   PID_inside_YawStructure->External_InPut_yaw=External_OutPut_yaw;
   PID_inside_YawStructure->real_angular_velocity_yaw=GZ;
   PID_inside_YawStructure->err_angular_velocity_yaw=PID_inside_YawStructure->External_InPut_yaw-PID_inside_YawStructure->real_angular_velocity_yaw;
   PID_inside_YawStructure->intergral_inside_yaw+=PID_inside_YawStructure->err_angular_velocity_yaw;
   PID_inside_YawStructure->PWM_OutPut_yaw=PID_inside_YawStructure->Kp_inside_yaw*PID_inside_YawStructure->err_angular_velocity_yaw+PID_inside_YawStructure->Ki_inside_yaw*PID_inside_YawStructure->intergral_inside_yaw+PID_inside_YawStructure->Kd_inside_yaw*(PID_inside_YawStructure->err_angular_velocity_yaw-PID_inside_YawStructure->err_last_angular_velocity_yaw);
   PID_inside_YawStructure->err_last_angular_velocity_yaw=PID_inside_YawStructure->err_angular_velocity_yaw;
   return PID_inside_YawStructure->PWM_OutPut_yaw;
}

//外环俯仰角PID控制器

float PID_Controller_external_Pitch(PID_external_Pitch *PID_external_PitchStructure,float PITCH)
{
   float index=0;
   PID_external_PitchStructure->real_pitch=PITCH;
   PID_external_PitchStructure->err_pitch=PID_external_PitchStructure->goaL_pitch-PID_external_PitchStructure->real_pitch;
   if(fabs(PID_external_PitchStructure->err_pitch)<10)
   {
      PID_external_PitchStructure->intergral_external_pitch+=PID_external_PitchStructure->err_pitch;
      index=1;
   }
   PID_external_PitchStructure->External_OutPut_pitch=PID_external_PitchStructure->Kp_external_pitch*PID_external_PitchStructure->err_pitch;//+PID_external_PitchStructure->Ki_external_pitch*PID_external_PitchStructure->intergral_external_pitch*index;
   return PID_external_PitchStructure->External_OutPut_pitch;
}

//内环俯仰角PID控制器
int PID_Controller_inside_Pitch(PID_inside_Pitch *PID_inside_PitchStructure,float External_OutPut_Pitch,float GY)
{
   PID_inside_PitchStructure->External_InPut_pitch=External_OutPut_Pitch;
   PID_inside_PitchStructure->real_angular_velocity_pitch=GY;
   PID_inside_PitchStructure->err_angular_velocity_pitch=PID_inside_PitchStructure->External_InPut_pitch-PID_inside_PitchStructure->real_angular_velocity_pitch;
   PID_inside_PitchStructure->intergral_inside_pitch+=PID_inside_PitchStructure->err_angular_velocity_pitch;
   PID_inside_PitchStructure->PWM_OutPut_pitch=PID_inside_PitchStructure->Kp_inside_pitch*PID_inside_PitchStructure->err_angular_velocity_pitch;//+PID_inside_PitchStructure->Ki_inside_pitch*PID_inside_PitchStructure->intergral_inside_pitch+PID_inside_PitchStructure->Kd_inside_pitch*(PID_inside_PitchStructure->err_angular_velocity_pitch-PID_inside_PitchStructure->err_last_angular_velocity_pitch);
   PID_inside_PitchStructure->err_last_angular_velocity_pitch=PID_inside_PitchStructure->err_angular_velocity_pitch;
   return PID_inside_PitchStructure->PWM_OutPut_pitch;
}

//外环翻滚角PID控制器
float PID_Controller_external_Roll(PID_external_Roll *PID_external_RollStructure,float ROLL)
{
   float index=0;
   PID_external_RollStructure->real_roll=ROLL;
   PID_external_RollStructure->err_roll=PID_external_RollStructure->goaL_roll-PID_external_RollStructure->real_roll;
   if(fabs(PID_external_RollStructure->err_roll)<10)
   {
      PID_external_RollStructure->intergral_external_roll+=PID_external_RollStructure->err_roll;
      index=1;
   }
   PID_external_RollStructure->External_OutPut_roll=PID_external_RollStructure->Kp_external_roll*PID_external_RollStructure->err_roll;//+PID_external_RollStructure->Ki_external_roll*PID_external_RollStructure->intergral_external_roll*index;
   return PID_external_RollStructure->External_OutPut_roll;
}

//内环翻滚角PID控制器
int PID_Controller_inside_Roll(PID_inside_Roll *PID_inside_RollStructure,float External_OutPut_Roll,float GX)
{
   PID_inside_RollStructure->External_InPut_roll=External_OutPut_Roll;
   PID_inside_RollStructure->real_angular_velocity_roll=GX;
   PID_inside_RollStructure->err_angular_velocity_roll=PID_inside_RollStructure->External_InPut_roll-PID_inside_RollStructure->real_angular_velocity_roll;
   PID_inside_RollStructure->intergral_inside_roll+=PID_inside_RollStructure->err_angular_velocity_roll;
   PID_inside_RollStructure->PWM_OutPut_roll=PID_inside_RollStructure->Kp_inside_roll*PID_inside_RollStructure->err_angular_velocity_roll;//+PID_inside_RollStructure->Ki_inside_roll*PID_inside_RollStructure->intergral_inside_roll+PID_inside_RollStructure->Kd_inside_roll*(PID_inside_RollStructure->err_angular_velocity_roll-PID_inside_RollStructure->err_last_angular_velocity_roll);
   PID_inside_RollStructure->err_last_angular_velocity_roll=PID_inside_RollStructure->err_angular_velocity_roll;
   return PID_inside_RollStructure->PWM_OutPut_roll; 
}

void PID_Init(void)
{
   int b;
   float Avehigh=0,Avepitch=0,Aveyaw=0,Averoll=0;
   datelist_init();
   for(b=0;b<5;b++)
   {
      Avehigh+=high;
      Avepitch+=pitch;
      Aveyaw+=yaw;
      Averoll+=roll;
   }
   Avehigh/=5.0;
   Avepitch/=5.0;
   Aveyaw/=5.0;
   Averoll/=5.0;
   //高度PID参数的初始化
   PID_HighStucutre.err_high=0;
   PID_HighStucutre.err_last_high=0;
   PID_HighStucutre.goal_high=high;
   PID_HighStucutre.integral_high=0;
   PID_HighStucutre.real_high=Avehigh;
   PID_HighStucutre.Kp_high=5;
   PID_HighStucutre.Ki_high=2;
   PID_HighStucutre.Kd_high=3;  
   
   //偏航角外环PID参数的初始化
   PID_external_YawStructure.err_yaw=0;
   PID_external_YawStructure.goaL_yaw=Aveyaw;
   PID_external_YawStructure.intergral_external_yaw=0;
   PID_external_YawStructure.real_yaw=yaw;
   PID_external_YawStructure.Ki_external_yaw=2;
   PID_external_YawStructure.Kp_external_yaw=5;
   
   //俯仰角外环PID参数的初始化
   PID_external_PitchStructure.err_pitch=0;
   PID_external_PitchStructure.goaL_pitch=Avepitch;
   PID_external_PitchStructure.real_pitch=pitch;
   PID_external_PitchStructure.intergral_external_pitch=0;
   PID_external_PitchStructure.Kp_external_pitch=0;
   PID_external_PitchStructure.Ki_external_pitch=0;
   
   //横滚角外环PID参数的初始化
   PID_external_RollStructure.err_roll=0;
   PID_external_RollStructure.goaL_roll=Averoll;
   PID_external_RollStructure.intergral_external_roll=0;
   PID_external_RollStructure.real_roll=roll;
   PID_external_RollStructure.Ki_external_roll=2;
   PID_external_RollStructure.Kp_external_roll=5;
   
   //俯仰角内环PID参数的初始化
   PID_inside_PitchStructure.err_angular_velocity_pitch=0;
   PID_inside_PitchStructure.err_last_angular_velocity_pitch=0;
   PID_inside_PitchStructure.intergral_inside_pitch=0;
   PID_inside_PitchStructure.real_angular_velocity_pitch=ay;
   PID_inside_PitchStructure.External_InPut_pitch=0;
   PID_inside_PitchStructure.Kp_inside_pitch=0.05;
   PID_inside_PitchStructure.Ki_inside_pitch=5;
   PID_inside_PitchStructure.Kd_inside_pitch=5;
   
   //横滚角内环PID参数的初始化
   PID_inside_RollStructure.err_angular_velocity_roll=0;
   PID_inside_RollStructure.err_last_angular_velocity_roll=0;
   PID_inside_RollStructure.intergral_inside_roll=0;
   PID_inside_RollStructure.External_InPut_roll=0;
   PID_inside_RollStructure.real_angular_velocity_roll=ax;
   PID_inside_RollStructure.Kd_inside_roll=0.02;
   PID_inside_RollStructure.Kp_inside_roll=0.05;
   PID_inside_RollStructure.Ki_inside_roll=0.03;
   
   //偏航角内环PID参数的初始化
   PID_inside_YawStructure.err_angular_velocity_yaw=0;
   PID_inside_YawStructure.err_last_angular_velocity_yaw=0;
   PID_inside_YawStructure.External_InPut_yaw=0;
   PID_inside_YawStructure.intergral_inside_yaw=0;
   PID_inside_YawStructure.real_angular_velocity_yaw=az;
   PID_inside_YawStructure.Kp_inside_yaw=0.05;
   PID_inside_YawStructure.Ki_inside_yaw=0.03;
   PID_inside_YawStructure.Kd_inside_yaw=0.02;
   
   printf("PID相关参数初始化完毕！\r\n");
}






