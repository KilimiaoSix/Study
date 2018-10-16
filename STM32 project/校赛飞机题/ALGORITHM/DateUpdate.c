#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "math.h"
#include "DateUpdate.h"
#include "IO.h"
#include "wave.h"
/*标志位 为 1 为有效*/
u8 uFindCir_flag = 0; //找圆标志位
u8 uFindLin_flag = 0; //找线标志位
u8 uLanding = 0;      //降落标志位

/*坐标数据*/
int cir_Point_x = 0;
int cir_Point_y = 0;

int line_Point_x = 0;
int line_Point_y = 0;
int line_Wide = 0;
int line_Angle = 0;

/*
	uFindCir_flag == 1时执行对圆坐标更新
	否则只对线参数更新
*/
void buff2pos(void)
{
 	u16 t = 0;  
	u16 len = 0;
	u8 pos_X = 0;//坐标轴位置
	u8 pos_Y = 0;
	u8 pos_W = 0;
	u8 pos_A = 0;
	
	int symbol_fux = 1;//负号标志位
	int symbol_fuy = 1;
	int symbol_fuw = 1;
	int symbol_fua = 1;
	
	u8 point_x = 0; //小数位数
	u8 point_y = 0;
	u8 point_w = 0;
	u8 point_a = 0;

	if(uLanding == 1)
		return ;
	
	if(USART_RX_STA&0x8000)
	{	
			
		if(USART_RX_BUF[0] == 'c')
		{uFindCir_flag = 1; uLanding = 0; uFindLin_flag = 0;}
		else if(USART_RX_BUF[0] == 'N' || USART_RX_BUF[0] == 0)
		{uFindCir_flag = 0; uLanding = 1; uFindLin_flag = 0; return ;}
		else if(USART_RX_BUF[0] == 'l')
		{uFindCir_flag = 0; uLanding = 0; uFindLin_flag = 1;}
		
/***************处理****************/
		
		if (uFindCir_flag == 1)
		{
			uFindCir_flag = 1; uLanding = 0; uFindLin_flag = 0;
			cir_Point_x = 0;cir_Point_y = 0;
			len = USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			
			/*********************通讯协议 坐标 *************************/
			//格式 ：cxxxxXxxxxY 坐标数据+轴选择（x或y） 回车（\r\n）结尾（大小写均可）
			for(t=1;t <len; t++)  //找出xy的位置
			{	
				if(USART_RX_BUF[t] == 0x78 || USART_RX_BUF[t] == 0x58) //x轴
					pos_X = t;
				if(USART_RX_BUF[t] == 0x79 || USART_RX_BUF[t] == 0x59) //y轴
					pos_Y = t;
			}
			if(pos_X < pos_Y)
			{			
				for(t=1; t<pos_X; t++) 				//处理x坐标数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fux = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_x = pos_X - (t + 1)	;	 //求出小数位数
					else				
						cir_Point_x =	(USART_RX_BUF[t] - 48) + cir_Point_x * 10; //累计数字
				}
				
				for(t = pos_X+1; t<pos_Y; t++) 	//处理y坐标数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fuy = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_y = pos_Y - (t + 1)	;	 //求出小数位数
					else				
						cir_Point_y =	(USART_RX_BUF[t] - 48) + cir_Point_y * 10; //累计数字
				}
			}
			else
			{
				for(t=1; t<pos_Y; t++) 				//处理y坐标数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fuy = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_y = pos_Y - (t+1)	;	 //求出小数位数
					else				
						cir_Point_y =	(USART_RX_BUF[t]-48) + cir_Point_y * 10; //累计数字
				}
				
				for(t=pos_Y+1; t<pos_X; t++) 	//处理x坐标数据
				{
					if((USART_RX_BUF[t]-48)==-3)	//如果有负号
						symbol_fux = -1 ;           //负号标志位
					else if((USART_RX_BUF[t]-48)==-2) // 如果有小数点
						point_x = pos_X - (t+1)	;	 //求出小数位数
					else				
						cir_Point_x =	(USART_RX_BUF[t] - 48) + cir_Point_x * 10; //累计数字
				}
			}
			
			cir_Point_x = symbol_fux*cir_Point_x*pow(10,-point_x);
			cir_Point_y = symbol_fuy*cir_Point_y*pow(10,-point_y);		
			/*坐标限幅*/
			if (cir_Point_x > 160||cir_Point_x == 0) cir_Point_x = 80;
         if (cir_Point_y > 120||cir_Point_y == 0) cir_Point_y = 60;
		}//接收数据为 圆类型 数据			
	  
		else if(uFindLin_flag == 1) //否则默认以 线类型 数据接收
		{
			uFindCir_flag = 0; uLanding = 0; uFindLin_flag = 1;
			line_Point_x = 0;line_Point_y = 0;line_Wide = 0;line_Angle = 0;
			len = USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			
			/*********************通讯协议 坐标 *************************/
			//格式 ：lxxxxXxxxxYxxxxWxxxxA 坐标数据+轴选择（x或y） 回车（\r\n）结尾（大小写均可）
			for(t=1;t <len; t++)  //找出xy的位置
			{	
				if(USART_RX_BUF[t] == 0x78 || USART_RX_BUF[t] == 0x58) //x轴
					pos_X = t;
				if(USART_RX_BUF[t] == 0x79 || USART_RX_BUF[t] == 0x59) //y轴
					pos_Y = t;
				if(USART_RX_BUF[t] == 0x77 || USART_RX_BUF[t] == 0x57) //w
					pos_W = t;
				if(USART_RX_BUF[t] == 0x61 || USART_RX_BUF[t] == 0x41) //a
					pos_A = t;
			}
			if(pos_X < pos_Y && pos_W < pos_A)
			{			
				for(t=1; t<pos_X; t++) 				//处理x坐标数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fux = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_x = pos_X - (t + 1)	;	 //求出小数位数
					else				
						line_Point_x =	(USART_RX_BUF[t] - 48) + line_Point_x * 10; //累计数字
				}
				
				for(t = pos_X+1; t<pos_Y; t++) 	//处理y坐标数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fuy = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_y = pos_Y - (t + 1)	;	 //求出小数位数
					else				
						line_Point_y =	(USART_RX_BUF[t] - 48) + line_Point_y * 10; //累计数字
				}
				
				for(t = pos_Y+1; t<pos_W; t++) 	//处理w数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fuw = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_w = pos_W - (t + 1)	;	 //求出小数位数
					else				
						line_Wide =	(USART_RX_BUF[t] - 48) + line_Wide * 10; //累计数字
				}	

				for(t = pos_W+1; t<pos_A; t++) 	//处理a数据
				{
					if((USART_RX_BUF[t] - 48) == -3)	//如果有负号
						symbol_fua = -1 ;           //负号标志位
					else if((USART_RX_BUF[t] - 48) == -2) // 如果有小数点
						point_a = pos_A - (t + 1)	;	 //求出小数位数
					else				
						line_Angle =	(USART_RX_BUF[t] - 48) + line_Angle * 10; //累计数字
				}						
			}
			
			line_Point_x = symbol_fux*line_Point_x*pow(10,-point_x);
			line_Point_y = symbol_fuy*line_Point_y*pow(10,-point_y);
			line_Wide    = symbol_fuw*line_Wide   *pow(10,-point_w);
			line_Angle   = symbol_fua*line_Angle  *pow(10,-point_a);
			/*坐标限幅*/
         if (line_Point_x > 160||line_Point_x == 0) line_Point_x = 80;
         if (line_Point_y > 120||line_Point_y == 0) line_Point_y = 60;
         if (line_Wide > 160)                       line_Wide = 0;
         if (line_Angle > 180||line_Angle < -180)   line_Angle = 0;
		}//线类型 数据接收结尾
		
		/*转换处理完成后全部清零处理*/
		for(t=0;t<len;t++)
		{
			USART_RX_BUF[t]='0';
		}	
		pos_X = 0;//坐标轴位置
		pos_Y = 0;
		pos_W = 0;
		pos_A = 0;
	
		symbol_fux = 1;//负号标志位
		symbol_fuy = 1;
		symbol_fuw = 1;
		symbol_fua = 1;
	
		point_x = 0; //小数位数
		point_y = 0;
		point_w = 0;
		point_a = 0;
		
		USART_RX_STA=0;
	}//接受到数据判断结尾
	
}//函数结尾			
void Data_Init(void)
{
//   do
//   {
//      buff2pos();  //不断读取数据openMV发来的数据
//      if(line_Point_x||line_Point_y||line_Wide||line_Angle||cir_Point_x||cir_Point_y)
//      {
//         LED0=1;
//         delay_ms(2000);
//         break;
//      }
//   }while(1);
   do
   {
      Get_High();
      if(high)
      {
         LED1=1;
         delay_ms(2000);
         break;
      }
   }while(1);
}
