#include "control.h"

int LongLine_Flag=0,Number=0;

//循迹
void Traction_control(PIDTypeDef *X,PIDTypeDef *Y,PIDTypeDef *Z)
{
   int x_out,z_out;
   buff2pos();
   x_out = PID_Controller(X,line_Point_x);     
   z_out = PID_Controller(Z,line_Angle);  //三轴参数导入PID控制器进行计算
   ROLL  = ROLL_MIDDLE+x_out;//
   PITCH = PITCH_MIDDLE+50;//
   YAW   = YAW_MIDDLE+z_out;//三轴调整
}
//定高
void High_control(PIDTypeDef *H,float high)
{
   int h_out;
   Get_High();
   h_out = PID_Controller(H,high);  //高度参数导入PID控制器进行计算
   THROTTLE = Standard_VAL+h_out;  //高度调整
   if(THROTTLE>1900)
      THROTTLE=1700;
   else if(THROTTLE<1200)
      THROTTLE=1200;
}
//追圆
void Chase_Circle(PIDTypeDef *X,PIDTypeDef *Y)
{
   int x_out,y_out; 
   buff2pos();
   x_out = PID_Controller(X,cir_Point_x);
   y_out = PID_Controller(Y,cir_Point_y);
   ROLL  = ROLL_MIDDLE+x_out;//
   PITCH = PITCH_MIDDLE+y_out;//
}
//降落
void Land(PIDTypeDef *H)
{
   int h_out;
   int val=0;
   Get_High();
   delay_ms(200);
   H->Goal=high;
   while(high>0.3)  //当高度小于10cm时
   {
      if(Stop_Flag)
         break;
      Get_High();
      if(H->Goal>0)
         H->Goal -= 0.1;  //逐渐把高度拉低
      h_out = PID_Controller(H,high);
      //Chase_Circle(&XStruct,&YStruct);//追圆
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
   THROTTLE = THROTTLE_MIN;  //关闭电机
} 
//起飞
void Take_off(PIDTypeDef *H)
{
   int h_out;int i;
   for(i=0;i<50;i++)
   {
      Get_High();
      delay_ms(20);
   }
   H->Goal=high;
   while(high<0.5)  //初始起飞高度0.5M
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
//飞控系统解锁
void Flight_control_Unlock(void)
{
   YAW      =         YAW_MIN;
   THROTTLE =         THROTTLE_MIN;
   PITCH    =         PITCH_MIN;
   ROLL     =         ROLL_MAX;//解锁方式：将油门,偏航,俯仰推到最低
                              //          将横滚推到最高
   delay_ms(500);
   YAW      =         YAW_MIDDLE;
   THROTTLE =         1300;
   PITCH    =         PITCH_MIDDLE;
   ROLL     =         ROLL_MIDDLE;  //恢复其他量到中值
                                   //将油门推到30%，防止电机怠速
   delay_ms(1000);delay_ms(1000);//延时2s
}
//长线判断
void Straight_line_judgment(void)
{
   buff2pos();  //更新数据
   if(line_Wide>90)  //如果宽度大于90个像素点
      LongLine_Flag=1;  //标记捕获到一次长线
   if(line_Wide<90&&LongLine_Flag==1)  //当长线消失时，标记位成功捕获一次长线，长线数+1
   {
      LongLine_Flag=0;
      Number++;
   }
}













