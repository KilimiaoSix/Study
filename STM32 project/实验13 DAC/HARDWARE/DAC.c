#include "DAC.h"
void DAC1_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   DAC_InitTypeDef DAC_InitStructure;
   
   //以下为初始化相关时钟
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
   
   //以下是对I/O口的配置
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;  //模拟输入/输出
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;  //设置下拉
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   //DAC相关参数配置
   DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;  //关闭输出缓存
   DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;  //关闭触发功能
   DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;  //关闭波形发生器
   DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;  //屏蔽，幅值配置
   
   DAC_Init(DAC_Channel_1,&DAC_InitStructure);
   DAC_Cmd(DAC_Channel_1,ENABLE);
   DAC_SetChannel1Data(DAC_Align_12b_R,0);  //设置12位右对齐数据格式
   
   
   
   
   
}
void Dac1_Set_Vol(u16 vol)
{
   double temp=vol;
   temp/=1000;
   temp=temp*4096/3.3;
   DAC_SetChannel1Data(DAC_Align_12b_R,temp);
   
   
}






