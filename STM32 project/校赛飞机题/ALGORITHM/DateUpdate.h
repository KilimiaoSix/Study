#ifndef __DATEUPDATE_H
#define __DATEUPDATE_H

#include "sys.h"

void buff2pos(void);
void Data_Init(void);
extern int cir_Point_x;
extern int cir_Point_y;

extern int line_Point_x;
extern int line_Point_y;
extern int line_Wide;
extern int line_Angle;

/*标志位 为 1 为有效*/
extern u8 uFindCir_flag; //找圆标志位
extern u8 uFindLin_flag; //找线标志位
extern u8 uLanding;      //降落标志位


#endif




