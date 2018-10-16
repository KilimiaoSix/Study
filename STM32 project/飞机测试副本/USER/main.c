#include "stm32f10x.h"
#include "main.h"
#include "timer.h"
Status Autopilot_license=0;
Status Start_permission=0;
Status SystemFlag=1;
PIDTypeDef ExRoll,InRoll,ExPitch,InPitch,ExYaw,InYaw,H;
 int main(void)
 {	
    float pitch=0,roll=0,yaw=0;//欧拉角
    Filterspace *pPitch=Create_New_Space(),*pRoll=Create_New_Space(),*pYaw=Create_New_Space();
	 short aacx=0,aacy=0,aacz=0;//加速度传感器原始数据
	 short gyrox=0,gyroy=0,gyroz=0;//陀螺仪原始数据
    Filterspace *pGyrox=Create_New_Space(),*pGyroy=Create_New_Space(),*pGyroz=Create_New_Space();
    Filterspace *pH=Create_New_Space();
    int x=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组2
    delay_init();//延时函数初始化
    uart_init(9600);//初始化蓝牙串口，定义波特率为9600
    MPU_Init();	   
	 while(mpu_dmp_init())
       ;
    printf("MPU6050 Init over!\r\n");
    PWM_Init(20000-1,72-1);//初始化PWM相关定时器及IO口，PWM频率为50Hz
    Echo_Init(0xffff,72-1);//初始化超声波模块
    usmart_dev.init(SystemCoreClock/1000000);//初始化Usmart
    My_EXTI_Init();//初始化外部中断
    LED_Init();//初始化LED指示灯 
    PID_Init(&ExRoll,&InRoll,&ExPitch,&InPitch,&ExYaw,&InYaw,&H,&pitch,&roll,&yaw,&gyrox,&gyroy,&gyroz,&aacx,&aacy,&aacz,pPitch,pRoll,pYaw,pGyrox,pGyroy,pGyroz,pH);//初始化PID控制器相关参数
    printf("PID Init over!\r\n");
    //完成初始化后等待蓝牙下达起飞命令
    //*************************************************/
    while(1)
       if(Start_permission)//等待蓝牙下达启动许可令
          break;//第一重保险 输入Unlock()后可解锁电调
    //*************************************************//
    PWM_Unlock();//电调解锁   
    //防止因为Reset导致飞机失控，血的教训
    while(1)
    {
       if(SystemFlag)//第三重保险，用于停止飞机，执行命令后飞机将无法启动
       //使用Stop()函数来控制
       {
          if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
          {
            MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
            MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
            AddNewdate(pPitch,pitch);AddNewdate(pRoll,roll);AddNewdate(pYaw,yaw);
          }
          Get_High();//读取输入捕获寄存器，更新高度数值
          AddNewdate(pH,high);
          if(Autopilot_license)//当蓝牙允许起飞后 Autopilot——license标志位置1 第二重保险
          //可以通过蓝牙调用Start() Suspend()来启动和暂停
          {
             Drive_Motor(&ExRoll,&InRoll,&ExPitch,&InPitch,&ExYaw,&InYaw,&H,AveDate(pPitch),AveDate(pRoll),AveDate(pYaw),&gyrox,&gyroy,&gyroz);
          }
          else
          {
             TIM_SetCompare1(TIM3,Manual_frontval);
             TIM_SetCompare2(TIM3,Manual_reatval);
             TIM_SetCompare3(TIM3,Manual_leftval);
             TIM_SetCompare4(TIM3,Manual_rightval);
          }
          if(x>10)
          {
             LED0=!LED0;       //指示灯，表明系统正在正常运行
             LED1=!LED1;
             x=0;
          }
          x++;
       }
    }
 }



 