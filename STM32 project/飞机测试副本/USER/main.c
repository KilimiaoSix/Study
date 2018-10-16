#include "stm32f10x.h"
#include "main.h"
#include "timer.h"
Status Autopilot_license=0;
Status Start_permission=0;
Status SystemFlag=1;
PIDTypeDef ExRoll,InRoll,ExPitch,InPitch,ExYaw,InYaw,H;
 int main(void)
 {	
    float pitch=0,roll=0,yaw=0;//ŷ����
    Filterspace *pPitch=Create_New_Space(),*pRoll=Create_New_Space(),*pYaw=Create_New_Space();
	 short aacx=0,aacy=0,aacz=0;//���ٶȴ�����ԭʼ����
	 short gyrox=0,gyroy=0,gyroz=0;//������ԭʼ����
    Filterspace *pGyrox=Create_New_Space(),*pGyroy=Create_New_Space(),*pGyroz=Create_New_Space();
    Filterspace *pH=Create_New_Space();
    int x=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ���2
    delay_init();//��ʱ������ʼ��
    uart_init(9600);//��ʼ���������ڣ����岨����Ϊ9600
    MPU_Init();	   
	 while(mpu_dmp_init())
       ;
    printf("MPU6050 Init over!\r\n");
    PWM_Init(20000-1,72-1);//��ʼ��PWM��ض�ʱ����IO�ڣ�PWMƵ��Ϊ50Hz
    Echo_Init(0xffff,72-1);//��ʼ��������ģ��
    usmart_dev.init(SystemCoreClock/1000000);//��ʼ��Usmart
    My_EXTI_Init();//��ʼ���ⲿ�ж�
    LED_Init();//��ʼ��LEDָʾ�� 
    PID_Init(&ExRoll,&InRoll,&ExPitch,&InPitch,&ExYaw,&InYaw,&H,&pitch,&roll,&yaw,&gyrox,&gyroy,&gyroz,&aacx,&aacy,&aacz,pPitch,pRoll,pYaw,pGyrox,pGyroy,pGyroz,pH);//��ʼ��PID��������ز���
    printf("PID Init over!\r\n");
    //��ɳ�ʼ����ȴ������´��������
    //*************************************************/
    while(1)
       if(Start_permission)//�ȴ������´����������
          break;//��һ�ر��� ����Unlock()��ɽ������
    //*************************************************//
    PWM_Unlock();//�������   
    //��ֹ��ΪReset���·ɻ�ʧ�أ�Ѫ�Ľ�ѵ
    while(1)
    {
       if(SystemFlag)//�����ر��գ�����ֹͣ�ɻ���ִ�������ɻ����޷�����
       //ʹ��Stop()����������
       {
          if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
          {
            MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
            MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
            AddNewdate(pPitch,pitch);AddNewdate(pRoll,roll);AddNewdate(pYaw,yaw);
          }
          Get_High();//��ȡ���벶��Ĵ��������¸߶���ֵ
          AddNewdate(pH,high);
          if(Autopilot_license)//������������ɺ� Autopilot����license��־λ��1 �ڶ��ر���
          //����ͨ����������Start() Suspend()����������ͣ
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
             LED0=!LED0;       //ָʾ�ƣ�����ϵͳ������������
             LED1=!LED1;
             x=0;
          }
          x++;
       }
    }
 }



 