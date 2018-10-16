#include "stm32f10x.h"
#include "main.h"
#include "timer.h"
Status Autopilot_license=0;
Status Start_permission=0;
Status SystemFlag=1;
 int main(void)
 {	
    int x=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组2
    delay_init();//延时函数初始化
    uart_init(115200);//初始化蓝牙串口，定义波特率为9600
    uart2_init(115200);//初始化IMU通信串口，定义波特率为115200
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);//等待IMU,蓝牙初始化
    printf("飞控系统初始化...........111...\r\n");
    PWM_Init(2000-1,720-1);//初始化PWM相关定时器及IO口，PWM频率为50Hz
//    TIM5_CH1_Cap_Init(0xffff,72-1);//初始化输入捕获相关定时器
    Echo_Init(0xffff,72-1);
    usmart_dev.init(SystemCoreClock/1000000);//初始化Usmart
    printf("usmart组件初始化完毕！！！\r\n");
    My_EXTI_Init();//初始化外部中断
    LED_Init();//初始化LED指示灯 
    PID_Init();//初始化PID控制器相关参数
    PWM_Unlock();//电调解锁
    printf("电调已解锁！\r\n\r\n\r\n");
    printf("初始化完毕!\r\n");
    printf("初始高度为：%f\r\n",PID_HighStucutre.goal_high);
    printf("初始姿态 yaw:%0.2f pitch:%0.2f roll:%0.2f\r\n",PID_external_YawStructure.goaL_yaw,PID_external_PitchStructure.goaL_pitch,PID_external_RollStructure.goaL_roll);
    //完成初始化后等待蓝牙下达起飞命令
    //*************************************************//
    printf("请输入 Start() 解除飞行器锁定\r\n");
    printf("请输入 Switch_Auto_or_Manual() 进入PID自动控制模式\r\n");
    printf("请输入 help 进入usmart帮助界面查询指令\r\n");
    printf("请输入 Print_PID() 观察参数设置情况\r\n");
    while(1)
       if(Start_permission)//等待蓝牙下达启动许可令
          break;//第一重保险
    //*************************************************//
       
    while(1)
    {
       if(SystemFlag)//第三重保险，紧急情况使用
       {
          UART2_CommandRoute();//更新俯仰角，偏航角等信息.
          Get_High();
          if(Autopilot_license)//如果蓝牙下达自动控制许可令
          {
             Anynet_Control();//进入自动控制模式  //第二重保险
          }//P.S.启动状态为手动状态，防止没有准备导致PID控制器失
          else//否则通过蓝牙手动控制系统
          {
             TIM_SetCompare1(TIM3,Manual_frontval);
             TIM_SetCompare2(TIM3,Manual_reatval);
             TIM_SetCompare3(TIM3,Manual_leftval);
             TIM_SetCompare4(TIM3,Manual_rightval);
          }
          if(x>100)
          {
             printf("yaw:%0.2f\r\n",yaw);
             printf("pitch:%0.2f\r\n",pitch);
             printf("roll:%0.2f\r\n",roll);
             printf("high:%0.2f\r\n",high);
             printf("gx:%d\r\n",gx);
             printf("gy:%d\r\n",gy);
             printf("gz:%d\r\n",gz);
             printf("front_val:%d\r\n",front_val);
             printf("reat_val:%d\r\n",reat_val);
             printf("right_val:%d\r\n",right_val);
             printf("left_val:%d\r\n",left_val);
             LED0=!LED0;       //指示灯，表明系统正在正常运行
             LED1=!LED1;
             x=0;
          }
          x++;
       }
    }
 }
