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
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж����ȼ����飬����Ϊ����2
//    delay_init();  //��ʼ����ʱ����
//    uart1_init(115200);  //openMV���ڳ�ʼ�� 
//    uart2_init(9600);  //�������ڳ�ʼ��
//    
//    IO_Init();LED_Init();  //��ʼ�����ֿ���IO��LED
//    
//    Wave_Init(0xffff,72-1);//��������ƽ������ʼ������ʱ��2���벶��ʹ��
//    //PID��ʼ��
//    PID_Init(&XStruct,0,0,0,XMiddle);
//    PID_Init(&YStruct,0,0,0,YMiddle);
//    PID_Init(&ZStruct,0,0,0,0);
//    PID_Init(&HStruct,0,0,0,0);//��PID�����ṹ����г�ʼ��
//    
//    TIM3_PWM_Init(20000-1,72-1);//������ʱ��3��PWM�����
//    
//    TIM4_Init(20000-1,72-1);  //7200Ԥ���� 10000��Ԥ����װ��ֵ ����Ƶ�ʾ���Ƶ����Ϊ1MHz
//                              //����һ�δ��Ϊ1us ���20msִ��һ�ο��ƺ���
//                              //��ȫʹ�ܶ�ʱ��4����ʼ����
//    while(1)
//    {
//       LED0=!LED0;
//       LED1=!LED1;
//       delay_ms(500);
//    }//led�ƽ�����˸�����������������
//    
//    
// }
int main()//����������
{
   int i=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж����ȼ����飬����Ϊ����2
   delay_init();  //��ʼ����ʱ����
   uart1_init(115200);
   uart2_init(9600);
   TIM3_PWM_Init(20000-1,72-1);//������ʱ��3��PWM�����
   TIM1_PWM_Init(20000-1,72-1);  
   Wave_Init(0xffff,72-1);
   IO_Init();LED_Init();
   Data_Init();
   PID_Init(&HStruct,200,0,0,0.5,high);//��PID�����ṹ����г�ʼ��  // Kp:200ƫ�� ��С //Kd:�ɼӣ�Ԥ��300����  //Ki:��С 1���ң�KiӰ��ϴ�
   LED0=1;
   LED1=0;
   openMVControl=0;
//   TIM4_Init(20000-1,72-1);  
   while(1)
   {  
      if(Stop_Flag)
         {
            THROTTLE=THROTTLE_MIN;  //�ر�����
            subject_flag=0;  //�����ֶ�����״̬
            Stop_Flag=0; //��λϵͳ
            Take_flag=1; 
            Land_flag=0;
         }
         
      if(subject_flag==1)  //���������������һ��
      {
         openMVControl=1;  //���������ţ���ʾ����Բ
         if(Take_flag)  //����������
         {
            Flight_control_Unlock();//�����ɿ�
            Take_off(&HStruct);  //���
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //�ȶ��߶�
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
         //Chase_Circle(&XStruct,&YStruct);  //�������꣬��֤�ܹ�������A����
         High_control(&HStruct,high);  //�ȶ��߶�
//         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //����ֵС��������ص�ʱ������
//         {
//            Land_flag=1;
//            for(i=0;i<100;i++)
//            {
//               High_control(&HStruct,high);  //�ȶ��߶�
//               delay_ms(20);
//               if(Stop_Flag)
//                  break;
//            }
//         }
//         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
//         {
//            Land(&HStruct);
//            Take_flag=1;
//            Land_flag=0;
//            subject_flag=0;
//            openMVControl=0;  //���������ţ���openMV�ع�Ĭ��ģʽ
//         }
      }
      else if(subject_flag==2)  //��������������ڶ���
      {
         openMVControl = 0;  //���������ţ���ʼѰ��ģʽ
         if(Take_flag)  //����������
         {
            Flight_control_Unlock();//�����ɿ�
            Take_off(&HStruct);  //���
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //�ȶ��߶�
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
         High_control(&HStruct,high);  //�ȶ��߶�
         if(uFindLin_flag)  //�������Ѱ��ģʽ
            Traction_control(&XStruct,&YStruct,&ZStruct);  //ѭ��
         else if(uFindCir_flag)//�������׷Բģʽ
            Chase_Circle(&XStruct,&YStruct);//׷Բ
         else if(uLanding)  //�쳣���
            Land_flag=1;    //�������亯��
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //�������׷Բģʽ�������ֵС��������ص㣬ʹ�ܽ��亯��
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //�ȶ��߶�
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //��λ�쳣״̬��־λ
            subject_flag=0;
            openMVControl=1;  //���������ţ��˳�ѰԲ����������ѰԲģʽ
         }
      }
      else if(subject_flag==3)  //�������������������
      {
         openMVControl = 0;  //���������ţ���ʼѰ��ģʽ
         if(Take_flag)  //����������
         {
            Flight_control_Unlock();//�����ɿ�
            Take_off(&HStruct);  //���
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //�ȶ��߶�
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
         Straight_line_judgment();  //�߶�У׼
         if(Number==0||Number>2)
            HStruct.Goal=0.6;
         else if(Number==2)
            HStruct.Goal=1.5;
         High_control(&HStruct,high);  //�ȶ��߶�
         if(uFindLin_flag)  //�������Ѱ��ģʽ
            Traction_control(&XStruct,&YStruct,&ZStruct);  //ѭ��
         else if(uFindCir_flag)//�������׷Բģʽ
            Chase_Circle(&XStruct,&YStruct);//׷Բ
         else if(uLanding)  //�쳣���
            Land_flag=1;    //�������亯��
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //�������׷Բģʽ�������ֵС��������ص㣬ʹ�ܽ��亯��
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //�ȶ��߶�
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //��λ�쳣״̬��־λ
            subject_flag=0;
            openMVControl=1;  //���������ţ��˳�ѰԲ����������ѰԲģʽ
            Number=0;   //���߹�λ
         }
      }
      else if(subject_flag == 4)//�ֶ�����
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
               THROTTLE+=10;  //������������
               Rise_Flag=0;   //��λ�������ӱ�־�
            }
         }
         
         if(Down_Flag)     
         {
            if(THROTTLE>THROTTLE_MIN)
            {
               THROTTLE-=10;  //������������
               Down_Flag=0;   //��λ�������ӱ�־λ
            }
         }
         
         if(Left_Flag)  
         {
            if(ROLL>1350)  //��б���޷�
               ROLL-=50;   //��б��΢��
            else
               ROLL=1350;  
            Left_Flag=0;
         }
         else if(ROLL<ROLL_MIDDLE)
            ROLL++;        //���û����ת��־λ��������λ��ת���ƼĴ���
         
         if(Right_Flag)  
         {
            if(ROLL<1650)  //��б���޷�
               ROLL+=50;   //��б��΢��
            else
               ROLL=1650;  
            Right_Flag=0;
         }
         else if(ROLL>ROLL_MIDDLE)
            ROLL--;        //���û����ת��־λ��������λ��ת���ƼĴ���
         
         if(Forward_Flag)  
         {
            if(PITCH<1650)  //��б���޷�
               PITCH+=50;   //��б��΢��
            else
               PITCH=1650;  
            Forward_Flag=0;
         }
         else if(PITCH>PITCH_MIDDLE)
            PITCH--;        //���û��ǰ����־λ�H������λǰ�����ƼĴ���
         
         if(Back_Flag)  
         {
            if(PITCH>1350)  //��б���޷�
               PITCH-=50;   //��б��΢��
            else
               PITCH=1350;  
            Back_Flag=0;
         }
         else if(PITCH<PITCH_MIDDLE)
            PITCH++;        //���û�к��˱�־     ������λ���˿��ƼĴ���
         
         if(LeftHand_Flag)
         {
            if(YAW>1350)    //��б���޷�
               YAW-=50;     //��б��΢��
            else
               YAW=1350;
            LeftHand_Flag=0;
         }
         else if(YAW<YAW_MIDDLE)
            YAW++;        //���û��������־λ����λ�������ƼĴ���
         
         if(RightHand_Flag)
         {
            if(YAW<1650)    //��б���޷�
               YAW+=50;     //��б��΢��
            else
               YAW=1650;
            RightHand_Flag=0;
         }
         else if(YAW>YAW_MIDDLE)
            YAW--;        //���û��������־λ����λ�������ƼĴ���
         
         if(Reset_Flag)  //����յ���λ�����Ǳ�־�������������PWM�����
         {
            YAW=YAW_MIDDLE;  //��λƫ��
            PITCH=PITCH_MIDDLE;  //��λ����
            ROLL=ROLL_MIDDLE;  //��λ���
         }
      }
      if(subject_flag==0)
      {
         YAW=YAW_MIDDLE;  //��λƫ��
         PITCH=PITCH_MIDDLE;  //��λ����
         ROLL=ROLL_MIDDLE;  //��λ���
         if(THROTTLE>THROTTLE_MIN)
            THROTTLE-=10;  //�𽥽�������ֱ��������С
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
 
 


 