#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "main.h"

extern int LongLine_Flag,Number;

void Traction_control(PIDTypeDef *X,PIDTypeDef *Y,PIDTypeDef *Z);
void High_control(PIDTypeDef *H,float high);
void Chase_Circle(PIDTypeDef *X,PIDTypeDef *Y);
void Land(PIDTypeDef *H);
void Take_off(PIDTypeDef *H);
void Straight_line_judgment(void);
void Flight_control_Unlock(void);

#endif






