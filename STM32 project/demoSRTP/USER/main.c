#include "sys.h"
#include "SHT21.h"
#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "timer.h"
#include "led.h"
   float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	float temp,humi;					//�¶�	ʪ��
   int Night_Mode=1;   //Ĭ�Ϸ�ҹ��ģʽ
    int16_t flag=0;
    void Sleep_Judge(void);
int main()
{
   delay_init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   SHT21_Init();
   MPU_Init();					//��ʼ��MPU6050
   uart_init(9600);
   while(mpu_dmp_init())
 	{
		printf("MPU6050 Init\r\n");
		delay_ms(50);
	}
   printf("MPU6050 OK!\r\n");
   delay_ms(200);
   while(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)  //��ȡ��һ�ε�����
	{ 
		temp=MPU_Get_Temperature();	//�õ��¶�ֵ
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
   }
   temp=tep();humi=hui();  //���µ�һ���¶�ʪ�ȵ�����
   TIM3_Init(10000-1,7200-1);  //������ʱ�������빤��ģʽ
   while(1)
   {
      if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)  //��ȡ��һ�ε�����
      { 
         MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
         MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
      }
      temp=tep();humi=hui();  //���µ�һ���¶�ʪ�ȵ�����
      Sleep_Judge();
   }
   
   
   
   
}
void Sleep_Judge(void)
{
   static int16_t x=0,y=0,z=0;
   if(fabs(x-aacx)>1000||fabs(y-aacy)>1000||fabs(z-aacz)>1000)
   {
      Night_Mode=0;
      flag=0;
   }
   else
      flag++;
   if(flag>100)
   {
      Night_Mode=1;
      flag=0;
   }
   if(aacx==0&&aacy==0&&aacz==0) //���ݶ�ʧ��Ϊ����ģʽ
         Night_Mode=0;
   x=aacx;
   y=aacy;
   z=aacz;
}
void TIM3_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
   {
      LED0=!LED0;
      LED1=!LED1;
      printf("%.2fT;%.2fH;%dM\r\n",temp,humi,Night_Mode);
   }
   TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
}






