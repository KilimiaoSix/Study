#include "control.h"
#include "main.h"
#include "encoder.h"
int Obstacle_avoidance=0;
int Dir=0;
u8 Flag_sudu=2,Flag_Stop=0; //蓝牙遥控相关的变量
int Turn_Dir=0;
int Encoder_Left=0,Encoder_Right=0;             //左右编码器的脉冲计数
int Moto1,Moto2;                            //电机PWM变量
int Balance_Pwm=0,Velocity_Pwm=0,Turn_Pwm=0;
/**************************************************************************
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
**************************************************************************/
int BalanceSelf(PIDTypeDef *PIDStructure,float Angle,float Gyro)
{
   int balance;
   balance=PIDStructure->Kp*(Angle-MIDDLE_VAL)+Gyro*PIDStructure->Kd;
   return balance;
}
/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity，比如，改成60就比较慢了
入口参数：左轮编码器、右轮编码器
返回  值：速度控制PWM
**************************************************************************/
int PIDvelocity_control(PIDTypeDef *pV,int encoder_left,int encoder_right)
{
   static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral,Target_Velocity;
   if(Obstacle_avoidance)//判断是否为高速模式
      Target_Velocity=LOW_Speed;
   else
      Target_Velocity=HIGH_Speed;
   if(Dir==DirForward)//判断为前进还是后退还是原地自平衡
      Movement=Target_Velocity;
   else if(Dir==DirBack)
      Movement=-Target_Velocity;
   else
      Movement=0;
   //=============速度PI控制器=======================//	
   Encoder_Least =(encoder_left+encoder_right)-0;                    //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
   Encoder *= 0.8;		                                                //===一阶低通滤波器       
	Encoder += Encoder_Least*0.2;	                                    //===一阶低通滤波器    
	Encoder_Integral +=Encoder;                                       //===积分出位移 积分时间：10ms
   Encoder_Integral=Encoder_Integral-Movement;                       //===接收遥控器数据，控制前进后退
   if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
   if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===积分限幅
   Velocity=Encoder*pV->Kp+Encoder_Integral*pV->Ki;     
   return Velocity; 
}
/**************************************************************************
函数功能：转向控制  修改转向速度，请修改Turn_Amplitude即可
入口参数：左轮编码器、右轮编码器、Z轴陀螺仪
返回  值：转向控制PWM
**************************************************************************/
int PID_Dircontrol(PIDTypeDef *pDir,int encoder_left,int encoder_right,float gyro)
{
   static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
   float Turn_Amplitude=88/Flag_sudu;
   if(Turn_Dir)
   {
      if(++Turn_Count==1)
         Encoder_temp=(int)(fabs(encoder_left+encoder_right));
      Turn_Convert=50/Encoder_temp;
      if(Turn_Convert<0.6)
         Turn_Convert=0.6;
		if(Turn_Convert>3)
         Turn_Convert=3;
   }
   else
   {
      Turn_Convert=0.9;
		Turn_Count=0;
		Encoder_temp=0;  
   }
   if(Turn_Dir==TurnDir_Left)	           
      Turn_Target-=Turn_Convert;
	else if(Turn_Dir==TurnDir_Right)	     
      Turn_Target+=Turn_Convert; 
	else 
      Turn_Target=0;
   if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===转向速度限幅
	if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;     
   if(Dir==1||Dir==-1)  pDir->Kd=0.5;        
		else pDir->Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
  	//=============转向PD控制器=======================//
		Turn=-Turn_Target*pDir->Kp -gyro*pDir->Kd;                 //===结合Z轴陀螺仪进行PD控制
	  return Turn;
}   
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
    	if(moto1<0)			AIN2=1,			AIN1=0;
			else 	          AIN2=0,			AIN1=1;
         moto1=(int)fabs(moto1);
			TIM_SetCompare1(TIM1,moto1);
		  if(moto2<0)	BIN1=1,			BIN2=0;
			else        BIN1=0,			BIN2=1;
         moto2=(int)fabs(moto2);
			TIM_SetCompare4(TIM1,moto2);
}
/**************************************************************************
函数功能：限制PWM赋值  
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
	  if(Dir==DirForward)  Moto1-=DIFFERENCE;  //DIFFERENCE是一个衡量平衡小车电机和机械安装差异的一个变量。直接作用于输出，让小车具有更好的一致性。
	  if(Dir==DirBack)   Moto2+=DIFFERENCE;
     if(Moto1<-Amplitude) Moto1=-Amplitude;	
	  if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
	  if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
/**************************************************************************
函数功能：异常关闭电机
入口参数：倾角和电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off(float angle)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop)//电池电压低于11.1V关闭电机
			{	                                                 //===倾角大于40度关闭电机
         temp=1;                                            //===Flag_Stop置1关闭电机
			AIN1=0;                                            
			AIN2=0;
			BIN1=0;
			BIN2=0;
      }
			else
      temp=0;
      return temp;			
}
	/**************************************************************************
函数功能：检测小车是否被拿起
入口参数：int
返回  值：unsigned int
**************************************************************************/
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count0,count1,count2;
	if(flag==0)                                                                   //第一步
	 {
	      if(fabs(encoder_left)+fabs(encoder_right)<30)                         //条件1，小车接近静止
				count0++;
        else 
        count0=0;		
        if(count0>10)				
		    flag=1,count0=0; 
	 } 
	 if(flag==1)                                                                  //进入第二步
	 {
		    if(++count1>200)       count1=0,flag=0;                                 //超时不再等待2000ms
	      if(Acceleration>26000&&(Angle>(-20+MIDDLE_VAL))&&(Angle<(20+MIDDLE_VAL)))   //条件2，小车是在0度附近被拿起
		    flag=2; 
	 } 
	 if(flag==2)                                                                  //第三步
	 {
		  if(++count2>100)       count2=0,flag=0;                                   //超时不再等待1000ms
	    if(fabs(encoder_left+encoder_right)>135)                                 //条件3，小车的轮胎因为正反馈达到最大的转速   
      {
				flag=0;                                                                                     
				return 1;                                                               //检测到小车被拿起
			}
	 }
	return 0;
}
/**************************************************************************
函数功能：检测小车是否被放下
入口参数：int
返回  值：unsigned int
**************************************************************************/
int Put_Down(float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count;	 
	 if(Flag_Stop==0)                           //防止误检      
   return 0;	                 
	 if(flag==0)                                               
	 {
	      if(Angle>(-10+MIDDLE_VAL)&&Angle<(10+MIDDLE_VAL)&&encoder_left==0&&encoder_right==0)         //条件1，小车是在0度附近的
		    flag=1; 
	 } 
	 if(flag==1)                                               
	 {
		  if(++count>50)                                          //超时不再等待 500ms
		  {
				count=0;flag=0;
		  }
	    if(encoder_left>3&&encoder_right>3&&encoder_left<60&&encoder_right<60)                //条件2，小车的轮胎在未上电的时候被人为转动  
      {
				flag=0;
				flag=0;
				return 1;                                             //检测到小车被放下
			}
	 }
	return 0;
}
void Get_Angle(float *roll,float *yaw,short *gyrox,short *gyroz,short *ax,short *az)
{
   float pitch;
   short gy,ay;
   while(mpu_dmp_get_data(&pitch,roll,yaw)==0)
   {
      MPU_Get_Accelerometer(ax,&ay,az);	//得到加速度传感器数据
      MPU_Get_Gyroscope(gyrox,&gy,gyroz);	//得到陀螺仪数据
   }
}
void Cotrol(PIDTypeDef *pV,PIDTypeDef *pDir,PIDTypeDef *pAngle)
{
   Get_Angle(&roll,&yaw,&gyrox,&gyroz,&aacx,&aacz);
   Encoder_Left=-Read_Encoder(2);
   Encoder_Right=Read_Encoder(4);
   Balance_Pwm=BalanceSelf(pAngle,roll,gyrox);
   Velocity_Pwm=PIDvelocity_control(pV,Encoder_Left,Encoder_Right);
//   Turn_Pwm=PID_Dircontrol(pDir,Encoder_Left,Encoder_Right,gyroz); 
   Moto1=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                            //===计算左轮电机最终PWM
  	Moto2=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                            //===计算右轮电机最终PWM
   Xianfu_Pwm();
//   if(Pick_Up(aacz,roll,Encoder_Left,Encoder_Right))//===检查是否小车被那起
//		Flag_Stop=1;	                                                      //===如果被拿起就关闭电机
//	if(Put_Down(roll,Encoder_Left,Encoder_Right))              //===检查是否小车被放下
//		Flag_Stop=0;	                                                      //===如果被放下就启动电机
   if(Turn_Off(roll)==0)                              //===如果不存在异常
 		Set_Pwm(Moto1,Moto2);                                               //===赋值给PWM寄存器 
}





















