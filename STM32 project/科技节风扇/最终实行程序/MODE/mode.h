#ifndef __MODE_H
#define __MODE_H
#include "sys.h"
#include "usart.h"
#include "SHT21.h"
#include "Switch.h"
#include "delay.h"
#include "miniMIU.h"
#include "PWM.h"

extern int16_t Gear;
void Fan_Mode_Auto(void);
void Humidifier_Mode_Auto(void);

#endif








