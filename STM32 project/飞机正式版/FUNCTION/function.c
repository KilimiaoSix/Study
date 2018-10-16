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
//float high_list[5],yaw_list[5],pitch_list[5],roll_list[5];
//int16_t gx_list[5],gy_list[5],gz_list[5];
//偏航角控制中间函数
int PIDcontrol_Yaw(PID_external_Yaw *PID_external_YawStructure,PID_inside_Yaw *PID_inside_YawStructure,float YAW,float GZ)
{
   float external_OutPut;
   int OutPut;
   external_OutPut=PID_Controller_external_Yaw(PID_external_YawStructure,YAW);
   OutPut=PID_Controller_inside_Yaw(PID_inside_YawStructure,external_OutPut,GZ);
   return OutPut;
}

//对偏航角相关数据更新并控制PWM输出
void Update_Yaw_control(PID_external_Yaw *PID_external_YawStructure,PID_inside_Yaw *PID_inside_YawStructure)
{
   int PWM_Output;
//   int b;
//   float aveyaw=0;
//   int16_t avegz=0;
//   Push_floatlist(pitch_list,yaw);
//   Push_intlist(gz_list,gz);
//   for(b=0;b<5;b++)
//   {
//      aveyaw+=pitch_list[b];
//      avegz+=gy_list[b];
//   }
   PWM_Output=PIDcontrol_Yaw(PID_external_YawStructure,PID_inside_YawStructure,yaw,gz);
//   Front_motor_control(PWM_Output);
//   Reat_motor_control(PWM_Output);
//   left_motor_control(-PWM_Output);
//   right_motor_control(-PWM_Output);
   front_val+=PWM_Output;
   reat_val+=PWM_Output;
   left_val-=PWM_Output;
   right_val-=PWM_Output;
   

}

//俯仰角控制中间函数
int PIDcontrol_Patch(PID_external_Pitch *PID_external_PitchStructure,PID_inside_Pitch *PID_inside_PitchStructure,float PITCH,float GY)
{
   float external_OutPut;
   int OutPut;
   external_OutPut=PID_Controller_external_Pitch(PID_external_PitchStructure,PITCH);
   OutPut=PID_Controller_inside_Pitch(PID_inside_PitchStructure,external_OutPut,GY);
   return OutPut;
}

//对俯仰角相关数据更新并控制PWM输出
void Update_Pitch_control(PID_external_Pitch *PID_external_PitchStructure,PID_inside_Pitch *PID_inside_PitchStructure)
{
   int PWM_Output;
//   int b;
//   float avepitch=0;
//   int16_t avegy=0;
//   Push_floatlist(pitch_list,pitch);
//   Push_intlist(gy_list,gy);
//   for(b=0;b<5;b++)
//   {
//      avepitch+=pitch_list[b];
//      avegy+=gy_list[b];
//   }
   PWM_Output=PIDcontrol_Patch(PID_external_PitchStructure,PID_inside_PitchStructure,pitch-pitch_init,gy-gy_init);
//   Front_motor_control(PWM_Output);
//   Reat_motor_control(-PWM_Output);
//   left_motor_control(PWM_Output);
//   right_motor_control(-PWM_Output);
   front_val-=PWM_Output;
   reat_val+=PWM_Output;
   left_val-=PWM_Output;
   right_val+=PWM_Output;

}

//横滚角控制中间函数
int PIDcontrol_Roll(PID_external_Roll *PID_external_RollStructure,PID_inside_Roll *PID_inside_RollStructure,float ROLL,float GX)
{
   float external_OutPut;
   int OutPut;
   external_OutPut=PID_Controller_external_Roll(PID_external_RollStructure,ROLL);
   OutPut=PID_Controller_inside_Roll(PID_inside_RollStructure,external_OutPut,GX);
   return OutPut;
}

