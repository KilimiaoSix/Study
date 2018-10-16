#include "mode.h"
#include "miniMIU.h"
int16_t Gear;
void Fan_Mode_Auto(void)
{
   float Body_temperature;
   if(Night_Mode)//判断是否为夜间模式，是的话把挡位锁定在1
     Set_PWM(GEAR_1);
   else
   {
      Body_temperature=tep();//读取体感温度
      Change_PWM_Body_Temperature(Body_temperature);//根据温度改变挡位
   }
   
}
void Humidifier_Mode_Auto(void)
{
   SW_Judge(hui());//根据湿度调整加湿器开关
}


