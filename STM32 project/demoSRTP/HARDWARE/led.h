#ifndef __LED_H
#define __LED_H

#include "sys.h"
void LED_Init(void);

#define LED0 PBout(0)
#define LED1 PBout(1)
#endif


