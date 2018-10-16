/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "Mcu_config.h"
/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval : None
  */


void MCU_Init(void)
{
	/* Configure the SysTick */
	SysTick_Configuration();
  /* Configure the usart */
  USART2_Configuration();
}


void USART2_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIOA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  
  /* Enable USART2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* Connect PA2 to USARTx_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  
  /* Connect PA3 to USARTx_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_DeInit(USART2);
	
  /* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/* NVIC configuration */
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
}

void SysTick_Configuration(void)
{
	if (SysTick_Config(SystemCoreClock / SycTi))  //1ms
	{
		while(1);
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//disable systick
}

static uint32_t TimingDelay;

void delay_1ms(uint32_t delay_ms)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;// enable systick
	TimingDelay = delay_ms;
  while(TimingDelay != 0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//disable systick
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


