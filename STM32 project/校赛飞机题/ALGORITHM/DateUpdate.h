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

/*��־λ Ϊ 1 Ϊ��Ч*/
extern u8 uFindCir_flag; //��Բ��־λ
extern u8 uFindLin_flag; //���߱�־λ
extern u8 uLanding;      //�����־λ


#endif




