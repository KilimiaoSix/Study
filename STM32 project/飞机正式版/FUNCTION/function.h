#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "delay.h"
#include "sys.h"
#include "main.h"
#include "Echo.h"
#include "IMU.h"
#include "LED.h"
#include "timer.h"
#include "pwm.h"
#include "usmart.h"
#include "PID.h"
#include "Echo.h"
extern int Manual_frontval;
extern int Manual_reatval;
extern int Manual_leftval;
extern int Manual_rightval;

extern int front_val;
extern int reat_val;
extern int left_val;
extern int right_val;

//extern float high_list[5];
//extern float pitch_list[5];
//extern float yaw_list[5];
//extern float roll_list[5];
extern float high_init,yaw_init,pitch_init,roll_init;
extern int16_t gx_init,gy_init,gz_init;
void Push_floatlist(float *list,float number);
void Push_intlist(int16_t *list,int number);
void datelist_init(void);
void PWM_Unlock(void);
void UpdatePIDControl_High(PID_High *PID_HighStructure);
int PIDcontrol_Yaw(PID_external_Yaw *PID_external_YawStructure,PID_inside_Yaw *PID_inside_YawStructure,float YAW,float AZ);
int PIDcontrol_Patch(PID_external_Pitch *PID_external_PitchStructure,PID_inside_Pitch *PID_inside_PitchStructure,float PITCH,float AY);
int PIDcontrol_Roll(PID_external_Roll *PID_external_RollStructure,PID_inside_Roll *PID_inside_RollStructure,float ROLL,float AX);
void Update_Roll_control(PID_external_Roll *PID_external_RollStructure,PID_inside_Roll *PID_inside_RollStructure);
void Update_Yaw_control(PID_external_Yaw *PID_external_YawStructure,PID_inside_Yaw *PID_inside_YawStructure);
void Update_Pitch_control(PID_external_Pitch *PID_external_PitchStructure,PID_inside_Pitch *PID_inside_PitchStructure);
void Front_motor_control(int val);
void Reat_motor_control(int val);
void left_motor_control(int val);
void right_motor_control(int val);
void Anynet_Control(void);
//以下是所有可以通过蓝牙人为调用的函数
void Manual_front_changeval(u16 val);
void Manual_reat_changeval(u16 val);
void Manual_right_changeval(u16 val);
void Manual_left_changeval(u16 val);

void highPID_KpLittleincrease(void);
void highPID_KiLittleincrease(void);
void highPID_KdLittleincrease(void);

void highPID_KpBigincrease(void);
void highPID_KiBigincrease(void);
void highPID_KdBigincrease(void);

void highPID_KpLittlereduce(void);
void highPID_KiLittlereduce(void);
void highPID_KdLittlereduce(void);

void highPID_KpBigreduce(void);
void highPID_KiBigreduce(void);
void highPID_KdBigreduce(void);

void yawexternal_KpLittleincrease(void);
void yawexternal_KiLittleincrease(void);
void yawexternal_KpLittlereduce(void);
void yawexternal_KiLittlereduce(void);
void yawexternal_KpBigincrease(void);
void yawexternal_KiBigincrease(void);
void yawexternal_KpBigreduce(void);
void yawexternal_KiBigreduce(void);

void pitchexternal_KpLittleincrease(void);
void pitchexternal_KiLittleincrease(void);
void pitchexternal_KpLittlereduce(void);
void pitchexternal_KiLittlereduce(void);
void pitchexternal_KpBigincrease(void);
void pitchexternal_KiBigincrease(void);
void pitchexternal_KpBigreduce(void);
void pitchexternal_KiBigreduce(void);

void rollexternal_KpLittleincrease(void);
void rollexternal_KiLittleincrease(void);
void rollexternal_KpLittlereduce(void);
void rollexternal_KiLittlereduce(void);
void rollexternal_KpBigincrease(void);
void rollexternal_KiBigincrease(void);
void rollexternal_KpBigreduce(void);
void rollexternal_KiBigreduce(void);

void yawinside_KpLittleincrease(void);
void yawinside_KiLittleincrease(void);
void yawinside_KdLittleincrease(void);
void yawinside_KpBigincrease(void);
void yawinside_KiBigincrease(void);
void yawinside_KdBigincrease(void);
void yawinside_KpLittlereduce(void);
void yawinside_KiLittlereduce(void);
void yawinside_KdLittlereduce(void);
void yawinside_KpBigreduce(void);
void yawinside_KiBigreduce(void);
void yawinside_KdBigreduce(void);

void pitchinside_KpLittleincrease(void);
void pitchinside_KiLittleincrease(void);
void pitchinside_KdLittleincrease(void);
void pitchinside_KpBigincrease(void);
void pitchinside_KiBigincrease(void);
void pitchinside_KdBigincrease(void);
void pitchinside_KpLittlereduce(void);
void pitchinside_KiLittlereduce(void);
void pitchinside_KdLittlereduce(void);
void pitchinside_KpBigreduce(void);
void pitchinside_KiBigreduce(void);
void pitchinside_KdBigreduce(void);

void rollinside_KpLittleincrease(void);
void rollinside_KiLittleincrease(void);
void rollinside_KdLittleincrease(void);
void rollinside_KpBigincrease(void);
void rollinside_KiBigincrease(void);
void rollinside_KdBigincrease(void);
void rollinside_KpLittlereduce(void);
void rollinside_KiLittlereduce(void);
void rollinside_KdLittlereduce(void);
void rollinside_KpBigreduce(void);
void rollinside_KiBigreduce(void);
void rollinside_KdBigreduce(void);

void goalhighchange(float goalhigh);
void goalyawchange(float goalyaw);
void goalpitchchange(float goalpitch);
void goalrollchange(float goalroll);
void Start(void);
void Stop(void);
void Switch_Auto_or_Manual(void);
void Print_PID(void);

#endif















