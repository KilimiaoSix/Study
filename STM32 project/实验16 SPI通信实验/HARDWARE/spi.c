#include "spi.h"
void SPI1_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   SPI_InitTypeDef SPI_InitStructure;
   
   //使能相关时钟线
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);  //使能挂载在APB2总线上的SPI1时钟
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  //使能挂载在AHB1总线上的GPIOB
   
   //配置GPIO
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  //初始化PB3,4,5
   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;  //定义为上拉复用模式
   
   GPIO_Init(GPIOB,&GPIO_InitStructure);  //初始化
   
   //配置引脚复用映射
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
   GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
   //将PB3,PB4,PB5复用为SPI1
   
   //Reset SPI
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
   
   SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
   SPI_InitStructure.SPI_Mode=SPI_Mode_Master;  //设置为主机模式
   SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;  //数据传输位为8位
   SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;  //串行同步时钟的空闲状态为高电平
   SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;  //串行同步时钟的第二个跳变沿数据被采样
   SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;  //NSS信号由软件管理
   SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;  //定义波特率预分配值：波特率预分频为256
   SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;  //指定数据传输从MSB开始
   SPI_InitStructure.SPI_CRCPolynomial=7;//CRC值计算的多项式
   SPI_Init(SPI1,&SPI_InitStructure);
   
   SPI_Cmd(SPI1,ENABLE);
   SPI1_ReadWriteByte(0xff);  //开始数据传输
}
//SPI1 速度设置函数
//SPI速度 APB2/分频系数
//分配系数 256
//APB2时钟为84Mhz
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
   assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
   SPI1->CR1&=0xffc7;  //清零寄存器位3-5 
   SPI1->CR1|=SPI_BaudRatePrescaler;  //设置SPI1速度
   SPI_Cmd(SPI1,ENABLE);
}
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{
   while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);//等待发送区清空
   SPI_I2S_SendData(SPI1,TxData);
   while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);//等待接收完一个byte
   return SPI_I2S_ReceiveData(SPI1);
}


