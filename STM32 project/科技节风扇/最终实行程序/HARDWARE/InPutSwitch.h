#ifndef __INPUTSWITCH_H
#define __INPUTSWITCH_H
#include "sys.h"
#include "delay.h"
#include "Switch.h"
#include "LED.h"


extern int16_t Fan_MODE_SW;
extern int16_t Humidifier_MODE_SW;



void KEY_Init(void);
void EXTIX_Init(void);

#endif








