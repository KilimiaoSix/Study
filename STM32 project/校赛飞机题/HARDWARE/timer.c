#include "timer.h"
void TIM4_Init(u32 arr,u32 psc)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  

   //定时器TIM1初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM1中断 开启更新中断
   
   //中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx	
}
//void TIM4_IRQHandler(void)
//{
//   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//   {
////      if(Stop_Flag)
////         {
////            THROTTLE=THROTTLE_MIN;  //关闭油门
////            subject_flag=0;  //结束手动控制状态
////            Stop_Flag=0; //复位系统
////            return;
////         }
////         
////      if(subject_flag==1)  //如果现在是在做第一题
////      {
////         openMVControl=1;  //拉高驱动脚，表示在找圆
////         if(Take_flag)  //启动飞行器
////         {
////            Flight_control_Unlock();//解锁飞控
////            Take_off(&HStruct);  //起飞
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//延时6秒后开始追圆
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //执行完起飞指令后飞机就不在使用起飞函数
////         //Chase_Circle(&XStruct,&YStruct);  //修正坐标，保证能够降落在A区域
////         High_control(&HStruct,high);  //稳定高度
//////         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //当差值小于五个像素点时，降落
//////         {
//////            Land_flag=1;
//////            delay_ms(1000);delay_ms(1000);//延时两秒后开始降落
//////         }
//////         if(Land_flag)  //当降落标志位置1时开始执行降落函数
//////         {
//////            Land(&HStruct);
//////            Take_flag=1;
//////            Land_flag=0;
//////            subject_flag=0;
//////            openMVControl=0;  //拉低驱动脚，将openMV回归默认模式
//////         }
////      }
////      else if(subject_flag==2)  //如果现在是在做第二题
////      {
////         openMVControl = 0;  //拉低驱动脚，开始寻线模式
////         if(Take_flag)  //启动飞行器
////         {
////            Flight_control_Unlock();//解锁飞控
////            Take_off(&HStruct);  //起飞
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//延时6秒后开始寻线
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //执行完起飞指令后飞机就不在使用起飞函数
////         High_control(&HStruct,high);  //稳定高度
////         if(uFindLin_flag)  //如果处于寻线模式
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //循迹
////         else if(uFindCir_flag)//如果处于追圆模式
////            Chase_Circle(&XStruct,&YStruct);//追圆
////         else if(uLanding)  //异常情况
////            Land_flag=1;    //启动降落函数
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //如果处于追圆模式且坐标差值小于五个像素点，使能降落函数
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//延时两秒后开始降落
////         if(Land_flag)  //当降落标志位置1时开始执行降落函数
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //复位异常状态标志位
////            subject_flag=0;
////            openMVControl=1;  //拉高驱动脚，退出寻圆锁定，进入寻圆模式
////         }
////      }
////      else if(subject_flag==3)  //如果现在是在做第三题
////      {
////         openMVControl = 0;  //拉低驱动脚，开始寻线模式
////         if(Take_flag)  //启动飞行器
////         {
////            Flight_control_Unlock();//解锁飞控
////            Take_off(&HStruct);  //起飞
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//延时6秒后开始寻线
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //执行完起飞指令后飞机就不在使用起飞函数
////         Straight_line_judgment();  //线段校准
////         if(Number==0||Number>2)
////            HStruct.Goal=0.6;
////         else if(Number==2)
////            HStruct.Goal=1.5;
////         High_control(&HStruct,high);  //稳定高度
////         if(uFindLin_flag)  //如果处于寻线模式
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //循迹
////         else if(uFindCir_flag)//如果处于追圆模式
////            Chase_Circle(&XStruct,&YStruct);//追圆
////         else if(uLanding)  //异常情况
////            Land_flag=1;    //启动降落函数
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //如果处于追圆模式且坐标差值小于五个像素点，使能降落函数
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//延时两秒后开始降落
////         if(Land_flag)  //当降落标志位置1时开始执行降落函数
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //复位异常状态标志位
////            subject_flag=0;
////            openMVControl=1;  //拉高驱动脚，退出寻圆锁定，进入寻圆模式
////         }
////      }
////      else if(subject_flag == 4)//手动控制
////      {
////         if(Unlock_Flag)
////         {
////            Flight_control_Unlock();
////            Unlock_Flag=0;
////         }
////         if(Rise_Flag)
////         {
////            if(THROTTLE<THROTTLE_MAX)
////            {
////               THROTTLE+=10;  //慢慢拉高油门
////               Rise_Flag=0;   //复位油门增加标志�
////            }
////         }
////         
////         if(Down_Flag)     
////         {
////            if(THROTTLE>THROTTLE_MIN)
////            {
////               THROTTLE-=10;  //慢慢降低油门
////               Down_Flag=0;   //复位油门增加标志位
////            }
////         }
////         
////         if(Left_Flag)  
////         {
////            if(ROLL>1350)  //倾斜角限幅
////               ROLL-=50;   //倾斜角微增
////            else
////               ROLL=1350;  
////            Left_Flag=0;
////         }
////         else if(ROLL<ROLL_MIDDLE)
////            ROLL++;        //如果没有左转标志位，慢慢复位左转控制寄存器
////         
////         if(Right_Flag)  
////         {
////            if(ROLL<1650)  //倾斜角限幅
////               ROLL+=50;   //倾斜角微增
////            else
////               ROLL=1650;  
////            Right_Flag=0;
////         }
////         else if(ROLL>ROLL_MIDDLE)
////            ROLL--;        //如果没有右转标志位，慢慢复位右转控制寄存器
////         
////         if(Forward_Flag)  
////         {
////            if(PITCH<1650)  //倾斜角限幅
////               PITCH+=50;   //倾斜角微增
////            else
////               PITCH=1650;  
////            Forward_Flag=0;
////         }
////         else if(PITCH>PITCH_MIDDLE)
////            PITCH--;        //如果没有前进标志位慢慢复位前进控制寄存器
////         
////         if(Back_Flag)  
////         {
////            if(PITCH>1350)  //倾斜角限幅
////               PITCH-=50;   //倾斜角微增
////            else
////               PITCH=1350;  
////            Back_Flag=0;
////         }
////         else if(PITCH<PITCH_MIDDLE)
////            PITCH++;        //如果没有后退标志     慢慢复位后退控制寄存器
////         
////         if(LeftHand_Flag)
////         {
////            if(YAW>1350)    //倾斜角限幅
////               YAW-=50;     //倾斜角微增
////            else
////               YAW=1350;
////            LeftHand_Flag=0;
////         }
////         else if(YAW<YAW_MIDDLE)
////            YAW++;        //如果没有左旋标志位，复位左旋控制寄存器
////         
////         if(RightHand_Flag)
////         {
////            if(YAW<1650)    //倾斜角限幅
////               YAW+=50;     //倾斜角微增
////            else
////               YAW=1650;
////            RightHand_Flag=0;
////         }
////         else if(YAW>YAW_MIDDLE)
////            YAW--;        //如果没有右旋标志位，复位右旋控制寄存器
////         
////         if(Reset_Flag)  //如果收到复位倾旋角标志，结束对三轴的PWM波输出
////         {
////            YAW=YAW_MIDDLE;  //复位偏航
////            PITCH=PITCH_MIDDLE;  //复位俯仰
////            ROLL=ROLL_MIDDLE;  //复位横滚
////         }
////      }
////      else if(subject_flag==0)
////      {
////         YAW=YAW_MIDDLE;  //复位偏航
////         PITCH=PITCH_MIDDLE;  //复位俯仰
////         ROLL=ROLL_MIDDLE;  //复位横滚
////         if(THROTTLE>THROTTLE_MIN)
////            THROTTLE-=10;  //逐渐降低油门直至油门最小
////         delay_ms(100);
////      }
////   }
//   TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//}
