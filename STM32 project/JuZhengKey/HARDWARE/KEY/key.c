///////////////////////////////////////////////////////////////////////////////
//����ƽ̨  STM32F103ZET6  ս��V3
//PF0-3�����ó��������  ��Ϊ4x4���̵���
//PF4-7�����ó���������  ��Ϊ4x4���̵���
//�������������LED������������   
////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "key.h"
#include "led.h"
#include "sys.h" 
#include "delay.h"

u16 keyz=0;

void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTA,PORTFʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//KEY0-KEY3  ������̵���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //���ó��������  GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY4-KEY7  ������̵���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //���ó���������  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOF,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
	

}



u8 keyscan(void)
{ 
	uint8_t LIE,HANG,k,i=0;
	
	GPIO_Write(GPIOF, 0xF0);                            //D0-D3���ͣ�D4-D7����
	if((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)          //�а�������
	{
	  delay_ms(40);                                     //����
	   if((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)       //�ٴ��ж��Ƿ���
	   {
		   LIE=GPIO_ReadInputData(GPIOF);                 //��ȡ�������º�õ��Ĵ���
		   HANG=LIE;                                      //�����븴�Ƹ���
		   LIE=~LIE;                                      //������ȡ�������磺����ĳ�����õ�0111 0000��ȡ����õ�1000 1111;
		   LIE=LIE&0XF0;                                  //�õ���1000 1111&1111 0000�õ�1000 0000���õ�����
		   for(i=0;i<4&&((HANG&0xF0)!=0xF0);i++)          //��ν������ߣ��ж�������ԭ����͵�λ�Ƿ���
		   {                                              //����֮ǰ��⵽Ϊ�͵��б�����˳�
		       GPIO_Write(GPIOF, (HANG&0xF0)|(0x01<<i));  //������ɨ�裬��ν��п������ߣ��б���Ϊ����ʱ��״̬
		       HANG=GPIO_ReadInputData(GPIOF);            //��ȡIO�ڣ������ж��Ƿ�ɨ�赽������			   
		   }
		   HANG&=0x0F;                                    //����ֵȡ��
		   k=LIE|HANG;                                    //���������õ�����
		   GPIO_Write(GPIOF, 0xF0);                       //D0-D3���ͣ�D4-D7���ߣ��˴�����������״̬��ʼ��Ϊδ����ʱ��״̬
	     while((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)  //���ͷ�
		   {
		        delay_ms(40);                             //����������ʱ���賤һ�㣬С��������ʱ����Զ�һ�㣬�󰴼��������������賤һ��
		   }
		   return k;                                      //���ؼ��� 
	   }
	}	
	return (0);                                         //�޼�����,����0
}


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           u8 keychuli(void)
{ 
	uint8_t key_1=0;
	uint8_t i=1;
	while(i)
	{
		keyz=keyscan();
		if(keyz!=0)
		{ 
			switch(keyz)
			{
				//case 0x11: PBout(5)=0;delay_ms(16000);PBout(5)=1;key_1=0;i--;break; 	//S4
				//case 0x21: PBout(5)=0;delay_ms(28000);PBout(5)=1;key_1=0;i--;break; 	//S8
				//case 0x41: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S12
				//case 0x81: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S16
				
				case 0x12: PBout(5)=0;delay_ms(30000);PBout(5)=1;key_1=0;i--;break; 	//S3
				//case 0x22: PBout(5)=0;delay_ms(25000);PBout(5)=1;key_1=0;i--;break; 	//S7
				//case 0x42: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S11
				//case 0x82: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S15
				
				case 0x14: PBout(5)=0;delay_ms(20000);PBout(5)=1;key_1=0;i--;break; 	//S2
				//case 0x24: PBout(5)=0;delay_ms(22000);PBout(5)=1;key_1=0;i--;break; 	//S6
				//case 0x44: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S10
				//case 0x84: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S14
				
				case 0x18: PDout(13)=1;delay_ms(10000);PDout(13)=0;key_1=0;i--;break; 	//S1
				//case 0x28: PBout(5)=0;delay_ms(19000);PBout(5)=1;key_1=0;i--;break; 	//S5
				//case 0x48: PBout(5)=0;delay_ms(31000);PBout(5)=1;key_1=0;i--;break; 	//S9
				//case 0x88: PBout(5)=0;delay_ms(10000);PBout(5)=1;key_1=0;i--;break; 	//S13
				default:break;
			}
		}
	}
	return key_1;
	
}

