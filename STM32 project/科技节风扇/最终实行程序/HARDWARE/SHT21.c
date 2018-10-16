//���������д��SHT21���򣬲��Կ��ã�
#include "SHT21.h"
#include "PWM.h"
uchar flagt; 
extern uchar lowd;
void SHT21_Init(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  /* Configure I2C1 pins: SCL and SDA */ 
  RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOA, ENABLE);    
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //��©����������ڲ��øı�����������¶�ȡIO�ĵ�ƽ 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  SHTSCK_SET;//GPIO_SetBits(GPIOA, GPIO_Pin_4)  
  SHTDA_SET; //GPIO_ResetBits(GPIOA, GPIO_Pin_4)
} 
void sht_delay(unsigned char us) 
{ 
	unsigned char tmp; 
	while(us--) 
	{ 
		for(tmp=0;tmp<100;tmp++) 
		{	 
			__nop(); 
         
		} 
	} 
} 
//******************************StateI2C************************************** 
//**************************��Ƭ�������ź�************************************ 
void StateI2C(void) 
{ 
  sht_delay(80); 
  SHTDA_SET; 
  SHTSCK_SET; 
  sht_delay(30); 
  SHTDA_CLR; 
  SHTSCK_CLR; 
  sht_delay(30); 
} 
//******************************STOPI2C************************************** 
//**************************��Ƭ�������ź�*********************************** 
void STOPI2C(void) 
{ 
  SHTDA_CLR; 
  SHTSCK_SET; 
  sht_delay(30); 
  SHTDA_SET; 
  sht_delay(30); 
} 
//******************************STOPI2C************************************** 
//***************************��Ƭ����Ӧ�ӻ�********************************** 
void Response(uchar a) 
{ 
  if(a==0) SHTDA_CLR;   //������Ӧ�𡱼������� 
  else  SHTDA_SET;      //����Ӧ�𡱱�ʾ���ݴ������   
  SHTSCK_SET; 
  SHTSCK_CLR; 
 } 
//********************��Ƭ����� 1byte ����****************************** 
void SHT_Master_byte2(uchar byte) 
{ 
  uchar i; 
  SHTSCK_CLR;   
  SHTDA_CLR; 
  for(i=0;i<8;i++) 
  { 
    if(byte&0X80) SHTDA_SET; 
    else SHTDA_CLR; 
    SHTSCK_SET; 
    sht_delay(80); 
    SHTSCK_CLR;    
    sht_delay(80); 
    byte*=2;     //����һλ 
  } 
  SHTSCK_SET;  
  sht_delay(10); 
  SHTSCK_CLR; 
  sht_delay(10);   
} 
//********************��Ƭ����� 1byte ����****************************** 
uchar SHT_Master_byte(uchar byte) 
{ 
  uchar i; 
  uchar ack=0; 
  SHTSCK_CLR;   
  SHTDA_CLR; 
  for(i=0;i<8;i++) 
  { 
    if(byte&0x80) SHTDA_SET; 
    else SHTDA_CLR; 
    SHTSCK_SET; 
    sht_delay(80); 
    SHTSCK_CLR;    
    sht_delay(80); 
    byte*=2;     //����һλ 
  } 
  SHTSCK_SET;   
  if(SHTDA_IN) ack=1;     //��Ӧ 
  SHTSCK_CLR;   
  return(ack); 
} 


