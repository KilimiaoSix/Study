#include "function.h"
int front_val=0;
int reat_val=0;
int left_val=0;
int right_val=0;
int Manual_frontval=100;
int Manual_reatval=100;
int Manual_leftval=100;
int Manual_rightval=100;
float high_init,yaw_init,pitch_init,roll_init;
int16_t gx_init,gy_init,gz_init;
//PID前电机驱动函数
void Front_motor_control(int val)
{
   if((Motor_reference_value+val)<=Motor_MAX&&(Motor_reference_value+val)>=Motor_MIN)
      front_val=Motor_reference_value+val;
   else if((Motor_reference_value+val)>=Motor_MAX)
      front_val=Motor_MAX;
   else if((Motor_reference_value+val)<=CCR_MIN)
      front_val=Motor_MIN;
   TIM_SetCompare1(TIM3,front_val);
}
//PID后电机驱动函数
void Reat_motor_control(int val)
{
   if((Motor_reference_value+val)<=Motor_MAX&&(Motor_reference_value+val)>=Motor_MIN)
      reat_val=Motor_reference_value+val;
   else if((Motor_reference_value+val)>=Motor_MAX)
      reat_val=Motor_MAX;
   else if((Motor_reference_value+val)<=Motor_MIN)
      reat_val=Motor_MIN;
   TIM_SetCompare2(TIM3,reat_val);
      
}
//PID左电机驱动函数
void left_motor_control(int val)
{
   if((Motor_reference_value+val)<=Motor_MAX&&(Motor_reference_value+val)>=Motor_MIN)
      left_val=Motor_reference_value+val;
   else if((Motor_reference_value+val)>=Motor_MAX)
      left_val=Motor_MAX;
   else if((Motor_reference_value+val)<=Motor_MIN)
      left_val=Motor_MIN;
   TIM_SetCompare3(TIM3,left_val);
}
//PID右电机驱动函数
void right_motor_control(int val)
{
   if((Motor_reference_value+val)<=Motor_MAX&&(Motor_reference_value+val)>=Motor_MIN)
      right_val=Motor_reference_value+val;
   else if((Motor_reference_value+val)>=Motor_MAX)
      right_val=Motor_MAX;
   else if((Motor_reference_value+val)<=Motor_MIN)
      right_val=Motor_MIN;
   TIM_SetCompare4(TIM3,right_val);
}


//电调解锁函数
void PWM_Unlock(void)
{
   TIM_SetCompare1(TIM3,CCR_MAX);
   TIM_SetCompare2(TIM3,CCR_MAX);
   TIM_SetCompare3(TIM3,CCR_MAX);
   TIM_SetCompare4(TIM3,CCR_MAX);   
   delay_ms(1000);delay_ms(1000);
   TIM_SetCompare1(TIM3,CCR_MIN);
   TIM_SetCompare2(TIM3,CCR_MIN);
   TIM_SetCompare3(TIM3,CCR_MIN);
   TIM_SetCompare4(TIM3,CCR_MIN);   
   delay_ms(1000);
}

void datelist_init(float *pitch,float *roll,float *yaw,PIDTypeDef *H,short *gx,short *gy,short *gz,short *ax,short *ay,short *az,Filterspace *pPitch,Filterspace *pRoll,Filterspace *pYaw,Filterspace *pgx,Filterspace *pgy,Filterspace *pgz,Filterspace *pH)
{
   float pitchspace[Deep],rollspace[Deep],yawspace[Deep];
   float gxspace[Deep],gyspace[Deep],gzspace[Deep];
   float hspace[Deep];
   int i;
   while(1)
   {
      if(mpu_dmp_get_data(pitch,roll,yaw)==0)  //得到欧拉角的三个角度，依次是俯仰角（pitch）、横滚角（roll）、航向角（yaw）
      { 	
			MPU_Get_Accelerometer(ax,ay,az);	//得到加速度传感器数据
			MPU_Get_Gyroscope(gx,gy,gz);	//得到陀螺仪数据
			delay_ms(10);
      }
      if((*pitch)!=0||(*roll)!=0||(*yaw)!=0||(*gx)!=0||(*gy)!=0||(*gz)!=0)
         break;
   }
   for(i=0;i<Deep;i++)
   {
      while(mpu_dmp_get_data(pitch,roll,yaw)==0)  //得到欧拉角的三个角度，依次是俯仰角（pitch）、横滚角（roll）、航向角（yaw）
      { 	
			MPU_Get_Accelerometer(ax,ay,az);	//得到加速度传感器数据
			MPU_Get_Gyroscope(gx,gy,gz);	//得到陀螺仪数据
         pitchspace[i]=*pitch;rollspace[i]=*roll;yawspace[i]=*yaw;
         gxspace[i]=(float)*gx;gyspace[i]=(float)*gy;gzspace[i]=(float)*gz;
			delay_ms(10);
      }
      Get_High();
      hspace[i]=high;
   }
   
   FilterspaceInit(pPitch,pitchspace);FilterspaceInit(pRoll,rollspace);FilterspaceInit(pYaw,yawspace);
   FilterspaceInit(pgx,gxspace);FilterspaceInit(pgy,gyspace);FilterspaceInit(pgz,gzspace);
   FilterspaceInit(pH,hspace);
}

