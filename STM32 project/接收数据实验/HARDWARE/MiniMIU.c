#include "MiniMIU.h"
/* 
 
���뻷����MDK-Lite  Version: 4.23
����ʱ��: 2012-05-25
���ԣ�  
���ܣ�
ʹ�ô����жϳ������mini IMU �����ݡ�
��ֲ�������Լ���д��Ӧ�Ĵ��ڳ�ʼ�����򣬲����������жϡ�
���ж��ӳ����� ��Ҫ����Ӧ�ĸĶ�

Ϊ��ʹ�������������Ҫ��
1.��ʼ����Ĵ��ڣ�����������ģ��Ĳ��������ó�һ�µ�
2.�������ڵĽ����жϣ����ο����³����д�ж��ӳ���
  �ο� void USART2_IRQHandler(void) 
3.���������ѭ�����У���ʱ�����ӳ���
  void UART2_CommandRoute(void)
  �Լ���Ƿ��յ��µ�����֡
  ���е���̬���ݺ�ADCֵ������ UART2_CommandRoute
  �н��и��¡�
4.ʹ�� ����ֵ���Զ����£�

float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
int16_t ax, ay, az;//���ٶȼ�
int16_t gx, gy, gz;//������
int16_t hx, hy, hz;//������
------------------------------------
*/
 




//uart reicer flag
#define b_uart_head  0x80  //�յ�A5 ͷ ��־λ
#define b_rx_over    0x40  //�յ�������֡��־
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //���ջ������ֽ���

volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; //�������ݻ�����
volatile unsigned char rx_wr_index; //����дָ��
volatile unsigned char RC_Flag;  //����״̬��־�ֽ�

int16_t ax, ay, az;//���ٶȼ�
int16_t gx, gy, gz;//������
int16_t hx, hy, hz;//������
float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
//�ڽ�����һ֡IMU��̬����󣬵�������ӳ�����ȡ����̬����
void UART2_Get_IMU(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	yaw=(float)temp / 10.0f; //ƫ����
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	pitch=(float)temp / 10.0f;//����
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	roll=(float)temp / 10.0f;//��ת

	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	alt=(float)temp / 10.0f;//�߶�
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	tempr=(float)temp / 10.0f;//�¶�
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	press=(float)temp * 10.0f;//��ѹ

}

//ADCֵ
//�ڽ���һ֡ReportMotion ���������ӳ�����ȡ��ADC����
void UART2_Get_Motion(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ax=temp;//���ٶȼ� X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//���ٶȼ� Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//���ٶȼ� Z���ADCֵ
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//������ X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//������ Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//������ Z���ADCֵ
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//������ X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//������ Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//������ Z���ADCֵ
}


//�����ж��ӳ����ǻ���STM32�ģ������ʹ�õĲ���STM32 ������Ӧ���޸�
//------------------------------------------------------
void USART1_IRQHandler(void) //�����ж��ӳ���
{
  unsigned char data;
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�Ƿ��յ�����?
  {
  data=USART_ReceiveData(USART1); //��ȡ���յ����ֽ�
  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //������յ�A5 ��λ֡ͷ��רλ
    rx_buffer[rx_wr_index++]=data; //��������ֽ�.
  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //�����һ���ֽ���A5 ��ô�϶� �����֡��ʼ�ֽ�
	     { rx_wr_index=0;  //���� ������ָ��
		   RC_Flag&=~b_rx_over; //���֡�Ÿոտ�ʼ��
         }
         else //��һ���ֽڲ���A5
		  rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //��֡ͷ��־
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //�չ����ֽ���.
	     {  
			RC_Flag|=b_rx_over; //��λ ����������һ֡����
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //��ֹ���������
  rx_wr_index--;
  /* Clear the USART2 Recive interrupt */
  USART_ClearITPendingBit(USART1, USART_IT_RXNE); //���жϱ�־.
  }
  
}


//--У�鵱ǰ���յ���һ֡�����Ƿ� ��֡У���ֽ�һ��
unsigned char Sum_check(void)
{ 
  unsigned char i;
  unsigned int checksum=0; 
  for(i=0;i<rx_buffer[0]-2;i++)
   checksum+=rx_buffer[i];
  if((checksum%256)==rx_buffer[rx_buffer[0]-2])
   return(0x01); //Checksum successful
  else
   return(0x00); //Checksum error
}



//--����ӳ�����Ҫ���������� ��ʱ����,�Լ�� �����Ƿ������һ֡����
void UART2_CommandRoute(void)
{
 if(RC_Flag&b_rx_over){  //�Ѿ�������һ֡?
		RC_Flag&=~b_rx_over; //���־��
		if(Sum_check()){ 
		//У��ͨ��
		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU ������
		 UART2_Get_IMU();	//ȡ����
		}
		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion ������
		 UART2_Get_Motion();	 //ȡ����
		} 
		
		}//У���Ƿ�ͨ��?
	}
}