//对横滚角相关数据更新并控制PWM输出
void Update_Roll_control(PID_external_Roll *PID_external_RollStructure,PID_inside_Roll *PID_inside_RollStructure)
{
   int PWM_Output;
//   int b;
//   float averoll=0;
//   int16_t avegx=0;
//   Push_floatlist(roll_list,roll);
//   Push_intlist(gx_list,gx);
//   for(b=0;b<5;b++)
//   {
//      averoll+=pitch_list[b];
//      avegx+=gx_list[b];
//   }
   PWM_Output=PIDcontrol_Roll(PID_external_RollStructure,PID_inside_RollStructure,roll,gx);
//   Front_motor_control(PWM_Output);
//   Reat_motor_control(-PWM_Output);
//   left_motor_control(-PWM_Output);
//   right_motor_control(PWM_Output);
   front_val+=PWM_Output;
   reat_val-=PWM_Output;
   left_val-=PWM_Output;
   right_val+=PWM_Output;

}
//对高度参数进行更新并控制电机
void UpdatePIDControl_High(PID_High *PID_HighStructure)
{
   int PWM_Output;
//   int b;
//   float avehigh=0;
//   Push_floatlist(high_list,high);
//   for(b=0;b<5;b++)
//      avehigh+=pitch_list[b];
   PWM_Output=PID_Controller_High(PID_HighStructure,high);
//   Front_motor_control(PWM_Output);
//   Reat_motor_control(PWM_Output);
//   left_motor_control(PWM_Output);
//   right_motor_control(PWM_Output);
   front_val+=PWM_Output;
   reat_val+=PWM_Output;
   left_val+=PWM_Output;
   right_val+=PWM_Output;
}
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
   delay_ms(1000);delay_ms(1000);
}

