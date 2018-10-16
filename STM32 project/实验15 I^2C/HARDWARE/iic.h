#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

#define SDA_IN() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;}

#define IIC_SCL PBout(8)
#define IIC_SDA PBout(9)
#define READ_SDA PBin(9)
void IIC_Init(void);//��ʼ��
void IIC_Start(void);//��ʼ���������ź�
void IIC_Stop(void);//ֹͣ�����ź�
u8 IIC_Wait_Ack(void);//�ȴ�Ӧ���ź�
void IIC_Ack(void);//����ack�ź�
void IIC_NAck(void);//������ACK�ź�
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);
#endif
