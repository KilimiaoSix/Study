#ifndef __TPAD_H
#define __TPAD_H
#include "delay.h"
#include "sys.h"
#include "usart.h"
#define TPAD_ARR_MAX_VAL 0xFFFFFFFF
#define TPAD_GATE_VAL 100
extern vu16 tpad_default_val;
void TIM2_CH1_Cap_Init(u32 arr,u16 psc);
void TPAD_Reset(void);
u8 TPAD_Init(u8 psc);
u16 TPAD_Get_Val(void);
u8 TPAD_Scan(u8 mode);
#endif


