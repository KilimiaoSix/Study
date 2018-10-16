#ifndef __AVEFILTERING_H
#define __AVEFILTERING_H

#include "sys.h"
#include "stdlib.h"
#include "stdio.h"
#define Deep 5

typedef struct{
	float Storagearea[5];
	int UpdateFlag;
}Filterspace;

Filterspace* Create_New_Space(void);
void DelateSpace(Filterspace *p);
void FilterspaceInit(Filterspace *p,float Datagroup[Deep]);
void AddNewdate(Filterspace *p,int value);
float AveDate(Filterspace *p);

#endif
