#ifndef __IMU_H
#define __IMU_H
#include "sys.h"

#define Sensitivity 32.8

#define b_uart_head  0x80  //收到A5 头 标志位
#define b_rx_over    0x40  //收到完整的帧标志
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //接收缓冲区字节数
extern volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; //接收数据缓冲区
extern volatile unsigned char rx_wr_index; //缓冲写指针
extern volatile unsigned char RC_Flag;  //接收状态标志字节

extern float 	yaw,  //偏航角
		pitch,//俯仰
		roll, //滚转
		alt,  //高度
		tempr,//温度
		press;//气压
extern float ax, ay, az;//加速度计
extern float gx, gy, gz;//陀螺仪
extern float hx, hy, hz;//磁力计
void UART2_Get_Motion(void);
unsigned char Sum_check(void);
void UART2_CommandRoute(void);
void uart2_init(u32 bound);
#endif




