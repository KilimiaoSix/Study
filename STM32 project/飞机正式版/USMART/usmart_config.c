#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "delay.h"	 	
#include "sys.h"

												 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",	
   (void*)Print_PID,"void Print_PID(void)",
   (void*)Stop,"void Stop(void)",      
   (void*)Start,"void Start(void)",
   (void*)Switch_Auto_or_Manual,"void Switch_Auto_or_Manual(void)",
   (void*)Manual_front_changeval,"void Manual_front_changeval(u16 val)",
   (void*)Manual_reat_changeval,"void Manual_reat_changeval(u16 val)",
   (void*)Manual_right_changeval,"void Manual_right_changeval(u16 val)",
   (void*)Manual_left_changeval,"void Manual_left_changeval(u16 val)",
   (void*)pitchinside_KpLittleincrease,"void pitchinside_KpLittleincrease(void)",
   (void*)pitchinside_KiLittleincrease,"void pitchinside_KiLittleincrease(void)",
   (void*)pitchinside_KdLittleincrease,"void pitchinside_KdLittleincrease(void)",
   (void*)pitchinside_KpBigincrease,"void pitchinside_KpBigincrease(void)",
   (void*)pitchinside_KiBigincrease,"void pitchinside_KiBigincrease(void)",
   (void*)pitchinside_KdBigincrease,"void pitchinside_KdBigincrease(void)",
   (void*)pitchinside_KpLittlereduce,"void pitchinside_KpLittlereduce(void)",
   (void*)pitchinside_KiLittlereduce,"void pitchinside_KiLittlereduce(void)",
   (void*)pitchinside_KdLittlereduce,"void pitchinside_KdLittlereduce(void)",
   (void*)pitchinside_KpBigreduce,"void pitchinside_KpBigreduce(void)",
   (void*)pitchinside_KiBigreduce,"void pitchinside_KiBigreduce(void)",
   (void*)pitchinside_KdBigreduce,"void pitchinside_KdBigreduce(void)", 
   (void*)highPID_KpLittleincrease,"void highPID_KpLittleincrease(void)",
   (void*)highPID_KpBigincrease,"void highPID_KpBigincrease(void)",
   (void*)highPID_KiLittleincrease,"void highPID_KiLittleincrease(void)",
   (void*)highPID_KdLittleincrease,"void highPID_KdLittleincrease(void)",
   (void*)highPID_KiBigincrease,"void highPID_KiBigincrease(void)",
   (void*)highPID_KdBigincrease,"void highPID_KdBigincrease(void)",
   (void*)highPID_KpLittlereduce,"void highPID_KpLittlereduce(void)",
   (void*)highPID_KiLittlereduce,"void highPID_KiLittlereduce(void)",
   (void*)highPID_KdLittlereduce,"void highPID_KdLittlereduce(void)",
   (void*)highPID_KpBigreduce,"void highPID_KpBigreduce(void)",
   (void*)highPID_KiBigreduce,"void highPID_KiBigreduce(void)",
   (void*)highPID_KdBigreduce,"void highPID_KdBigreduce(void)",
   (void*)yawexternal_KpLittleincrease,"void yawexternal_KpLittleincrease(void)",
   (void*)yawexternal_KiLittleincrease,"void yawexternal_KiLittleincrease(void)",
   (void*)yawexternal_KpLittlereduce,"void yawexternal_KpLittlereduce(void)",   
   (void*)yawexternal_KiLittlereduce,"void yawexternal_KiLittlereduce(void)",
   (void*)yawexternal_KpBigincrease,"void yawexternal_KpBigincrease(void)",
   (void*)yawexternal_KiBigincrease,"void yawexternal_KiBigincrease(void)",
   (void*)yawexternal_KpBigreduce,"void yawexternal_KpBigreduce(void)",   
   (void*)yawexternal_KiBigreduce,"void yawexternal_KiBigreduce(void)",  
   (void*)pitchexternal_KpLittleincrease,"void pitchexternal_KpLittleincrease(void)",
   (void*)pitchexternal_KiLittleincrease,"void pitchexternal_KiLittleincrease(void)",
   (void*)pitchexternal_KpLittlereduce,"void pitchexternal_KpLittlereduce(void)",   
   (void*)pitchexternal_KiLittlereduce,"void pitchexternal_KiLittlereduce(void)",
   (void*)pitchexternal_KpBigincrease,"void pitchexternal_KpBigincrease(void)",
   (void*)pitchexternal_KiBigincrease,"void pitchexternal_KiBigincrease(void)",
   (void*)pitchexternal_KpBigreduce,"void pitchexternal_KpBigreduce(void)",   
   (void*)pitchexternal_KiBigreduce,"void pitchexternal_KiBigreduce(void)",   
   (void*)rollexternal_KpLittleincrease,"void rollexternal_KpLittleincrease(void)",
   (void*)rollexternal_KiLittleincrease,"void rollexternal_KiLittleincrease(void)",
   (void*)rollexternal_KpLittlereduce,"void rollexternal_KpLittlereduce(void)",   
   (void*)rollexternal_KiLittlereduce,"void rollexternal_KiLittlereduce(void)",
   (void*)rollexternal_KpBigincrease,"void rollexternal_KpBigincrease(void)",
   (void*)rollexternal_KiBigincrease,"void rollexternal_KiBigincrease(void)",
   (void*)rollexternal_KpBigreduce,"void rollexternal_KpBigreduce(void)",   
   (void*)rollexternal_KiBigreduce,"void rollexternal_KiBigreduce(void)",   
   (void*)yawinside_KpLittleincrease,"void yawinside_KpLittleincrease(void)",
   (void*)yawinside_KiLittleincrease,"void yawinside_KiLittleincrease(void)",
   (void*)yawinside_KdLittleincrease,"void yawinside_KdLittleincrease(void)",
   (void*)yawinside_KpBigincrease,"void yawinside_KpBigincrease(void)",
   (void*)yawinside_KiBigincrease,"void yawinside_KiBigincrease(void)",
   (void*)yawinside_KdBigincrease,"void yawinside_KdBigincrease(void)",
   (void*)yawinside_KpLittlereduce,"void yawinside_KpLittlereduce(void)",
   (void*)yawinside_KiLittlereduce,"void yawinside_KiLittlereduce(void)",
   (void*)yawinside_KdLittlereduce,"void yawinside_KdLittlereduce(void)",
   (void*)yawinside_KpBigreduce,"void yawinside_KpBigreduce(void)",
   (void*)yawinside_KiBigreduce,"void yawinside_KiBigreduce(void)",
   (void*)yawinside_KdBigreduce,"void yawinside_KdBigreduce(void)",    
   (void*)rollinside_KpLittleincrease,"void rollinside_KpLittleincrease(void)",
   (void*)rollinside_KiLittleincrease,"void rollinside_KiLittleincrease(void)",
   (void*)rollinside_KdLittleincrease,"void rollinside_KdLittleincrease(void)",
   (void*)rollinside_KpBigincrease,"void rollinside_KpBigincrease(void)",
   (void*)rollinside_KiBigincrease,"void rollinside_KiBigincrease(void)",
   (void*)rollinside_KdBigincrease,"void rollinside_KdBigincrease(void)",
   (void*)rollinside_KpLittlereduce,"void rollinside_KpLittlereduce(void)",
   (void*)rollinside_KiLittlereduce,"void rollinside_KiLittlereduce(void)",
   (void*)rollinside_KdLittlereduce,"void rollinside_KdLittlereduce(void)",
   (void*)rollinside_KpBigreduce,"void rollinside_KpBigreduce(void)",
   (void*)rollinside_KiBigreduce,"void rollinside_KiBigreduce(void)",
   (void*)rollinside_KdBigreduce,"void rollinside_KdBigreduce(void)",  
   (void*)goalhighchange,"void goalhighchange(float goalhigh)",
   (void*)goalyawchange,"void goalyawchange(float goalyaw)",
   (void*)goalpitchchange,"void goalpitchchange(float goalpitch)",
   (void*)goalrollchange,"void goalrollchange(float goalroll)"  ,       
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















