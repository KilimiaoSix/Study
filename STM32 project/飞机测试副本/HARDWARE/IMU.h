#ifndef __IMU_H
#define __IMU_H
#include "sys.h"

#define Sensitivity 32.8

#define b_uart_head  0x80  //�յ�A5 ͷ ��־λ
#define b_rx_over    0x40  //�յ�������֡��־
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //���ջ������ֽ���
extern volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; //�������ݻ�����
extern volatile unsigned char rx_wr_index; //����дָ��
extern volatile unsigned char RC_Flag;  //����״̬��־�ֽ�

extern float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
extern float ax, ay, az;//���ٶȼ�
extern float gx, gy, gz;//������
extern float hx, hy, hz;//������
void UART2_Get_Motion(void);
unsigned char Sum_check(void);
void UART2_CommandRoute(void);
void uart2_init(u32 bound);
#endif




