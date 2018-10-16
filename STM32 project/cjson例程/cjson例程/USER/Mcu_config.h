/**
  ******************************************************************************
  * @file    Mcu_config.h 
  * @author  liuwenliang
  * @version V0.0.1
  * @date    2015-05-18
  * @brief   This file contains the mcu coofigure and initialization.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCU_CPNFIG_H
#define __MCU_CPNFIG_H

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#define	SycTi		1000	//1mS

void MCU_Init(void);
void USART2_Configuration(void);
void SysTick_Configuration(void);
void delay_1ms(uint32_t delay_ms);
void TimingDelay_Decrement(void);
#endif /* __MCU_CPNFIG_H */
