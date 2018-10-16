#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PDout(13)
#define LED1 PDout(14)	

void LED_Init(void);

		 				    
#endif
