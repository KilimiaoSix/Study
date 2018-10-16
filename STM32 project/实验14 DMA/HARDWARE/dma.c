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
   while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE){}  //�ȴ�DMA������
   DMA_InitStructure.DMA_Channel=chx;  //����DMAͨ��
   DMA_InitStructure.DMA_PeripheralBaseAddr=par;  //DMA�����ַ
   DMA_InitStructure.DMA_Memory0BaseAddr=mar;  //��DMA��ַ���ó�0ģʽ
   DMA_InitStructure.DMA_DIR=DMA_DIR_MemoryToPeripheral;  //��DMA�洢��������ģʽ
   DMA_InitStructure.DMA_BufferSize=ndtr;  //���ݴ�����
   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//���������ģʽ
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;  //���ô洢�����ݳ���Ϊ8λ
   DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;  //ʹ����ͨģʽ
   DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;  //�е�����ģʽ
   DMA_InitStructure.DMA_FIFOMode=DMA_FIFOMode_Disable;  //�ر�FIFP
   DMA_InitStructure.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;  //FIFO��ֵ
   DMA_InitStructure.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //�洢��ͻ�����δ���
   DMA_InitStructure.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;  //����ͻ�����δ���
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


