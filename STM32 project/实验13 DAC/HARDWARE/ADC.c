#include "ADC.h"

void My_ADC_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   ADC_CommonInitTypeDef ADC_CommonInitStructure;
   ADC_InitTypeDef ADC_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
   
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;  //ģ������
   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //������Ҳ������
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5; 
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
   
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);  //ADC1��λ
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);   //������λ
   
   //����ΪADCͨ�ò�������
   ADC_CommonInitStructure.ADC_Mode=ADC_Mode_Independent;  //����ADCģʽΪ����ģʽ
   ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;   //DMAʧ��
   ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;  //���β���������ʱ������
   ADC_CommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4; //ʱ���ķ�Ƶ����ֹƵ�ʳ���36Mhz;
   
   ADC_CommonInit(&ADC_CommonInitStructure);
   
   //����ΪADC1��ز�������
   ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;  //12λ�ֱ���ģʽ
   ADC_InitStructure.ADC_ScanConvMode=DISABLE;  //�ر�ɨ��ģʽ
   ADC_InitStructure.ADC_ContinuousConvMode=DISABLE; //�ر�����ת��ģʽ
   ADC_InitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None; //�رմ������
   ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //�Ҷ���ģʽ
   ADC_InitStructure.ADC_NbrOfConversion=1;  //һ��ת���ڹ���������
   
   ADC_Init(ADC1,&ADC_InitStructure);
   
   ADC_Cmd(ADC1,ENABLE);  //����ADת����1  
}   
u16 Get_ADC(u8 ch)
{
   ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_480Cycles);
   ADC_SoftwareStartConv(ADC1);  //ʹ��ָ��ADCλ
   while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //�ȴ�ADC1ת������
   return ADC_GetConversionValue(ADC1);  //�������һ��ADC1�������е�ת�����
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














