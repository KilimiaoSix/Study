#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "pid.h"
#include "math.h"
#include "motor.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#define LOW_Speed 45
#define HIGH_Speed 115

#define MIDDLE_VAL 3

#define DirForward 1
#define DirBack -1
#define DirNo 0

#define TurnDir_Left -1
#define TurnDir_Right 1
#define TurnDir_No 0

#define DIFFERENCE 100
extern int Obstacle_avoidance;
extern u8 Flag_sudu,Flag_Stop; //蓝牙遥控相关的变量
extern int Turn_Dir;
extern int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
extern int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
extern int Moto1,Moto2; 
extern int Dir;
void Set_Pwm(int moto1,int moto2);
void Cotrol(PIDTypeDef *pV,PIDTypeDef *pDir,PIDTypeDef *pAngle);
int BalanceSelf(PIDTypeDef *PIDStructure,float Angle,float Gyro);
int PIDvelocity_control(PIDTypeDef *pV,int encoder_left,int encoder_right);
int PID_Dircontrol(PIDTypeDef *pDir,int encoder_left,int encoder_right,float gyro);
void Xianfu_Pwm(void);
u8 Turn_Off(float angle);
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right);
int Put_Down(float Angle,int encoder_left,int encoder_right);
void Get_Angle(float *roll,float *yaw,short *gyrox,short *gyroz,short *ax,short *az);

#endif


