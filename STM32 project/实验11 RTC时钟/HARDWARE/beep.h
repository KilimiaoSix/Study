#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"
void BEEP_Init(void);
#define BEEP PFout(8)
#endif

