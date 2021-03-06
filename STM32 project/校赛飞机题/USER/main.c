#include "main.h"
int subject_flag=0;
int Take_flag=1;
int Land_flag=0;
int Forward_Flag=0,Back_Flag=0,Left_Flag=0,Right_Flag=0;
int Rise_Flag=0,Down_Flag=0;
int LeftHand_Flag=0,RightHand_Flag=0;
int Reset_Flag=0;
int Stop_Flag=0;
int Unlock_Flag=0;
PIDTypeDef XStruct,YStruct,ZStruct,HStruct;

// int main(void)
// {	
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断优先级分组，配置为分组2
//    delay_init();  //初始化延时函数
//    uart1_init(115200);  //openMV串口初始化 
//    uart2_init(9600);  //蓝牙串口初始化
//    
//    IO_Init();LED_Init();  //初始化部分控制IO和LED
//    
//    Wave_Init(0xffff,72-1);//超声波电平驱动初始化，定时器2输入捕获使能
//    //PID初始化
//    PID_Init(&XStruct,0,0,0,XMiddle);
//    PID_Init(&YStruct,0,0,0,YMiddle);
//    PID_Init(&ZStruct,0,0,0,0);
//    PID_Init(&HStruct,0,0,0,0);//对PID参数结构体进行初始化
//    
//    TIM3_PWM_Init(20000-1,72-1);//启动定时器3的PWM波输出
//    
//    TIM4_Init(20000-1,72-1);  //7200预分配 10000的预先重装载值 脉冲频率经分频后大概为1MHz
//                              //计数一次大概为1us 大概20ms执行一次控制函数
//                              //完全使能定时器4，开始控制
//    while(1)
//    {
//       LED0=!LED0;
//       LED1=!LED1;
//       delay_ms(500);
//    }//led灯交替闪烁，表面程序正常运行
//    
//    
// }
int main()//测试主函数
{
   int i=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断优先级分组，配置为分组2
   delay_init();  //初始化延时函数
   uart1_init(115200);
   uart2_init(9600);
   TIM3_PWM_Init(20000-1,72-1);//启动定时器3的PWM波输出
   TIM1_PWM_Init(20000-1,72-1);  
   Wave_Init(0xffff,72-1);
   IO_Init();LED_Init();
   Data_Init();
   PID_Init(&HStruct,200,0,0,0.5,high);//对PID参数结构体进行初始化  // Kp:200偏大 略小 //Kd:可加，预计300左右  //Ki:给小 1左右，Ki影响较大
   LED0=1;
   LED1=0;
   openMVControl=0;
//   TIM4_Init(20000-1,72-1);  
   while(1)
   {  
      if(Stop_Flag)
         {
            THROTTLE=THROTTLE_MIN;  //关闭油门
            subject_flag=0;  //结束手动控制状态
            Stop_Flag=0; //复位系统
            Take_flag=1; 
            Land_flag=0;
         }
         
      if(subject_flag==1)  //如果现在是在做第一题
      {
         openMVControl=1;  //拉高驱动脚，表示在找圆
         if(Take_flag)  //启动飞行器
         {
            Flight_control_Unlock();//解锁飞控
            Take_off(&HStruct);  //起飞
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //稳定高度
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //执行完起飞指令后飞机就不在使用起飞函数
         //Chase_Circle(&XStruct,&YStruct);  //修正坐标，保证能够降落在A区域
         High_control(&HStruct,high);  //稳定高度
//         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //当差值小于五个像素点时，降落
//         {
//            Land_flag=1;
//            for(i=0;i<100;i++)
//            {
//               High_control(&HStruct,high);  //稳定高度
//               delay_ms(20);
//               if(Stop_Flag)
//                  break;
//            }
//         }
//         if(Land_flag)  //当降落标志位置1时开始执行降落函数
//         {
//            Land(&HStruct);
//            Take_flag=1;
//            Land_flag=0;
//            subject_flag=0;
//            openMVControl=0;  //拉低驱动脚，将openMV回归默认模式
//         }
      }
      else if(subject_flag==2)  //如果现在是在做第二题
      {
         openMVControl = 0;  //拉低驱动脚，开始寻线模式
         if(Take_flag)  //启动飞行器
         {
            Flight_control_Unlock();//解锁飞控
            Take_off(&HStruct);  //起飞
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //稳定高度
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //执行完起飞指令后飞机就不在使用起飞函数
         High_control(&HStruct,high);  //稳定高度
         if(uFindLin_flag)  //如果处于寻线模式
            Traction_control(&XStruct,&YStruct,&ZStruct);  //循迹
         else if(uFindCir_flag)//如果处于追圆模式
            Chase_Circle(&XStruct,&YStruct);//追圆
         else if(uLanding)  //异常情况
            Land_flag=1;    //启动降落函数
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //如果处于追圆模式且坐标差值小于五个像素点，使能降落函数
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //稳定高度
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //当降落标志位置1时开始执行降落函数
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //复位异常状态标志位
            subject_flag=0;
            openMVControl=1;  //拉高驱动脚，退出寻圆锁定，进入寻圆模式
         }
      }
      else if(subject_flag==3)  //如果现在是在做第三题
      {
         openMVControl = 0;  //拉低驱动脚，开始寻线模式
         if(Take_flag)  //启动飞行器
         {
            Flight_control_Unlock();//解锁飞控
            Take_off(&HStruct);  //起飞
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //稳定高度
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //执行完起飞指令后飞机就不在使用起飞函数
         Straight_line_judgment();  //线段校准
         if(Number==0||Number>2)
            HStruct.Goal=0.6;
         else if(Number==2)
            HStruct.Goal=1.5;
         High_control(&HStruct,high);  //稳定高度
         if(uFindLin_flag)  //如果处于寻线模式
            Traction_control(&XStruct,&YStruct,&ZStruct);  //循迹
         else if(uFindCir_flag)//如果处于追圆模式
            Chase_Circle(&XStruct,&YStruct);//追圆
         else if(uLanding)  //异常情况
            Land_flag=1;    //启动降落函数
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //如果处于追圆模式且坐标差值小于五个像素点，使能降落函数
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //稳定高度
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //当降落标志位置1时开始执行降落函数
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //复位异常状态标志位
            subject_flag=0;
            openMVControl=1;  //拉高驱动脚，退出寻圆锁定，进入寻圆模式
            Number=0;   //长线归位
         }
      }
      else if(subject_flag == 4)//手动控制
      {
         if(Unlock_Flag)
         {
            Flight_control_Unlock();
            Unlock_Flag=0;
         }
         if(Rise_Flag)
         {
            if(THROTTLE<THROTTLE_MAX)
            {
               THROTTLE+=10;  //慢慢拉高油门
               Rise_Flag=0;   //复位油门增加标志�
            }
         }
         
         if(Down_Flag)     
         {
            if(THROTTLE>THROTTLE_MIN)
            {
               THROTTLE-=10;  //慢慢降低油门
               Down_Flag=0;   //复位油门增加标志位
            }
         }
         
         if(Left_Flag)  
         {
            if(ROLL>1350)  //倾斜角限幅
               ROLL-=50;   //倾斜角微增
            else
               ROLL=1350;  
            Left_Flag=0;
         }
         else if(ROLL<ROLL_MIDDLE)
            ROLL++;        //如果没有左转标志位，慢慢复位左转控制寄存器
         
         if(Right_Flag)  
         {
            if(ROLL<1650)  //倾斜角限幅
               ROLL+=50;   //倾斜角微增
            else
               ROLL=1650;  
            Right_Flag=0;
         }
         else if(ROLL>ROLL_MIDDLE)
            ROLL--;        //如果没有右转标志位，慢慢复位右转控制寄存器
         
         if(Forward_Flag)  
         {
            if(PITCH<1650)  //倾斜角限幅
               PITCH+=50;   //倾斜角微增
            else
               PITCH=1650;  
            Forward_Flag=0;
         }
         else if(PITCH>PITCH_MIDDLE)
            PITCH--;        //如果没有前进标志位慢慢复位前进控制寄存器
         
         if(Back_Flag)  
         {
            if(PITCH>1350)  //倾斜角限幅
               PITCH-=50;   //倾斜角微增
            else
               PITCH=1350;  
            Back_Flag=0;
         }
         else if(PITCH<PITCH_MIDDLE)
            PITCH++;        //如果没有后退标志     慢慢复位后退控制寄存器
         
         if(LeftHand_Flag)
         {
            if(YAW>1350)    //倾斜角限幅
               YAW-=50;     //倾斜角微增
            else
               YAW=1350;
            LeftHand_Flag=0;
         }
         else if(YAW<YAW_MIDDLE)
            YAW++;        //如果没有左旋标志位，复位左旋控制寄存器
         
         if(RightHand_Flag)
         {
            if(YAW<1650)    //倾斜角限幅
               YAW+=50;     //倾斜角微增
            else
               YAW=1650;
            RightHand_Flag=0;
         }
         else if(YAW>YAW_MIDDLE)
            YAW--;        //如果没有右旋标志位，复位右旋控制寄存器
         
         if(Reset_Flag)  //如果收到复位倾旋角标志，结束对三轴的PWM波输出
         {
            YAW=YAW_MIDDLE;  //复位偏航
            PITCH=PITCH_MIDDLE;  //复位俯仰
            ROLL=ROLL_MIDDLE;  //复位横滚
         }
      }
      if(subject_flag==0)
      {
         YAW=YAW_MIDDLE;  //复位偏航
         PITCH=PITCH_MIDDLE;  //复位俯仰
         ROLL=ROLL_MIDDLE;  //复位横滚
         if(THROTTLE>THROTTLE_MIN)
            THROTTLE-=10;  //逐渐降低油门直至油门最小
         delay_ms(10);
      }
      if(i>=10)
      {
         LED0=!LED0;
         LED1=!LED1;
         i=0;
      }
      i++;
      delay_ms(50);
   }
}
 
 


 