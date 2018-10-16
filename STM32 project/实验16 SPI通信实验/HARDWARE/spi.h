#ifndef __SPI_H
#define __SPI_H


#include "sys.h"


void SPI1_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
#endif




