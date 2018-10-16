#include "timer.h"
void TIM4_Init(u32 arr,u32 psc)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  

   //��ʱ��TIM1��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM1�ж� ���������ж�
   
   //�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx	
}
//void TIM4_IRQHandler(void)
//{
//   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//   {
////      if(Stop_Flag)
////         {
////            THROTTLE=THROTTLE_MIN;  //�ر�����
////            subject_flag=0;  //�����ֶ�����״̬
////            Stop_Flag=0; //��λϵͳ
////            return;
////         }
////         
////      if(subject_flag==1)  //���������������һ��
////      {
////         openMVControl=1;  //���������ţ���ʾ����Բ
////         if(Take_flag)  //����������
////         {
////            Flight_control_Unlock();//�����ɿ�
////            Take_off(&HStruct);  //���
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//��ʱ6���ʼ׷Բ
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
////         //Chase_Circle(&XStruct,&YStruct);  //�������꣬��֤�ܹ�������A����
////         High_control(&HStruct,high);  //�ȶ��߶�
//////         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //����ֵС��������ص�ʱ������
//////         {
//////            Land_flag=1;
//////            delay_ms(1000);delay_ms(1000);//��ʱ�����ʼ����
//////         }
//////         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
//////         {
//////            Land(&HStruct);
//////            Take_flag=1;
//////            Land_flag=0;
//////            subject_flag=0;
//////            openMVControl=0;  //���������ţ���openMV�ع�Ĭ��ģʽ
//////         }
////      }
////      else if(subject_flag==2)  //��������������ڶ���
////      {
////         openMVControl = 0;  //���������ţ���ʼѰ��ģʽ
////         if(Take_flag)  //����������
////         {
////            Flight_control_Unlock();//�����ɿ�
////            Take_off(&HStruct);  //���
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//��ʱ6���ʼѰ��
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
////         High_control(&HStruct,high);  //�ȶ��߶�
////         if(uFindLin_flag)  //�������Ѱ��ģʽ
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //ѭ��
////         else if(uFindCir_flag)//�������׷Բģʽ
////            Chase_Circle(&XStruct,&YStruct);//׷Բ
////         else if(uLanding)  //�쳣���
////            Land_flag=1;    //�������亯��
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //�������׷Բģʽ�������ֵС��������ص㣬ʹ�ܽ��亯��
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//��ʱ�����ʼ����
////         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //��λ�쳣״̬��־λ
////            subject_flag=0;
////            openMVControl=1;  //���������ţ��˳�ѰԲ����������ѰԲģʽ
////         }
////      }
////      else if(subject_flag==3)  //�������������������
////      {
////         openMVControl = 0;  //���������ţ���ʼѰ��ģʽ
////         if(Take_flag)  //����������
////         {
////            Flight_control_Unlock();//�����ɿ�
////            Take_off(&HStruct);  //���
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//��ʱ6���ʼѰ��
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //ִ�������ָ���ɻ��Ͳ���ʹ����ɺ���
////         Straight_line_judgment();  //�߶�У׼
////         if(Number==0||Number>2)
////            HStruct.Goal=0.6;
////         else if(Number==2)
////            HStruct.Goal=1.5;
////         High_control(&HStruct,high);  //�ȶ��߶�
////         if(uFindLin_flag)  //�������Ѱ��ģʽ
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //ѭ��
////         else if(uFindCir_flag)//�������׷Բģʽ
////            Chase_Circle(&XStruct,&YStruct);//׷Բ
////         else if(uLanding)  //�쳣���
////            Land_flag=1;    //�������亯��
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //�������׷Բģʽ�������ֵС��������ص㣬ʹ�ܽ��亯��
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//��ʱ�����ʼ����
////         if(Land_flag)  //�������־λ��1ʱ��ʼִ�н��亯��
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //��λ�쳣״̬��־λ
////            subject_flag=0;
////            openMVControl=1;  //���������ţ��˳�ѰԲ����������ѰԲģʽ
////         }
////      }
////      else if(subject_flag == 4)//�ֶ�����
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
////               THROTTLE+=10;  //������������
////               Rise_Flag=0;   //��λ�������ӱ�־�
////            }
////         }
////         
////         if(Down_Flag)     
////         {
////            if(THROTTLE>THROTTLE_MIN)
////            {
////               THROTTLE-=10;  //������������
////               Down_Flag=0;   //��λ�������ӱ�־λ
////            }
////         }
////         
////         if(Left_Flag)  
////         {
////            if(ROLL>1350)  //��б���޷�
////               ROLL-=50;   //��б��΢��
////            else
////               ROLL=1350;  
////            Left_Flag=0;
////         }
////         else if(ROLL<ROLL_MIDDLE)
////            ROLL++;        //���û����ת��־λ��������λ��ת���ƼĴ���
////         
////         if(Right_Flag)  
////         {
////            if(ROLL<1650)  //��б���޷�
////               ROLL+=50;   //��б��΢��
////            else
////               ROLL=1650;  
////            Right_Flag=0;
////         }
////         else if(ROLL>ROLL_MIDDLE)
////            ROLL--;        //���û����ת��־λ��������λ��ת���ƼĴ���
////         
////         if(Forward_Flag)  
////         {
////            if(PITCH<1650)  //��б���޷�
////               PITCH+=50;   //��б��΢��
////            else
////               PITCH=1650;  
////            Forward_Flag=0;
////         }
////         else if(PITCH>PITCH_MIDDLE)
////            PITCH--;        //���û��ǰ����־λ�H������λǰ�����ƼĴ���
////         
////         if(Back_Flag)  
////         {
////            if(PITCH>1350)  //��б���޷�
////               PITCH-=50;   //��б��΢��
////            else
////               PITCH=1350;  
////            Back_Flag=0;
////         }
////         else if(PITCH<PITCH_MIDDLE)
////            PITCH++;        //���û�к��˱�־     ������λ���˿��ƼĴ���
////         
////         if(LeftHand_Flag)
////         {
////            if(YAW>1350)    //��б���޷�
////               YAW-=50;     //��б��΢��
////            else
////               YAW=1350;
////            LeftHand_Flag=0;
////         }
////         else if(YAW<YAW_MIDDLE)
////            YAW++;        //���û��������־λ����λ�������ƼĴ���
////         
////         if(RightHand_Flag)
////         {
////            if(YAW<1650)    //��б���޷�
////               YAW+=50;     //��б��΢��
////            else
////               YAW=1650;
////            RightHand_Flag=0;
////         }
////         else if(YAW>YAW_MIDDLE)
////            YAW--;        //���û��������־λ����λ�������ƼĴ���
////         
////         if(Reset_Flag)  //����յ���λ�����Ǳ�־�������������PWM�����
////         {
////            YAW=YAW_MIDDLE;  //��λƫ��
////            PITCH=PITCH_MIDDLE;  //��λ����
////            ROLL=ROLL_MIDDLE;  //��λ���
////         }
////      }
////      else if(subject_flag==0)
////      {
////         YAW=YAW_MIDDLE;  //��λƫ��
////         PITCH=PITCH_MIDDLE;  //��λ����
////         ROLL=ROLL_MIDDLE;  //��λ���
////         if(THROTTLE>THROTTLE_MIN)
////            THROTTLE-=10;  //�𽥽�������ֱ��������С
////         delay_ms(100);
////      }
////   }
//   TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//}
