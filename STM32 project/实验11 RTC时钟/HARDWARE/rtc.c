#include "rtc.h"
#include "led.h"
u8 My_RTC_Init(void)
{
   RTC_InitTypeDef RTC_InitStructure;
   
   u16 retry=0x1FFF;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
   PWR_BackupAccessCmd(ENABLE);
   //第一步
   if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x5050)
   {
      RCC_LSEConfig(RCC_LSE_ON);
      while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET)
      {
         retry++;
         delay_ms(10);
      }
      if(retry==0)
         return 1;
      RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
      RCC_RTCCLKCmd(ENABLE);
      
      RTC_InitStructure.RTC_AsynchPrediv=0x7f;
      RTC_InitStructure.RTC_SynchPrediv=0xff;
      RTC_InitStructure.RTC_HourFormat=RTC_HourFormat_24;
      
      RTC_Init(&RTC_InitStructure);
      
      RTC_Set_Time(10,7,0,RTC_H12_AM);
      RTC_Set_Date(17,3,17,6);
   }
   return 0;
}
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm)
{
	RTC_TimeTypeDef RTC_TimeTypeInitStructure;
	
	RTC_TimeTypeInitStructure.RTC_Hours=hour;
	RTC_TimeTypeInitStructure.RTC_Minutes=min;
	RTC_TimeTypeInitStructure.RTC_Seconds=sec;
	RTC_TimeTypeInitStructure.RTC_H12=ampm;
	
	return RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructure);
	
}
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=date;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	return RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}
//设置闹钟的时间
//week：星期 hour：小时 min 分钟 sec 秒
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec)
{
   EXTI_InitTypeDef EXTI_InitStructure;
   RTC_AlarmTypeDef RTC_AlarmStructure;
   RTC_TimeTypeDef RTC_TimeStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
   RTC_AlarmCmd(RTC_Alarm_A,DISABLE);//关闭闹钟A
   
   RTC_TimeStructure.RTC_Hours=hour;
   RTC_TimeStructure.RTC_Minutes=min;
   RTC_TimeStructure.RTC_Seconds=sec;
   RTC_TimeStructure.RTC_H12=RTC_H12_AM;
   
   RTC_AlarmStructure.RTC_AlarmDateWeekDay=week;
   RTC_AlarmStructure.RTC_AlarmDateWeekDaySel=RTC_AlarmDateWeekDaySel_WeekDay;
   RTC_AlarmStructure.RTC_AlarmMask=RTC_AlarmMask_None;
   RTC_AlarmStructure.RTC_AlarmTime=RTC_TimeStructure;
   RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmStructure);
   
   RTC_ClearITPendingBit(RTC_IT_ALRA);
   EXTI_ClearITPendingBit(EXTI_Line17);
   
   RTC_ITConfig(RTC_IT_ALRA,ENABLE);
   RTC_AlarmCmd(RTC_Alarm_A,ENABLE);
   
   EXTI_InitStructure.EXTI_Line=EXTI_Line17;
   EXTI_InitStructure.EXTI_LineCmd=ENABLE;
   EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
   EXTI_Init(&EXTI_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel=RTC_Alarm_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   
}
void RTC_Set_WakeUp(u32 wksel,u16 cnt)
{
   NVIC_InitTypeDef NVIC_InitStructure;
   EXTI_InitTypeDef EXTI_InitStructure;
   RTC_WakeUpCmd(DISABLE);
   RTC_WakeUpClockConfig(wksel);//选择唤醒时钟
   RTC_SetWakeUpCounter(cnt);//设置Wake up自动重装载寄存器
   RTC_ClearITPendingBit(RTC_IT_WUT);
   EXTI_ClearITPendingBit(EXTI_Line22);
   RTC_ITConfig(RTC_IT_WUT,ENABLE);
   RTC_WakeUpCmd(ENABLE);
   EXTI_InitStructure.EXTI_Line=EXTI_Line22;
   EXTI_InitStructure.EXTI_LineCmd=ENABLE;
   EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
   EXTI_Init(&EXTI_InitStructure);
   
   NVIC_InitStructure.NVIC_IRQChannel=RTC_WKUP_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
   NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}
void RTC_Alarm_IRQHandler(void)
{
   if(RTC_GetFlagStatus(RTC_FLAG_ALRAF)==SET)
   {
      RTC_ClearFlag(RTC_FLAG_ALRAF);
      printf("ALARMA\r\n");
      BEEP=1;
   }
   EXTI_ClearITPendingBit(EXTI_Line17);
}
void RTC_WKUP_IRQHandler(void)
{
   if(RTC_GetFlagStatus(RTC_FLAG_WUTF)==SET)
   {
      RTC_ClearFlag(RTC_FLAG_WUTF);
      LED1=!LED1;
   }
   EXTI_ClearITPendingBit(EXTI_Line22);
}


   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   