void Anynet_Control(void)
{
   front_val=0;
   reat_val=0;
   left_val=0;
   right_val=0;
   //Update_Yaw_control(&PID_external_YawStructure,&PID_inside_YawStructure);
   Update_Pitch_control(&PID_external_PitchStructure,&PID_inside_PitchStructure);
   Update_Roll_control(&PID_external_RollStructure,&PID_inside_RollStructure);
   //UpdatePIDControl_High(&PID_HighStucutre);
   Front_motor_control(front_val);
   Reat_motor_control(reat_val);
   left_motor_control(left_val);
   right_motor_control(right_val);
}
void datelist_init(void)
{
//   int q;
   printf("正在初始化MPU6050，请等待......\r\n");
   while(1)
   {
      if(yaw!=0||pitch!=0||roll!=0)
         break;
      else
      {
         UART2_CommandRoute();
         Get_High();
      }
         
   }
   pitch_init=pitch;
   roll_init=roll;
   yaw_init=yaw;
   high_init=high;
   gx_init=gx;
   gy_init=gy;
   gz_init=gz;
//   for(q=0;q<200;q++)
//   {
//      UART2_CommandRoute();
//      Get_High();
//      delay_ms(10);
//   }
//   for(q=0;q<5;q++)
//   {
//      UART2_CommandRoute();
//      delay_ms(100);
//      delay_ms(100);
//      UART2_CommandRoute();
//      delay_ms(100);
//      delay_ms(100);
//      yaw_list[q]=yaw;
//      pitch_list[q]=pitch;
//      roll_list[q]=roll;
//      gx_list[q]=gx;
//      gy_list[q]=gy;
//      gz_list[q]=gz;
//   }
//   for(q=0;q<5;q++)
//   {
//      Get_High();
//      delay_ms(100);
//      delay_ms(100);
//      Get_High();
//      delay_ms(100);
//      delay_ms(100);
//      high_list[q]=high;
//   }
   printf("MPU6050初始化完毕！！！\r\n");
}
void Push_floatlist(float *list,float number)
{
   int b;
   for(b=4;b>0;b--)
      *(list+b)=*(list+b-1);
   *list=number;
}
void Push_intlist(int16_t *list,int number)
{
   int b;
   for(b=4;b>0;b--)
      *(list+b)=*(list+b-1);
   *list=number;
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
//函数5-7 高度PID调参函数
void highPID_KpLittleincrease(void)
{
   PID_HighStucutre.Kp_high+=0.01;
}
void highPID_KpBigincrease(void)
{
   PID_HighStucutre.Kp_high+=1.0;
}
void highPID_KdLittleincrease(void)
{
   PID_HighStucutre.Kd_high+=0.01;
}
void highPID_KdBigincrease(void)
{
   PID_HighStucutre.Kd_high+=1.0;
}
void highPID_KiLittleincrease(void)
{
   PID_HighStucutre.Ki_high+=0.01;
}
void highPID_KiBigincrease(void)
{
   PID_HighStucutre.Ki_high+=1.0;
}
void highPID_KpLittlereduce(void)
{
   PID_HighStucutre.Kp_high-=0.01;
}
void highPID_KpBigreduce(void)
{
   PID_HighStucutre.Kp_high-=1.0;
}
void highPID_KdLittlereduce(void)
{
   PID_HighStucutre.Kd_high-=0.01;
}
void highPID_KdBigreduce(void)
{
   PID_HighStucutre.Kd_high-=1.0;
}
void highPID_KiLittlereduce(void)
{
   PID_HighStucutre.Ki_high-=0.01;
}
void highPID_KiBigreduce(void)
{
   PID_HighStucutre.Ki_high-=1.0;
}
//函数8-9 偏航角外环PID调参函数
void yawexternal_KpLittleincrease(void)
{
   PID_external_YawStructure.Kp_external_yaw+=0.01;
}
void yawexternal_KiLittleincrease(void)
{
   PID_external_YawStructure.Ki_external_yaw+=0.01;
}
void yawexternal_KpLittlereduce(void)
{
   PID_external_YawStructure.Kp_external_yaw-=0.01;
}
void yawexternal_KiLittlereduce(void)
{
   PID_external_YawStructure.Ki_external_yaw-=0.01;
}
void yawexternal_KpBigincrease(void)
{
   PID_external_YawStructure.Kp_external_yaw+=1.0;
}
void yawexternal_KiBigincrease(void)
{
   PID_external_YawStructure.Ki_external_yaw+=1.0;
}
void yawexternal_KpBigreduce(void)
{
   PID_external_YawStructure.Kp_external_yaw-=1.0;
}
void yawexternal_KiBigreduce(void)
{
   PID_external_YawStructure.Ki_external_yaw-=1.0;
}
//函数10-11 俯仰角外环PID调参函数
void pitchexternal_KpLittleincrease(void)
{
   PID_external_PitchStructure.Kp_external_pitch+=0.01;
}
void pitchexternal_KiLittleincrease(void)
{
   PID_external_PitchStructure.Ki_external_pitch+=0.01;
}
void pitchexternal_KpLittlereduce(void)
{
   PID_external_PitchStructure.Kp_external_pitch-=0.01;
}
void pitchexternal_KiLittlereduce(void)
{
   PID_external_PitchStructure.Ki_external_pitch-=0.01;
}
void pitchexternal_KpBigincrease(void)
{
   PID_external_PitchStructure.Kp_external_pitch+=1.0;
}
void pitchexternal_KiBigincrease(void)
{
   PID_external_PitchStructure.Ki_external_pitch+=1.0;
}
void pitchexternal_KpBigreduce(void)
{
   PID_external_PitchStructure.Kp_external_pitch-=1.0;
}
void pitchexternal_KiBigreduce(void)
{
   PID_external_PitchStructure.Ki_external_pitch-=1.0;
}
//函数11-12 横滚角外环PID调参函数
void rollexternal_KpLittleincrease(void)
{
   PID_external_RollStructure.Kp_external_roll+=0.01;
}
void rollexternal_KiLittleincrease(void)
{
   PID_external_RollStructure.Ki_external_roll+=0.01;
}
void rollexternal_KpLittlereduce(void)
{
   PID_external_RollStructure.Kp_external_roll-=0.01;
}
void rollexternal_KiLittlereduce(void)
{
   PID_external_RollStructure.Ki_external_roll-=0.01;
}
void rollexternal_KpBigincrease(void)
{
   PID_external_RollStructure.Kp_external_roll+=1.0;
}
void rollexternal_KiBigincrease(void)
{
   PID_external_RollStructure.Ki_external_roll+=1.0;
}
void rollexternal_KpBigreduce(void)
{
   PID_external_RollStructure.Kp_external_roll-=1.0;
}
void rollexternal_KiBigreduce(void)
{
   PID_external_RollStructure.Ki_external_roll-=1.0;
}
//函数13-15 偏航角内环PID调参函数
void yawinside_KpLittleincrease(void)
{
   PID_inside_YawStructure.Kp_inside_yaw+=0.01;
}
void yawinside_KiLittleincrease(void)
{
   PID_inside_YawStructure.Ki_inside_yaw+=0.01;
}
void yawinside_KdLittleincrease(void)
{
   PID_inside_YawStructure.Kd_inside_yaw+=0.01;
}
void yawinside_KpBigincrease(void)
{
   PID_inside_YawStructure.Kp_inside_yaw+=1.0;
}
void yawinside_KiBigincrease(void)
{
   PID_inside_YawStructure.Ki_inside_yaw+=1.0;
}
void yawinside_KdBigincrease(void)
{
   PID_inside_YawStructure.Kd_inside_yaw+=1.0;
}
void yawinside_KpLittlereduce(void)
{
   PID_inside_YawStructure.Kp_inside_yaw+=0.01;
}
void yawinside_KiLittlereduce(void)
{
   PID_inside_YawStructure.Ki_inside_yaw-=0.01;
}
void yawinside_KdLittlereduce(void)
{
   PID_inside_YawStructure.Kd_inside_yaw-=0.01;
}
void yawinside_KpBigreduce(void)
{
   PID_inside_YawStructure.Kp_inside_yaw-=1.0;
}
void yawinside_KiBigreduce(void)
{
   PID_inside_YawStructure.Ki_inside_yaw-=1.0;
}
void yawinside_KdBigreduce(void)
{
   PID_inside_YawStructure.Kd_inside_yaw-=1.0;
}
//函数15-18 俯仰角内环PID调参函数
void pitchinside_KpLittleincrease(void)
{
   PID_inside_PitchStructure.Kp_inside_pitch+=0.01;
}
void pitchinside_KiLittleincrease(void)
{
   PID_inside_PitchStructure.Ki_inside_pitch+=0.01;
}
void pitchinside_KdLittleincrease(void)
{
   PID_inside_PitchStructure.Kd_inside_pitch+=0.01;
}
void pitchinside_KpBigincrease(void)
{
   PID_inside_PitchStructure.Kp_inside_pitch+=1.0;
}
void pitchinside_KiBigincrease(void)
{
   PID_inside_PitchStructure.Ki_inside_pitch+=1.0;
}
void pitchinside_KdBigincrease(void)
{
   PID_inside_PitchStructure.Kd_inside_pitch+=1.0;
}
void pitchinside_KpLittlereduce(void)
{
   PID_inside_PitchStructure.Kp_inside_pitch+=0.01;
}
void pitchinside_KiLittlereduce(void)
{
   PID_inside_PitchStructure.Ki_inside_pitch-=0.01;
}
void pitchinside_KdLittlereduce(void)
{
   PID_inside_PitchStructure.Kd_inside_pitch-=0.01;
}
void pitchinside_KpBigreduce(void)
{
   PID_inside_PitchStructure.Kp_inside_pitch-=1.0;
}
void pitchinside_KiBigreduce(void)
{
   PID_inside_PitchStructure.Ki_inside_pitch-=1.0;
}
void pitchinside_KdBigreduce(void)
{
   PID_inside_PitchStructure.Kd_inside_pitch-=1.0;
}
//函数19-21 横滚角内环PID调参函数
void rollinside_KpLittleincrease(void)
{
   PID_inside_RollStructure.Kp_inside_roll+=0.01;
}
void rollinside_KiLittleincrease(void)
{
   PID_inside_RollStructure.Ki_inside_roll+=0.01;
}
void rollinside_KdLittleincrease(void)
{
   PID_inside_RollStructure.Kd_inside_roll+=0.01;
}
void rollinside_KpBigincrease(void)
{
   PID_inside_RollStructure.Kp_inside_roll+=1.0;
}
void rollinside_KiBigincrease(void)
{
   PID_inside_RollStructure.Ki_inside_roll+=1.0;
}
void rollinside_KdBigincrease(void)
{
   PID_inside_RollStructure.Kd_inside_roll+=1.0;
}
void rollinside_KpLittlereduce(void)
{
   PID_inside_RollStructure.Kp_inside_roll+=0.01;
}
void rollinside_KiLittlereduce(void)
{
   PID_inside_RollStructure.Ki_inside_roll-=0.01;
}
void rollinside_KdLittlereduce(void)
{
   PID_inside_RollStructure.Kd_inside_roll-=0.01;
}
void rollinside_KpBigreduce(void)
{
   PID_inside_RollStructure.Kp_inside_roll-=1.0;
}
void rollinside_KiBigreduce(void)
{
   PID_inside_RollStructure.Ki_inside_roll-=1.0;
}
void rollinside_KdBigreduce(void)
{
   PID_inside_RollStructure.Kd_inside_roll-=1.0;
}
//函数22-25 目标值改变函数
void goalhighchange(float goalhigh)
{
   PID_HighStucutre.goal_high=goalhigh;
}
void goalyawchange(float goalyaw)
{
   PID_external_YawStructure.goaL_yaw=goalyaw;
}
void goalpitchchange(float goalpitch)
{
   PID_external_PitchStructure.goaL_pitch=goalpitch;
}
void goalrollchange(float goalroll)
{
   PID_external_RollStructure.goaL_roll=goalroll;
}
void Start(void)
{
   Start_permission=OK;
}
void Stop(void)
{
   TIM_SetCompare1(TIM3,CCR_MIN);
   TIM_SetCompare2(TIM3,CCR_MIN);
   TIM_SetCompare3(TIM3,CCR_MIN);
   TIM_SetCompare4(TIM3,CCR_MIN);
   Print_PID();
   printf("系统停止！请重新上电\r\n");
   SystemFlag=0;
}
void Switch_Auto_or_Manual(void)
{
   Autopilot_license=!Autopilot_license;
}
void Print_PID(void)
{
   printf("yaw_external_Kp:%f\r\n",PID_external_YawStructure.Kp_external_yaw);
   printf("yaw_external_Ki:%f\r\n",PID_external_YawStructure.Ki_external_yaw);
   printf("pitch_external_Kp:%f\r\n",PID_external_PitchStructure.Kp_external_pitch);
   printf("pitch_external_Ki:%f\r\n",PID_external_PitchStructure.Ki_external_pitch);
   printf("roll_external_Kp:%f\r\n",PID_external_RollStructure.Kp_external_roll);
   printf("roll_external_Ki:%f\r\n",PID_external_RollStructure.Ki_external_roll);
   printf("yaw_inside_Kp:%f\r\n",PID_inside_YawStructure.Kp_inside_yaw);
   printf("yaw_inside_Ki:%f\r\n",PID_inside_YawStructure.Ki_inside_yaw);
   printf("yaw_inside_Kd:%f\r\n",PID_inside_YawStructure.Kd_inside_yaw);
   printf("pitch_inside_Kp:%f\r\n",PID_inside_PitchStructure.Kp_inside_pitch);
   printf("pitch_inside_Ki:%f\r\n",PID_inside_PitchStructure.Ki_inside_pitch);
   printf("pitch_inside_Kd:%f\r\n",PID_inside_PitchStructure.Kd_inside_pitch);
   printf("roll_inside_Kp:%f\r\n",PID_inside_RollStructure.Kp_inside_roll);
   printf("roll_inside_Ki:%f\r\n",PID_inside_RollStructure.Ki_inside_roll);
   printf("roll_inside_Kd:%f\r\n",PID_inside_RollStructure.Kd_inside_roll);
   printf("high_Kp:%f\r\n",PID_HighStucutre.Kp_high);
   printf("high_Ki:%f\r\n",PID_HighStucutre.Ki_high);
   printf("high_Kd:%f\r\n",PID_HighStucutre.Kd_high);
}


















