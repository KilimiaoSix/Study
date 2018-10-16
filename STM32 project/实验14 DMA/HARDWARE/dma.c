#include "dma.h"
void My_DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr)
{
   DMA_InitTypeDef DMA_InitStructure;
   if((u32)DMA_Streamx>(u32)DMA2)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
   }
   else
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
   }
   DMA_DeInit(DMA_Streamx);
   while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE){}  //等待DMA可配置
   DMA_InitStructure.DMA_Channel=chx;  //设置DMA通道
   DMA_InitStructure.DMA_PeripheralBaseAddr=par;  //DMA外设地址
   DMA_InitStructure.DMA_Memory0BaseAddr=mar;  //将DMA地址设置成0模式
   DMA_InitStructure.DMA_DIR=DMA_DIR_MemoryToPeripheral;  //将DMA存储器到外设模式
   DMA_InitStructure.DMA_BufferSize=ndtr;  //数据传输量
   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设非增量模式
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //设置存储器数据长度为8位
   DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;  //使用普通模式
   DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;  //中等优先模式
   DMA_InitStructure.DMA_FIFOMode=DMA_FIFOMode_Disable;  //关闭FIFP
   DMA_InitStructure.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;  //FIFO阈值
   DMA_InitStructure.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //存储器突发单次传输
   DMA_InitStructure.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;  //外设突发单次传输
   DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
   DMA_Init(DMA_Streamx,&DMA_InitStructure);
}
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
   DMA_Cmd(DMA_Streamx,DISABLE);
   while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE){}
   DMA_SetCurrDataCounter(DMA_Streamx,ndtr);
   DMA_Cmd(DMA_Streamx,ENABLE);
   
   
}


