#include "stm32f10x.h"
#include "main.h"
float pitch,roll,yaw;
short gyrox,gyroy,gyroz;
short aacx,aacy,aacz;
 int main(void)
 {	
    int i=0;
    PIDTypeDef pV,pAngle,pTurn;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//=====ÖÐ¶ÏÓÅÏÈ¼¶·Ö×
    delay_init();
    uart_init(9600);
    LED_Init();
    MiniBalance_PWM_Init(7199,0);
    Encoder_Init_TIM2();
    Encoder_Init_TIM4();
    MPU_Init();	   
	 while(mpu_dmp_init())
       ;
    PID_Init(&pV,80,0.4,0);
    PID_Init(&pAngle,300,0,1);//300£¬0£¬1
    PID_Init(&pTurn,42,0,0);
    TIM3_Cap_Init(0XFFFF,72-1);	    //=====³¬Éù²¨³õÊ¼»
    while(1)
    {
       if(i>50)
       {
          LED0=!LED0;
          LED1=!LED1;
       }
       Cotrol(&pV,&pTurn,&pAngle);
//      AIN1=1;BIN1=0;
//      AIN2=0;BIN2=1;
//      TIM_SetCompare1(TIM1,3500);
//      TIM_SetCompare4(TIM1,3500);
    }
      
 }
