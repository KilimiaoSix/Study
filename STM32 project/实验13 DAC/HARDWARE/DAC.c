#include "DAC.h"
void DAC1_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   DAC_InitTypeDef DAC_InitStructure;
   
   //����Ϊ��ʼ�����ʱ��
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
   
   //�����Ƕ�I/O�ڵ�����
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;  //ģ������/���
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;  //��������
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   //DAC��ز�������
   DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;  //�ر��������
   DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;  //�رմ�������
   DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;  //�رղ��η�����
   DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;  //���Σ���ֵ����
   
   DAC_Init(DAC_Channel_1,&DAC_InitStructure);
   DAC_Cmd(DAC_Channel_1,ENABLE);
   DAC_SetChannel1Data(DAC_Align_12b_R,0);  //����12λ�Ҷ������ݸ�ʽ
   
   
   
   
   
}
void Dac1_Set_Vol(u16 vol)
{
   double temp=vol;
   temp/=1000;
   temp=temp*4096/3.3;
   DAC_SetChannel1Data(DAC_Align_12b_R,temp);
   
   
}






