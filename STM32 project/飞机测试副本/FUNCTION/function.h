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
void datelist_init(float *pitch,float *roll,float *yaw,PIDTypeDef *H,short *gx,short *gy,short *gz,short *ax,short *ay,short *az,Filterspace *pPitch,Filterspace *pRoll,Filterspace *pYaw,Filterspace *pgx,Filterspace *pgy,Filterspace *pgz,Filterspace *pH);
void PWM_Unlock(void);
void Front_motor_control(int val);
void Reat_motor_control(int val);
void left_motor_control(int val);
void right_motor_control(int val);
void Kp_littleincrease(PIDTypeDef *Temp);
void Ki_littleincrease(PIDTypeDef *Temp);
void Kd_littleincrease(PIDTypeDef *Temp);
void Kp_bigincrease(PIDTypeDef *Temp);
void Ki_bigincrease(PIDTypeDef *Temp);
void Kd_bigincrease(PIDTypeDef *Temp);
void Kp_bigreduce(PIDTypeDef *Temp);
void Ki_bigreduce(PIDTypeDef *Temp);
void Kd_bigreduce(PIDTypeDef *Temp);
void Kp_bigincrease(PIDTypeDef *Temp);
void Ki_bigincrease(PIDTypeDef *Temp);
void Kd_bigincrease(PIDTypeDef *Temp);
//以下是所有可以通过蓝牙人为调用的函数
void Manual_front_changeval(u16 val);
void Manual_reat_changeval(u16 val);
void Manual_right_changeval(u16 val);
void Manual_left_changeval(u16 val);
void goalhighchange(float goalhigh);
void goalyawchange(float goalyaw);
void goalpitchchange(float goalpitch);
void goalrollchange(float goalroll);
void Unlock(void);
void Stop(void);
void Suspend(void);
void Start(void);

void PID_Adjust(int num);
#endif















