#ifndef  __IO_H
#define  __IO_H

#include "sys.h"

#define LED0 PBout(12)
#define LED1 PBout(13)

#define openMVControl PBout(14)

void IO_Init(void);
void LED_Init(void);


#endif


