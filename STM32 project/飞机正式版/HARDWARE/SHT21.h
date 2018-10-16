#ifndef __SHT21_H
#define __SHT21_H
#include "sys.h"
#include <math.h> 
typedef unsigned uint;
typedef unsigned long intulong;
typedef unsigned char uchar;
 
/****************************************************************************** 
*ʱ���ߣ�PA.4 
*�����ߣ�PA.3 
*�����¶�14λ��ʪ��12λ 
*******************************************************************************/ 
#define SHTSCK_SET	GPIO_SetBits(GPIOA, GPIO_Pin_4) 
#define SHTSCK_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_4) 

#define SHTDA_SET 	GPIO_SetBits(GPIOA, GPIO_Pin_3) 
#define SHTDA_CLR  GPIO_ResetBits(GPIOA, GPIO_Pin_3) 

//����0����1 
#define SHTDA_IN  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) 

#define SHTWRITE       0x80   //��ַ1000 000   0��ʾд 
#define SHTREAD        0x81   //               1��ʾ�� 
#define RH_Master  0xe5  //����ģʽʪ�Ȳ��� 
#define T_Master   0xe3  //����ģʽ�¶Ȳ��� 
#define SHT_RST    0xfe  //�����λ 
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




