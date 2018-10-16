#include "stm32f10x.h"
#include "main.h"
#include "timer.h"
Status Autopilot_license=0;
Status Start_permission=0;
Status SystemFlag=1;
 int main(void)
 {	
    int x=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ���2
    delay_init();//��ʱ������ʼ��
    uart_init(115200);//��ʼ���������ڣ����岨����Ϊ9600
    uart2_init(115200);//��ʼ��IMUͨ�Ŵ��ڣ����岨����Ϊ115200
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);//�ȴ�IMU,������ʼ��
    printf("�ɿ�ϵͳ��ʼ��...........111...\r\n");
    PWM_Init(2000-1,720-1);//��ʼ��PWM��ض�ʱ����IO�ڣ�PWMƵ��Ϊ50Hz
//    TIM5_CH1_Cap_Init(0xffff,72-1);//��ʼ�����벶����ض�ʱ��
    Echo_Init(0xffff,72-1);
    usmart_dev.init(SystemCoreClock/1000000);//��ʼ��Usmart
    printf("usmart�����ʼ����ϣ�����\r\n");
    My_EXTI_Init();//��ʼ���ⲿ�ж�
    LED_Init();//��ʼ��LEDָʾ�� 
    PID_Init();//��ʼ��PID��������ز���
    PWM_Unlock();//�������
    printf("����ѽ�����\r\n\r\n\r\n");
    printf("��ʼ�����!\r\n");
    printf("��ʼ�߶�Ϊ��%f\r\n",PID_HighStucutre.goal_high);
    printf("��ʼ��̬ yaw:%0.2f pitch:%0.2f roll:%0.2f\r\n",PID_external_YawStructure.goaL_yaw,PID_external_PitchStructure.goaL_pitch,PID_external_RollStructure.goaL_roll);
    //��ɳ�ʼ����ȴ������´��������
    //*************************************************//
    printf("������ Start() �������������\r\n");
    printf("������ Switch_Auto_or_Manual() ����PID�Զ�����ģʽ\r\n");
    printf("������ help ����usmart���������ѯָ��\r\n");
    printf("������ Print_PID() �۲�����������\r\n");
    while(1)
       if(Start_permission)//�ȴ������´����������
          break;//��һ�ر���
    //*************************************************//
       
    while(1)
    {
       if(SystemFlag)//�����ر��գ��������ʹ��
       {
          UART2_CommandRoute();//���¸����ǣ�ƫ���ǵ���Ϣ.
          Get_High();
          if(Autopilot_license)//��������´��Զ����������
          {
             Anynet_Control();//�����Զ�����ģʽ  //�ڶ��ر���
          }//P.S.����״̬Ϊ�ֶ�״̬����ֹû��׼������PID������ʧ
          else//����ͨ�������ֶ�����ϵͳ
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
             LED0=!LED0;       //ָʾ�ƣ�����ϵͳ������������
             LED1=!LED1;
             x=0;
          }
          x++;
       }
    }
 }
