#ifndef __SHT21_H
#define __SHT21_H
#include "sys.h"
#include <math.h> 
typedef unsigned uint;
typedef unsigned long intulong;
typedef unsigned char uchar;
 
/****************************************************************************** 
*时钟线：PA.4 
*数据线：PA.3 
*采用温度14位，湿度12位 
*******************************************************************************/ 
#define SHTSCK_SET	GPIO_SetBits(GPIOA, GPIO_Pin_4) 
#define SHTSCK_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_4) 

#define SHTDA_SET 	GPIO_SetBits(GPIOA, GPIO_Pin_3) 
#define SHTDA_CLR  GPIO_ResetBits(GPIOA, GPIO_Pin_3) 

//返回0，和1 
#define SHTDA_IN  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) 

#define SHTWRITE       0x80   //地址1000 000   0表示写 
#define SHTREAD        0x81   //               1表示读 
#define RH_Master  0xe5  //主机模式湿度测量 
#define T_Master   0xe3  //主机模式温度测量 
#define SHT_RST    0xfe  //软件复位 
void SHT21_Init(void);
void sht_delay(unsigned char us);
void StateI2C(void);
void STOPI2C(void);
void Response(uchar a);
void SHT_Master_byte2(uchar byte);
uchar SHT_Master_byte(uchar byte);
uchar SHT_Receiver_byte(void);
float temper(void);
float humier(void);
unsigned char read_Register(void);
uchar write_Register(uchar aaa);
float tep(void);
float hui(void);
float Felt_Air_Temperature(float TEMPER,float HUMIER);
int judge(float THI);
#endif




