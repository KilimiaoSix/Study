#ifndef __PID_H
#define __PID_H

#include "Echo.h"
#include "IMU.h"
#include "sys.h"


/*float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
int16_t ax, ay, az;//���ٶȼ�
int16_t gx, gy, gz;//������
int16_t hx, hy, hz;//������
------------------------------------
*/

//�߶�PID����
typedef struct{
   float goal_high;  //Ŀ��߶�
   float real_high;  //ʵ�ʸ߶�
   float err_high;   //�߶����
   float err_last_high;  //��һ�εĸ߶����
   float Kp_high,Ki_high,Kd_high;  //PID����
   float integral_high;  //�߶�������
   int PWM_OutPut_high;  //�߶���ص�PWM���
}PID_High;

//ƫ�����⻷PID����
typedef struct{
   float goaL_yaw;  //Ŀ��ƫ����
   float real_yaw;  //ʵ��ƫ����
   float err_yaw;   //ƫ�������
   float Kp_external_yaw,Ki_external_yaw;  //�⻷PID����
   float intergral_external_yaw;  //ƫ����������
   float External_OutPut_yaw;  //�⻷���
}PID_external_Yaw;

//ƫ�����ڻ�PID����
typedef struct{
   float External_InPut_yaw;  //�⻷PID����
   float real_angular_velocity_yaw;  //ʵ�ʽ��ٶ�
   float err_angular_velocity_yaw;  //���ٶ����
   float err_last_angular_velocity_yaw;
   float Kp_inside_yaw,Ki_inside_yaw,Kd_inside_yaw;  //�ڻ�PID����
   float intergral_inside_yaw;  //���ٶ�������
   int PWM_OutPut_yaw;  //ƫ������ص�PWM���
}PID_inside_Yaw;

//�������⻷PID����
typedef struct{
   float goaL_pitch;  //Ŀ�긩����
   float real_pitch;  //ʵ�ʸ�����
   float err_pitch;   //���������
   float Kp_external_pitch,Ki_external_pitch;  //�⻷PID����
   float intergral_external_pitch;  //������������
   float External_OutPut_pitch;  //�⻷���
}PID_external_Pitch;

//�������ڻ�PID����
typedef struct{
   float External_InPut_pitch;  //�⻷PID����
   float real_angular_velocity_pitch;  //ʵ�ʽ��ٶ�
   float err_angular_velocity_pitch;  //���ٶ����
   float Kp_inside_pitch,Ki_inside_pitch,Kd_inside_pitch;  //�ڻ�PID����
   float intergral_inside_pitch;  //���ٶ�������
   float err_last_angular_velocity_pitch;
   int PWM_OutPut_pitch;  //��������ص�PWM���
}PID_inside_Pitch;

//�������⻷PID����
typedef struct{
   float goaL_roll;  //Ŀ�귭����
   float real_roll;  //ʵ�ʷ�����
   float err_roll;   //���������
   float Kp_external_roll,Ki_external_roll;  //�⻷PID����
   float intergral_external_roll;  //������������
   float External_OutPut_roll;  //�⻷���
}PID_external_Roll;

//�������ڻ�PID����
typedef struct{
   float External_InPut_roll;  //�⻷PID����
   float real_angular_velocity_roll;  //ʵ�ʽ��ٶ�
   float err_angular_velocity_roll;  //���ٶ����
   float Kp_inside_roll,Ki_inside_roll,Kd_inside_roll;  //�ڻ�PID����
   float intergral_inside_roll;  //���ٶ�������
   float err_last_angular_velocity_roll;
   int PWM_OutPut_roll;  //ƫ������ص�PWM���
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