//以下为手动控制函数，可通过usmart进行调用
//函数1-4：电机调参函数，手动模式下使用
void Manual_front_changeval(u16 val)
{
   if(val<=CCR_MAX&&val>=CCR_MIN)
      Manual_frontval=val;
}
void Manual_reat_changeval(u16 val)
{
   if(val<=CCR_MAX&&val>=CCR_MIN)
      Manual_reatval=val;
}
void Manual_right_changeval(u16 val)
{
   if(val<=CCR_MAX&&val>=CCR_MIN)
      Manual_rightval=val;
}
void Manual_left_changeval(u16 val)
{
   if(val<=CCR_MAX&&val>=CCR_MIN)
      Manual_leftval=val;
}
void Unlock(void)
{
   Start_permission=OK;
}
void Stop(void)
{
   TIM_SetCompare1(TIM3,CCR_MIN);
   TIM_SetCompare2(TIM3,CCR_MIN);
   TIM_SetCompare3(TIM3,CCR_MIN);
   TIM_SetCompare4(TIM3,CCR_MIN);
   SystemFlag=0;
   delay_ms(1000);
   TIM_Cmd(TIM3,DISABLE);
}
void Start(void)
{
   Autopilot_license=OK;
}
void Suspend(void)
{
   Autopilot_license=FALSE;
}
void Kp_littleincrease(PIDTypeDef *Temp)
{
   Temp->Kp+=0.01;
}
void Ki_littleincrease(PIDTypeDef *Temp)
{
   Temp->Ki+=0.01;
}
void Kd_littleincrease(PIDTypeDef *Temp)
{
   Temp->Kd+=0.01;
}
void Kp_bigincrease(PIDTypeDef *Temp)
{
   Temp->Kp+=1.0;
}
void Ki_bigincrease(PIDTypeDef *Temp)
{
   Temp->Ki+=1.0;
}
void Kd_bigincrease(PIDTypeDef *Temp)
{
   Temp->Kd+=1.0;
}
void Kp_littlereduce(PIDTypeDef *Temp)
{
   Temp->Kp-=0.01;
}
void Ki_littlereduce(PIDTypeDef *Temp)
{
   Temp->Ki-=0.01;
}
void Kd_littlereduce(PIDTypeDef *Temp)
{
   Temp->Kd-=0.01;
}
void Kp_bigreduce(PIDTypeDef *Temp)
{
   Temp->Kp-=1.0;
}
void Ki_bigreduce(PIDTypeDef *Temp)
{
   Temp->Ki-=1.0;
}
void Kd_bigreduce(PIDTypeDef *Temp)
{
   Temp->Kd-=1.0;
}
void PID_Adjust(int num)
{
   PIDTypeDef *Temp;
   int i=0;
   i=num%100;
   switch(i)
   {
      case 00:
         Temp=&H;break;
      case 01:
         Temp=&ExRoll;break;
      case 02:
         Temp=&ExPitch;break;
      case 03:
         Temp=&ExYaw;break;
      case 11:
         Temp=&InRoll;break;
      case 12:
         Temp=&InPitch;break;
      case 13:
         Temp=&InPitch;break;
      default:
         return;
    }
   i=(num/100)%1000;
   switch(i)
   {
      case 100:
         Kp_littleincrease(Temp);break;
      case 101:
         Ki_littleincrease(Temp);break;
      case 102:
         Kd_littleincrease(Temp);break;
      case 000:
         Kp_littlereduce(Temp);break;
      case 001:
         Ki_littlereduce(Temp);break;
      case 002:
         Kd_littlereduce(Temp);break;
      case 110:
         Kp_bigincrease(Temp);break;
      case 111:
         Ki_bigincrease(Temp);break;
      case 112:
         Kd_bigincrease(Temp);break;
      case 010:
         Kp_bigreduce(Temp);break;
      case 011:
         Ki_bigreduce(Temp);break;
      case 012:
         Kd_bigreduce(Temp);break;
      default:
         return;
   }
   printf("Kp : %f",Temp->Kp);
   printf("Kd : %f",Temp->Kd);
   printf("Ki : %f",Temp->Ki);
   delay_ms(1000);
   delay_ms(1000);
         
      
}














