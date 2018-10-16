#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

#define SDA_IN() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;}

#define IIC_SCL PBout(8)
#define IIC_SDA PBout(9)
#define READ_SDA PBin(9)
void IIC_Init(void);//初始化
void IIC_Start(void);//开始传输数据信号
void IIC_Stop(void);//停止接受信号
u8 IIC_Wait_Ack(void);//等待应答信号
void IIC_Ack(void);//产生ack信号
void IIC_NAck(void);//不产生ACK信号
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);
#endif
