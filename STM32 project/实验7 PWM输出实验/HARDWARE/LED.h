#ifndef __LED_H
#define __LED_H
#include "sys.h"
void LED_Init(void);

#define LED0 PFout(9)
#define LED1 PFout(10)

#endif



