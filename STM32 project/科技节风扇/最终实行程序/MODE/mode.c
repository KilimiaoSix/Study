#include "mode.h"
#include "miniMIU.h"
int16_t Gear;
void Fan_Mode_Auto(void)
{
   float Body_temperature;
   if(Night_Mode)//�ж��Ƿ�Ϊҹ��ģʽ���ǵĻ��ѵ�λ������1
     Set_PWM(GEAR_1);
   else
   {
      Body_temperature=tep();//��ȡ����¶�
      Change_PWM_Body_Temperature(Body_temperature);//�����¶ȸı䵲λ
   }
   
}
void Humidifier_Mode_Auto(void)
{
   SW_Judge(hui());//����ʪ�ȵ�����ʪ������
}


