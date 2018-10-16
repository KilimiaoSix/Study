#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "math.h"
#include "DateUpdate.h"
#include "IO.h"
#include "wave.h"
/*��־λ Ϊ 1 Ϊ��Ч*/
u8 uFindCir_flag = 0; //��Բ��־λ
u8 uFindLin_flag = 0; //���߱�־λ
u8 uLanding = 0;      //�����־λ

/*��������*/
int cir_Point_x = 0;
int cir_Point_y = 0;

int line_Point_x = 0;
int line_Point_y = 0;
int line_Wide = 0;
int line_Angle = 0;

/*
	uFindCir_flag == 1ʱִ�ж�Բ�������
	����ֻ���߲�������
*/
void buff2pos(void)
{
 	u16 t = 0;  
	u16 len = 0;
	u8 pos_X = 0;//������λ��
	u8 pos_Y = 0;
	u8 pos_W = 0;
	u8 pos_A = 0;
	
	int symbol_fux = 1;//���ű�־λ
	int symbol_fuy = 1;
	int symbol_fuw = 1;
	int symbol_fua = 1;
	
	u8 point_x = 0; //С��λ��
	u8 point_y = 0;
	u8 point_w = 0;
	u8 point_a = 0;

	if(uLanding == 1)
		return ;
	
	if(USART_RX_STA&0x8000)
	{	
			
		if(USART_RX_BUF[0] == 'c')
		{uFindCir_flag = 1; uLanding = 0; uFindLin_flag = 0;}
		else if(USART_RX_BUF[0] == 'N' || USART_RX_BUF[0] == 0)
		{uFindCir_flag = 0; uLanding = 1; uFindLin_flag = 0; return ;}
		else if(USART_RX_BUF[0] == 'l')
		{uFindCir_flag = 0; uLanding = 0; uFindLin_flag = 1;}
		
/***************����****************/
		
		if (uFindCir_flag == 1)
		{
			uFindCir_flag = 1; uLanding = 0; uFindLin_flag = 0;
			cir_Point_x = 0;cir_Point_y = 0;
			len = USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			
			/*********************ͨѶЭ�� ���� *************************/
			//��ʽ ��cxxxxXxxxxY ��������+��ѡ��x��y�� �س���\r\n����β����Сд���ɣ�
			for(t=1;t <len; t++)  //�ҳ�xy��λ��
			{	
				if(USART_RX_BUF[t] == 0x78 || USART_RX_BUF[t] == 0x58) //x��
					pos_X = t;
				if(USART_RX_BUF[t] == 0x79 || USART_RX_BUF[t] == 0x59) //y��
					pos_Y = t;
			}
			if(pos_X < pos_Y)
			{			
				for(t=1; t<pos_X; t++) 				//����x��������
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fux = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_x = pos_X - (t + 1)	;	 //���С��λ��
					else				
						cir_Point_x =	(USART_RX_BUF[t] - 48) + cir_Point_x * 10; //�ۼ�����
				}
				
				for(t = pos_X+1; t<pos_Y; t++) 	//����y��������
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fuy = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_y = pos_Y - (t + 1)	;	 //���С��λ��
					else				
						cir_Point_y =	(USART_RX_BUF[t] - 48) + cir_Point_y * 10; //�ۼ�����
				}
			}
			else
			{
				for(t=1; t<pos_Y; t++) 				//����y��������
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fuy = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_y = pos_Y - (t+1)	;	 //���С��λ��
					else				
						cir_Point_y =	(USART_RX_BUF[t]-48) + cir_Point_y * 10; //�ۼ�����
				}
				
				for(t=pos_Y+1; t<pos_X; t++) 	//����x��������
				{
					if((USART_RX_BUF[t]-48)==-3)	//����и���
						symbol_fux = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t]-48)==-2) // �����С����
						point_x = pos_X - (t+1)	;	 //���С��λ��
					else				
						cir_Point_x =	(USART_RX_BUF[t] - 48) + cir_Point_x * 10; //�ۼ�����
				}
			}
			
			cir_Point_x = symbol_fux*cir_Point_x*pow(10,-point_x);
			cir_Point_y = symbol_fuy*cir_Point_y*pow(10,-point_y);		
			/*�����޷�*/
			if (cir_Point_x > 160||cir_Point_x == 0) cir_Point_x = 80;
         if (cir_Point_y > 120||cir_Point_y == 0) cir_Point_y = 60;
		}//��������Ϊ Բ���� ����			
	  
		else if(uFindLin_flag == 1) //����Ĭ���� ������ ���ݽ���
		{
			uFindCir_flag = 0; uLanding = 0; uFindLin_flag = 1;
			line_Point_x = 0;line_Point_y = 0;line_Wide = 0;line_Angle = 0;
			len = USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			
			/*********************ͨѶЭ�� ���� *************************/
			//��ʽ ��lxxxxXxxxxYxxxxWxxxxA ��������+��ѡ��x��y�� �س���\r\n����β����Сд���ɣ�
			for(t=1;t <len; t++)  //�ҳ�xy��λ��
			{	
				if(USART_RX_BUF[t] == 0x78 || USART_RX_BUF[t] == 0x58) //x��
					pos_X = t;
				if(USART_RX_BUF[t] == 0x79 || USART_RX_BUF[t] == 0x59) //y��
					pos_Y = t;
				if(USART_RX_BUF[t] == 0x77 || USART_RX_BUF[t] == 0x57) //w
					pos_W = t;
				if(USART_RX_BUF[t] == 0x61 || USART_RX_BUF[t] == 0x41) //a
					pos_A = t;
			}
			if(pos_X < pos_Y && pos_W < pos_A)
			{			
				for(t=1; t<pos_X; t++) 				//����x��������
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fux = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_x = pos_X - (t + 1)	;	 //���С��λ��
					else				
						line_Point_x =	(USART_RX_BUF[t] - 48) + line_Point_x * 10; //�ۼ�����
				}
				
				for(t = pos_X+1; t<pos_Y; t++) 	//����y��������
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fuy = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_y = pos_Y - (t + 1)	;	 //���С��λ��
					else				
						line_Point_y =	(USART_RX_BUF[t] - 48) + line_Point_y * 10; //�ۼ�����
				}
				
				for(t = pos_Y+1; t<pos_W; t++) 	//����w����
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fuw = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_w = pos_W - (t + 1)	;	 //���С��λ��
					else				
						line_Wide =	(USART_RX_BUF[t] - 48) + line_Wide * 10; //�ۼ�����
				}	

				for(t = pos_W+1; t<pos_A; t++) 	//����a����
				{
					if((USART_RX_BUF[t] - 48) == -3)	//����и���
						symbol_fua = -1 ;           //���ű�־λ
					else if((USART_RX_BUF[t] - 48) == -2) // �����С����
						point_a = pos_A - (t + 1)	;	 //���С��λ��
					else				
						line_Angle =	(USART_RX_BUF[t] - 48) + line_Angle * 10; //�ۼ�����
				}						
			}
			
			line_Point_x = symbol_fux*line_Point_x*pow(10,-point_x);
			line_Point_y = symbol_fuy*line_Point_y*pow(10,-point_y);
			line_Wide    = symbol_fuw*line_Wide   *pow(10,-point_w);
			line_Angle   = symbol_fua*line_Angle  *pow(10,-point_a);
			/*�����޷�*/
         if (line_Point_x > 160||line_Point_x == 0) line_Point_x = 80;
         if (line_Point_y > 120||line_Point_y == 0) line_Point_y = 60;
         if (line_Wide > 160)                       line_Wide = 0;
         if (line_Angle > 180||line_Angle < -180)   line_Angle = 0;
		}//������ ���ݽ��ս�β
		
		/*ת��������ɺ�ȫ�����㴦��*/
		for(t=0;t<len;t++)
		{
			USART_RX_BUF[t]='0';
		}	
		pos_X = 0;//������λ��
		pos_Y = 0;
		pos_W = 0;
		pos_A = 0;
	
		symbol_fux = 1;//���ű�־λ
		symbol_fuy = 1;
		symbol_fuw = 1;
		symbol_fua = 1;
	
		point_x = 0; //С��λ��
		point_y = 0;
		point_w = 0;
		point_a = 0;
		
		USART_RX_STA=0;
	}//���ܵ������жϽ�β
	
}//������β			
void Data_Init(void)
{
//   do
//   {
//      buff2pos();  //���϶�ȡ����openMV����������
//      if(line_Point_x||line_Point_y||line_Wide||line_Angle||cir_Point_x||cir_Point_y)
//      {
//         LED0=1;
//         delay_ms(2000);
//         break;
//      }
//   }while(1);
   do
   {
      Get_High();
      if(high)
      {
         LED1=1;
         delay_ms(2000);
         break;
      }
   }while(1);
}
