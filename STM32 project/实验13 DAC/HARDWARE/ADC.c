#include "ADC.h"

void My_ADC_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   ADC_CommonInitTypeDef ADC_CommonInitStructure;
   ADC_InitTypeDef ADC_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;  //模拟输入
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //不上拉也不下拉
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5; 
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);  //ADC1复位
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);   //结束复位
   
   //以下为ADC通用参数设置
   ADC_CommonInitStructure.ADC_Mode=ADC_Mode_Independent;  //配置ADC模式为独立模式
   ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;   //DMA失能
   ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;  //两次采样间隔五个时钟周期
   ADC_CommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4; //时钟四分频，防止频率超过36Mhz;
   
   ADC_CommonInit(&ADC_CommonInitStructure);
   
   //以下为ADC1相关参数配置
   ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;  //12位分辨率模式
   ADC_InitStructure.ADC_ScanConvMode=DISABLE;  //关闭扫描模式
   ADC_InitStructure.ADC_ContinuousConvMode=DISABLE; //关闭连续转换模式
   ADC_InitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None; //关闭触发检测
   ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //右对齐模式
   ADC_InitStructure.ADC_NbrOfConversion=1;  //一个转换在规则序列中
   
   ADC_Init(ADC1,&ADC_InitStructure);
   
   ADC_Cmd(ADC1,ENABLE);  //启动AD转换器1  
}   
u16 Get_ADC(u8 ch)
{
   ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_480Cycles);
   ADC_SoftwareStartConv(ADC1);  //使能指定ADC位
   while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //等待ADC1转换结束
   return ADC_GetConversionValue(ADC1);  //返回最近一个ADC1规则组中的转换结果
}
u16 Get_Adc_Average(u8 ch,u8 times)
{
   u32 temp_val=0;
   u8 t;
   for(t=0;t<times;t++)
   {
      temp_val+=Get_ADC(ch);
      delay_ms(5);
   }
   return temp_val/times;
}














