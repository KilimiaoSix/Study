#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
char x[200],y[200];
int flag;
int i=0,j=0;
int x0,y0;
 void My_USART1_Init(void)
 {
	 USART_InitTypeDef USART_InitStructure;//定义结构体变量USART_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;//定义结构体变量NVIC_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能串口1时钟；
	 
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA时钟；
	 
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);//将GPIOA9,GPIOA10映射到串口1

	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;//将Pin9和Pin10设置；
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//设置模式为复用模式；
	 GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//将其上拉
	 GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//定义为推挽输出模式
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//设置频率为100MHz
	 GPIO_Init(GPIOA,&GPIO_InitStructure);//调用初始化函数
	 
	 USART_InitStructure.USART_BaudRate=115200;//设置波特率为115200
	 USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用硬件流控制
	 USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//设置模式为发送与接受
	 USART_InitStructure.USART_Parity=USART_Parity_No;//设置不进行奇偶校验
	 USART_InitStructure.USART_StopBits=USART_StopBits_1;//设置停止位为1个
	 USART_InitStructure.USART_WordLength=USART_WordLength_8b;//设置自字长为八位
	 USART_Init(USART1,&USART_InitStructure);//调用初始化函数
	 
	 USART_Cmd(USART1,ENABLE);//使能串口1
	 
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能中断
	 
	 NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//设置通道为串口1
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//设置抢占优先级为1
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//设置响应优先级为1
	 NVIC_Init(&NVIC_InitStructure);//调用初始化函数
 }
 void USART1_IRQHandler(void)
 {
	 u8 res;
	 if(USART_GetITStatus(USART1,USART_IT_RXNE))//如果发生的中断
	 {
		 res=USART_ReceiveData(USART1);//接受串口1的数据
       if(res=='(')
       {
          flag=1;
          i=0;
       }
       else if(flag==1&&res!=','&&res!=')')
       {
          x[i]=res;
          i++;
       }
       else if(res==',')
       {
          flag=2;
          j=0;
       }
       else if(flag==2&&res!=')')
       {
          y[j]=res;
          j++;
       }
       else if(res==')')
       {
          flag=0;
       }
		 USART_SendData(USART1,res);//往串口1发送数据
	 }
	 
 }
 int main()
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组
	 My_USART1_Init();//初始化串口1
	 while(1)
    {
       if(flag==0)
       {
          switch(i+1)
          {
             case 1:
                x0=x[0];break;
             case 2:
                x0=x[0]*10+x[1];break;
             case 3:
                x0=x[0]*100+x[1]*10+x[2];break;
             case 4:
                x0=x[0]*1000+x[1]*100+x[2]*10+x[3];break;
             default:break;
          }
          switch(j+1)
          {
             case 1:
                y0=y[0];break;
             case 2:
                y0=y[0]*10+y[1];break;
             case 3:
                y0=y[0]*100+y[1]*10+y[2];break;
             case 4:
                y0=y[0]*1000+y[1]*100+y[2]*10+y[3];break;
             default:break;
          }
          printf("%d,%d\r\n",x0,y0);
       }
    }
 }
 


