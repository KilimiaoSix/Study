#include "control.h"
#include "main.h"
#include "encoder.h"
int Obstacle_avoidance=0;
int Dir=0;
u8 Flag_sudu=2,Flag_Stop=0; //����ң����صı���
int Turn_Dir=0;
int Encoder_Left=0,Encoder_Right=0;             //���ұ��������������
int Moto1,Moto2;                            //���PWM����
int Balance_Pwm=0,Velocity_Pwm=0,Turn_Pwm=0;
/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ����ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int BalanceSelf(PIDTypeDef *PIDStructure,float Angle,float Gyro)
{
   int balance;
   balance=PIDStructure->Kp*(Angle-MIDDLE_VAL)+Gyro*PIDStructure->Kd;
   return balance;
}
/**************************************************************************
�������ܣ��ٶ�PI���� �޸�ǰ�������ٶȣ�����Target_Velocity�����磬�ĳ�60�ͱȽ�����
��ڲ��������ֱ����������ֱ�����
����  ֵ���ٶȿ���PWM
**************************************************************************/
int PIDvelocity_control(PIDTypeDef *pV,int encoder_left,int encoder_right)
{
   static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral,Target_Velocity;
   if(Obstacle_avoidance)//�ж��Ƿ�Ϊ����ģʽ
      Target_Velocity=LOW_Speed;
   else
      Target_Velocity=HIGH_Speed;
   if(Dir==DirForward)//�ж�Ϊǰ�����Ǻ��˻���ԭ����ƽ��
      Movement=Target_Velocity;
   else if(Dir==DirBack)
      Movement=-Target_Velocity;
   else
      Movement=0;
   //=============�ٶ�PI������=======================//	
   Encoder_Least =(encoder_left+encoder_right)-0;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
   Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
	Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
	Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
   Encoder_Integral=Encoder_Integral-Movement;                       //===����ң�������ݣ�����ǰ������
   if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
   if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===�����޷�
   Velocity=Encoder*pV->Kp+Encoder_Integral*pV->Ki;     
   return Velocity; 
}
/**************************************************************************
�������ܣ�ת�����  �޸�ת���ٶȣ����޸�Turn_Amplitude����
��ڲ��������ֱ����������ֱ�������Z��������
����  ֵ��ת�����PWM
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
   if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת���ٶ��޷�
	if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;     
   if(Dir==1||Dir==-1)  pDir->Kd=0.5;        
		else pDir->Kd=0;   //ת���ʱ��ȡ�������ǵľ��� �е�ģ��PID��˼��
  	//=============ת��PD������=======================//
		Turn=-Turn_Target*pDir->Kp -gyro*pDir->Kd;                 //===���Z�������ǽ���PD����
	  return Turn;
}   
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
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
�������ܣ�����PWM��ֵ  
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM������7200 ������6900
	  if(Dir==DirForward)  Moto1-=DIFFERENCE;  //DIFFERENCE��һ������ƽ��С������ͻ�е��װ�����һ��������ֱ���������������С�����и��õ�һ���ԡ�
	  if(Dir==DirBack)   Moto2+=DIFFERENCE;
     if(Moto1<-Amplitude) Moto1=-Amplitude;	
	  if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
	  if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off(float angle)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop)//��ص�ѹ����11.1V�رյ��
			{	                                                 //===��Ǵ���40�ȹرյ��
         temp=1;                                            //===Flag_Stop��1�رյ��
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
�������ܣ����С���Ƿ�����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count0,count1,count2;
	if(flag==0)                                                                   //��һ��
	 {
	      if(fabs(encoder_left)+fabs(encoder_right)<30)                         //����1��С���ӽ���ֹ
				count0++;
        else 
        count0=0;		
        if(count0>10)				
		    flag=1,count0=0; 
	 } 
	 if(flag==1)                                                                  //����ڶ���
	 {
		    if(++count1>200)       count1=0,flag=0;                                 //��ʱ���ٵȴ�2000ms
	      if(Acceleration>26000&&(Angle>(-20+MIDDLE_VAL))&&(Angle<(20+MIDDLE_VAL)))   //����2��С������0�ȸ���������
		    flag=2; 
	 } 
	 if(flag==2)                                                                  //������
	 {
		  if(++count2>100)       count2=0,flag=0;                                   //��ʱ���ٵȴ�1000ms
	    if(fabs(encoder_left+encoder_right)>135)                                 //����3��С������̥��Ϊ�������ﵽ����ת��   
      {
				flag=0;                                                                                     
				return 1;                                                               //��⵽С��������
			}
	 }
	return 0;
}
/**************************************************************************
�������ܣ����С���Ƿ񱻷���
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int Put_Down(float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count;	 
	 if(Flag_Stop==0)                           //��ֹ���      
   return 0;	                 
	 if(flag==0)                                               
	 {
	      if(Angle>(-10+MIDDLE_VAL)&&Angle<(10+MIDDLE_VAL)&&encoder_left==0&&encoder_right==0)         //����1��С������0�ȸ�����
		    flag=1; 
	 } 
	 if(flag==1)                                               
	 {
		  if(++count>50)                                          //��ʱ���ٵȴ� 500ms
		  {
				count=0;flag=0;
		  }
	    if(encoder_left>3&&encoder_right>3&&encoder_left<60&&encoder_right<60)                //����2��С������̥��δ�ϵ��ʱ����Ϊת��  
      {
				flag=0;
				flag=0;
				return 1;                                             //��⵽С��������
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
      MPU_Get_Accelerometer(ax,&ay,az);	//�õ����ٶȴ���������
      MPU_Get_Gyroscope(gyrox,&gy,gyroz);	//�õ�����������
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
   Moto1=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                            //===�������ֵ������PWM
  	Moto2=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                            //===�������ֵ������PWM
   Xianfu_Pwm();
//   if(Pick_Up(aacz,roll,Encoder_Left,Encoder_Right))//===����Ƿ�С��������
//		Flag_Stop=1;	                                                      //===���������͹رյ��
//	if(Put_Down(roll,Encoder_Left,Encoder_Right))              //===����Ƿ�С��������
//		Flag_Stop=0;	                                                      //===��������¾��������
   if(Turn_Off(roll)==0)                              //===����������쳣
 		Set_Pwm(Moto1,Moto2);                                               //===��ֵ��PWM�Ĵ��� 
}





















