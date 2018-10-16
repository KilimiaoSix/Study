#include "sys.h"
#include "SHT21.h"
#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "timer.h"
#include "led.h"
   float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	float temp,humi;					//温度	湿度
   int Night_Mode=1;   //默认非夜间模式
    int16_t flag=0;
    void Sleep_Judge(void);
int main()
{
   delay_init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   SHT21_Init();
   MPU_Init();					//初始化MPU6050
   uart_init(9600);
   while(mpu_dmp_init())
 	{
		printf("MPU6050 Init\r\n");
		delay_ms(50);
	}
   printf("MPU6050 OK!\r\n");
   delay_ms(200);
   while(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)  //获取第一次的数据
	{ 
		temp=MPU_Get_Temperature();	//得到温度值
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
   }
   temp=tep();humi=hui();  //更新第一次温度湿度的数据
   TIM3_Init(10000-1,7200-1);  //开启定时器，进入工作模式
   while(1)
   {
      if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)  //获取第一次的数据
      { 
         MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
         MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
      }
      temp=tep();humi=hui();  //更新第一次温度湿度的数据
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
   if(aacx==0&&aacy==0&&aacz==0) //数据丢失则为常规模式
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






