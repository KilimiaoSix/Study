//下面我最近写的SHT21程序，测试可用！
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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //开漏输出，可以在不用改变成输入的情况下读取IO的电平 
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
//**************************单片机启动信号************************************ 
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
//**************************单片机结束信号*********************************** 
void STOPI2C(void) 
{ 
  SHTDA_CLR; 
  SHTSCK_SET; 
  sht_delay(30); 
  SHTDA_SET; 
  sht_delay(30); 
} 
//******************************STOPI2C************************************** 
//***************************单片机回应从机********************************** 
void Response(uchar a) 
{ 
  if(a==0) SHTDA_CLR;   //主机“应答”继续传输 
  else  SHTDA_SET;      //“非应答”表示数据传输结束   
  SHTSCK_SET; 
  SHTSCK_CLR; 
 } 
//********************单片机输出 1byte 数据****************************** 
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
    byte*=2;     //左移一位 
  } 
  SHTSCK_SET;  
  sht_delay(10); 
  SHTSCK_CLR; 
  sht_delay(10);   
} 
//********************单片机输出 1byte 数据****************************** 
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
    byte*=2;     //左移一位 
  } 
  SHTSCK_SET;   
  if(SHTDA_IN) ack=1;     //回应 
  SHTSCK_CLR;   
  return(ack); 
} 


//********************从机输出1byte 数据****************************** 
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
//**************************非主机模式温度测试***************************** 
float temper(void) 
{ 
  float wendu,tt; 
  uint  aaa=0; 
  uchar ack; 
  uchar tem1,tem2; 
  StateI2C();                             
   SHT_Master_byte2(0x80);   //地址+写 
   SHT_Master_byte2(0xf3);   //命令：非主机温度测试 
   
     
   do 
   { 
     sht_delay(20);                
     StateI2C(); 
     ack = SHT_Master_byte(0x81);   //命令：读取数据。。等待回应 
   } 
   while(ack==1); 
    sht_delay(20); 
    sht_delay(20); 
   tem1=SHT_Receiver_byte();   //读取数据高八位 
   sht_delay(20); 
   //Response(0);               //单片机回应 
   tem2 = SHT_Receiver_byte();    //读取数据低八位 
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
//**************************非主机模式湿度测试***************************** 
float humier(void) 
{ 
  float sdd,sd; 
  uint  aaa=0; 
  uchar ack; 
  uchar tem1,tem2; 
  StateI2C();                                
   SHT_Master_byte2(0x80);  //地址+写 
   SHT_Master_byte2(0xf5);   //命令：非主机湿度测试 
   do 
   { 
    sht_delay(20); 
     StateI2C(); 
     ack = SHT_Master_byte(0x81);    //命令：读取数据。。等待回应 
   } 
   while(ack==1); 
   tem1=SHT_Receiver_byte();  //读取数据高八位 
 //  Response(0);        //单片机回应 
   tem2 = SHT_Receiver_byte();  //读取数据低八位 
   STOPI2C(); 
   aaa = (aaa|tem1)*256+tem2; 
   aaa = aaa & 0xfffc; 
   sd=(float)(aaa * 0.00190735); 
   sdd=(sd-6); 
   //aaa =(int)((aaa * 0.00190735 -6)*10);   
   //if(aaa>998)aaa=999;///防止湿度超过100% 
   return(sdd); 
} 
//****************************读用户寄存器*********************************** 
unsigned char read_Register(void)     
{ 
  uchar aaa=0 ,ack=0; 
  StateI2C();                  
  ack = SHT_Master_byte(0x80); 
  ack = SHT_Master_byte(0xE7);  //命令：读寄存  
  StateI2C();  
  ack = SHT_Master_byte(0x81); 
  if(ack) 
	  return(ack);   //返回 1 读操作失败了 
  aaa = SHT_Receiver_byte(); 
  STOPI2C(); 
  return(aaa);  
} 

//****************************写用户寄存器*********************************** 
uchar write_Register(uchar aaa)   //不能随便写，默认位不能改   ，先读出来默认位 
{ 
  uchar ack=0; 
  StateI2C();             //写寄存器 
  ack = SHT_Master_byte(0x80); 
  ack = SHT_Master_byte(0xE6); 
  ack = SHT_Master_byte(aaa);    //不能随便写，默认位不能改 
  STOPI2C();   
  return(ack);   //返回 1 写操作失败 
} 
/******************************************************************************  
函数名称:SH11返回温度函数 
修改日期:  
入口参数:无 
返回值: 无  
******************************************************************************/ 
float tep(void) 
{   
       float TEMP=0;  
       TEMP= temper(); 
        return TEMP; 
} 
/******************************************************************************  
函数名称:SH11返回湿度函数 
修改日期:  
入口参数:无 
返回值: 无  
******************************************************************************/ 
float hui(void) 
{ 
        float HUMI=0;  
        HUMI=  humier(); 
        return HUMI; 
/******************************************************************************  
函数名称:SH11返回体感温度函数
修改日期:  
入口参数:温度，湿度
返回值: 体感温度 
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
函数名称:封装PWM自动调速装置
修改日期:  
入口参数:体感温度
返回值: 无
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