//********************�ӻ����1byte ����****************************** 
uchar SHT_Receiver_byte(void) 
{ 
  uchar aaa=0,i; 
  for(i=0;i<8;i++) 
  { 
    aaa*=2;  
    SHTSCK_SET;    
    if(SHTDA_IN) aaa+=1; 
    SHTSCK_CLR;     
  } 
  return(aaa); 
} 
//**************************������ģʽ�¶Ȳ���***************************** 
float temper(void) 
{ 
  float wendu,tt; 
  uint  aaa=0; 
  uchar ack; 
  uchar tem1,tem2; 
  StateI2C();                             
   SHT_Master_byte2(0x80);   //��ַ+д 
   SHT_Master_byte2(0xf3);   //����������¶Ȳ��� 
   
     
   do 
   { 
     sht_delay(20);                
     StateI2C(); 
     ack = SHT_Master_byte(0x81);   //�����ȡ���ݡ����ȴ���Ӧ 
   } 
   while(ack==1); 
    sht_delay(20); 
    sht_delay(20); 
   tem1=SHT_Receiver_byte();   //��ȡ���ݸ߰�λ 
   sht_delay(20); 
   //Response(0);               //��Ƭ����Ӧ 
   tem2 = SHT_Receiver_byte();    //��ȡ���ݵͰ�λ 
   STOPI2C(); 
   aaa = (aaa|tem1)*256+tem2; 
   aaa = aaa & 0xfffc; 
   tt=(float)( aaa * 0.02681); 
   wendu =( tt -468.5)/10; 
 /*  if(wendu>0) 
   { 
      lowd=0x01; 
      aaa=(int)(wendu); 
      return(aaa); 
   } 
    else 
    { 
     lowd=0x02; 
     aaa=abs(wendu); 
     return(aaa); 
    }  */ 
return(wendu);	   
} 
//**************************������ģʽʪ�Ȳ���***************************** 
float humier(void) 
{ 
  float sdd,sd; 
  uint  aaa=0; 
  uchar ack; 
  uchar tem1,tem2; 
  StateI2C();                                
   SHT_Master_byte2(0x80);  //��ַ+д 
   SHT_Master_byte2(0xf5);   //���������ʪ�Ȳ��� 
   do 
   { 
    sht_delay(20); 
     StateI2C(); 
     ack = SHT_Master_byte(0x81);    //�����ȡ���ݡ����ȴ���Ӧ 
   } 
   while(ack==1); 
   tem1=SHT_Receiver_byte();  //��ȡ���ݸ߰�λ 
 //  Response(0);        //��Ƭ����Ӧ 
   tem2 = SHT_Receiver_byte();  //��ȡ���ݵͰ�λ 
   STOPI2C(); 
   aaa = (aaa|tem1)*256+tem2; 
   aaa = aaa & 0xfffc; 
   sd=(float)(aaa * 0.00190735); 
   sdd=(sd-6); 
   //aaa =(int)((aaa * 0.00190735 -6)*10);   
   //if(aaa>998)aaa=999;///��ֹʪ�ȳ���100% 
   return(sdd); 
} 
//****************************���û��Ĵ���*********************************** 
unsigned char read_Register(void)     
{ 
  uchar aaa=0 ,ack=0; 
  StateI2C();                  
  ack = SHT_Master_byte(0x80); 
  ack = SHT_Master_byte(0xE7);  //������Ĵ�  
  StateI2C();  
  ack = SHT_Master_byte(0x81); 
  if(ack) 
	  return(ack);   //���� 1 ������ʧ���� 
  aaa = SHT_Receiver_byte(); 
  STOPI2C(); 
  return(aaa);  
} 

//****************************д�û��Ĵ���*********************************** 
uchar write_Register(uchar aaa)   //�������д��Ĭ��λ���ܸ�   ���ȶ�����Ĭ��λ 
{ 
  uchar ack=0; 
  StateI2C();             //д�Ĵ��� 
  ack = SHT_Master_byte(0x80); 
  ack = SHT_Master_byte(0xE6); 
  ack = SHT_Master_byte(aaa);    //�������д��Ĭ��λ���ܸ� 
  STOPI2C();   
  return(ack);   //���� 1 д����ʧ�� 
} 
/******************************************************************************  
��������:SH11�����¶Ⱥ��� 
�޸�����:  
��ڲ���:�� 
����ֵ: ��  
******************************************************************************/ 
float tep(void) 
{   
       float TEMP=0;  
       TEMP= temper(); 
        return TEMP; 
} 
/******************************************************************************  
��������:SH11����ʪ�Ⱥ��� 
�޸�����:  
��ڲ���:�� 
����ֵ: ��  
******************************************************************************/ 
float hui(void) 
{ 
        float HUMI=0;  
        HUMI=  humier(); 
        return HUMI; 
/******************************************************************************  
��������:SH11��������¶Ⱥ���
�޸�����:  
��ڲ���:�¶ȣ�ʪ��
����ֵ: ����¶� 
******************************************************************************/ 
}
float Felt_Air_Temperature(float TEMPER,float HUMIER)
{
   float THI,LU;
   LU=TEMPER*HUMIER;
   THI = TEMPER - 0.55* (1 - (exp(( 17.269*LU)/(LU + 237.3 ))/exp (( 17.269*TEMPER))/((TEMPER + 237.3)))) * ( TEMPER - 14);
   return THI;
}
/******************************************************************************  
��������:��װPWM�Զ�����װ��
�޸�����:  
��ڲ���:����¶�
����ֵ: ��
******************************************************************************/ 
void Change_PWM_Body_Temperature(float Body_Temperature)
{
   if(Body_Temperature>20&&Body_Temperature<25)
      Set_PWM(GEAR_2);
   else if(Body_Temperature>=25)
      Set_PWM(GEAR_3);
   else
      Set_PWM(GEAR_1);
}








