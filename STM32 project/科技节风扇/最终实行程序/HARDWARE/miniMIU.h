#ifndef __MINIMIU_H
#define __MINIMIU_H
#include "sys.h"
#include "math.h"
#include "TIM.h"
#define b_uart_head  0x80  //收到A5 头 标志位
#define b_rx_over    0x40  //收到完整的帧标志
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //接收缓冲区字节数
extern int16_t ax, ay, az;//加速度计
extern int16_t gx, gy, gz;//陀螺仪
extern int16_t hx, hy, hz;//磁力计
extern int16_t flag;
extern int16_t Night_Mode;
extern float 	yaw,  //偏航角
		pitch,//俯仰
		roll, //滚转
		alt,  //高度
		tempr,//温度
		press;//气压
void UART1_Get_IMU(void);
void UART1_Get_Motion(void);
unsigned char Sum_check(void);
void UART1_CommandRoute(void);
void Sleep_Judge(void);
#endif



