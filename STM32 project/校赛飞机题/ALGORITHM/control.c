#include "control.h"

int LongLine_Flag=0,Number=0;

//ѭ��
void Traction_control(PIDTypeDef *X,PIDTypeDef *Y,PIDTypeDef *Z)
{
   int x_out,z_out;
   buff2pos();
   x_out = PID_Controller(X,line_Point_x);     
   z_out = PID_Controller(Z,line_Angle);  //�����������PID���������м���
   ROLL  = ROLL_MIDDLE+x_out;//
   PITCH = PITCH_MIDDLE+50;//
   YAW   = YAW_MIDDLE+z_out;//�������
}
//����
void High_control(PIDTypeDef *H,float high)
{
   int h_out;
   Get_High();
   h_out = PID_Controller(H,high);  //�߶Ȳ�������PID���������м���
   THROTTLE = Standard_VAL+h_out;  //�߶ȵ���
   if(THROTTLE>1900)
      THROTTLE=1700;
   else if(THROTTLE<1200)
      THROTTLE=1200;
}
//׷Բ
void Chase_Circle(PIDTypeDef *X,PIDTypeDef *Y)
{
   int x_out,y_out; 
   buff2pos();
   x_out = PID_Controller(X,cir_Point_x);
   y_out = PID_Controller(Y,cir_Point_y);
   ROLL  = ROLL_MIDDLE+x_out;//
   PITCH = PITCH_MIDDLE+y_out;//
}
//����
void Land(PIDTypeDef *H)
{
   int h_out;
   int val=0;
   Get_High();
   delay_ms(200);
   H->Goal=high;
   while(high>0.3)  //���߶�С��10cmʱ
   {
      if(Stop_Flag)
         break;
      Get_High();
      if(H->Goal>0)
         H->Goal -= 0.1;  //�𽥰Ѹ߶�����
      h_out = PID_Controller(H,high);
      //Chase_Circle(&XStruct,&YStruct);//׷Բ
      THROTTLE = Standard_VAL+h_out;
      delay_ms(10);
   }
   while(val>1100)
   {
      if(Stop_Flag)
         break;
      THROTTLE -= 10;
      delay_ms(100);
   }
   THROTTLE = THROTTLE_MIN;  //�رյ��
} 
//���
void Take_off(PIDTypeDef *H)
{
   int h_out;int i;
   for(i=0;i<50;i++)
   {
      Get_High();
      delay_ms(20);
   }
   H->Goal=high;
   while(high<0.5)  //��ʼ��ɸ߶�0.5M
   {
      Get_High();
      if(H->Goal<0.5)
         H->Goal += 0.01;
      h_out = PID_Controller(H,high);
      THROTTLE = Standard_VAL+h_out;
      if(Stop_Flag)
         return;
      delay_ms(10);
   }
   H->Goal=0.50;
}
//�ɿ�ϵͳ����
void Flight_control_Unlock(void)
{
   YAW      =         YAW_MIN;
   THROTTLE =         THROTTLE_MIN;
   PITCH    =         PITCH_MIN;
   ROLL     =         ROLL_MAX;//������ʽ��������,ƫ��,�����Ƶ����
                              //          ������Ƶ����
   delay_ms(500);
   YAW      =         YAW_MIDDLE;
   THROTTLE =         1300;
   PITCH    =         PITCH_MIDDLE;
   ROLL     =         ROLL_MIDDLE;  //�ָ�����������ֵ
                                   //�������Ƶ�30%����ֹ�������
   delay_ms(1000);delay_ms(1000);//��ʱ2s
}
//�����ж�
void Straight_line_judgment(void)
{
   buff2pos();  //��������
   if(line_Wide>90)  //�����ȴ���90�����ص�
      LongLine_Flag=1;  //��ǲ���һ�γ���
   if(line_Wide<90&&LongLine_Flag==1)  //��������ʧʱ�����λ�ɹ�����һ�γ��ߣ�������+1
   {
      LongLine_Flag=0;
      Number++;
   }
}













