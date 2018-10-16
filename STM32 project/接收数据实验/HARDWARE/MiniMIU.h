#ifndef __MINIMIU_H
#define __MINIMIU_H
#include "sys.h"
void UART2_Get_IMU(void);
void UART2_Get_Motion(void);
unsigned char Sum_check(void);
void UART2_CommandRoute(void);
void uart_init2(u32 bound);

extern int16_t ax, ay, az;//加速度计
extern int16_t gx, gy, gz;//陀螺仪
extern int16_t hx, hy, hz;//磁力计

#endif





