#ifndef __SWITCH_H
#define __SWITCH_H
#include "sys.h"
#define Humidifier PBout(15)
#define ON 1
#define OFF 0
void SW_Init(void);
void SW_Judge(u8 j);

#endif


