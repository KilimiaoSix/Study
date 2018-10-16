#ifndef __MAIN_H
#define __MAIN_H

#include "sys.h"
#include "main.h"
#include "Echo.h"
#include "IMU.h"
#include "LED.h"
#include "timer.h"
#include "pwm.h"
#include "usmart.h"
#include "usart.h"
#include "delay.h"
#include "exti.h"
#include "function.h"
#include "PID.h"


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean; 

extern Status Autopilot_license;
extern Status Start_permission;
extern Status SystemFlag;
#endif




