#include "24cxx.h"
void AT24CXX_Init(void)
{
   IIC_Init();
}
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
   u8 temp=0;
   IIC_Start();
   if(EE_TYPE>AT24C16)
   {
      IIC_Send_Byte(0xa0);  //发送写命令
      IIC_Wait_Ack();
      IIC_Send_Byte(ReadAddr>>8);  //发送高位地址
   }else IIC_Send_Byte(0xa0+((ReadAddr/256)<<1));  //发送器件地址，写数据
   IIC_Wait_Ack();
   IIC_Send_Byte(ReadAddr%256);  //发送低位地址
   IIC_Wait_Ack();
   IIC_Start();
   IIC_Send_Byte(0xa1);  //进入接受模式
   IIC_Wait_Ack();
   temp=IIC_Read_Byte(0);
   IIC_Stop();  //停止接受
   return temp;
}
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{
   IIC_Start();
   if(EE_TYPE>AT24C16)
   {
      IIC_Send_Byte(0xa0);  //发送写命令
      IIC_Wait_Ack();
      IIC_Send_Byte(WriteAddr>>8);//发送高位地址
   }else IIC_Send_Byte(0xa0+((WriteAddr/256)<<1));
   IIC_Wait_Ack();
   IIC_Send_Byte(WriteAddr%256);  //发送低位地址
   IIC_Wait_Ack();
   IIC_Send_Byte(DataToWrite);
   IIC_Wait_Ack();
   IIC_Stop();
   delay_ms(10);
}
//在AT4CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据
//WriteAddr 开始写入的地址
//DataToWrite 数据数组首地址
//Len 要写入数据的长度
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{
   u8 t;
   for(t=0;t<Len;t++)
   {
      AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
   }
}
//在AT24CXX里面的指定地址读出长度为Len的数据
//ReadAddr 开始读出的地址
//返回值 数据
//Len 数据的长度
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{
   u8 t;
   u32 temp=0;
   for(t=0;t<Len;t++)
   {
      temp<<=8;
      temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1);
   }
   return temp;
   
}
//检查AT24CXX是否正常
//这里用24XX的最后一个地址(255)来存储标志字
//如果用24C其他系列，这个地址要改
//返回1 检测成功
//返回0 检测失败
u8 AT24CXX_Check(void)
{
   u8 temp;
   temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX
   if(temp==0x55)
      return 0;
   else//排除第一次初始化的情况
   {
      AT24CXX_WriteOneByte(255,0X55);
      temp=AT24CXX_ReadOneByte(255);
      if(temp==0x55)
         return 0;
   }
   return 1;
}
//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr 开始读出的地址 对24c02为0~255
//pBuffer 数据数组的首地址
//NumToRead 要读出数据的个数
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{ 
   while(NumToRead)
   {
      *pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);
      NumToRead--;
   }
   
}

void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
   while(NumToWrite--)
   {
      AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
      WriteAddr++;
      pBuffer++;
   }
   
   
   
}
