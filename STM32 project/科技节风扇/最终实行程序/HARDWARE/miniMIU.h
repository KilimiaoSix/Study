#ifndef __MINIMIU_H
#define __MINIMIU_H
#include "sys.h"
#include "math.h"
#include "TIM.h"
#define b_uart_head  0x80  //�յ�A5 ͷ ��־λ
#define b_rx_over    0x40  //�յ�������֡��־
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //���ջ������ֽ���
extern int16_t ax, ay, az;//���ٶȼ�
extern int16_t gx, gy, gz;//������
extern int16_t hx, hy, hz;//������
extern int16_t flag;
extern int16_t Night_Mode;
extern float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
void UART1_Get_IMU(void);
void UART1_Get_Motion(void);
unsigned char Sum_check(void);
void UART1_CommandRoute(void);
void Sleep_Judge(void);
#endif



