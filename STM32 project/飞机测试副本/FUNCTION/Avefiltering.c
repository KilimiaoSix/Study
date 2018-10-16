#include "Avefiltering.h"
Filterspace* Create_New_Space(void)
{
	return (Filterspace*)malloc(sizeof(Filterspace));
}
void DelateSpace(Filterspace *p)
{
	free(p);
}
void FilterspaceInit(Filterspace *p,float Datagroup[Deep])
{
	int i=0;
	for(i=0;i<Deep;i++)
		p->Storagearea[i]=Datagroup[i];
	p->UpdateFlag=i;
}
void AddNewdate(Filterspace *p,int value)
{
	++p->UpdateFlag;
	if(p->UpdateFlag>=Deep)
		p->UpdateFlag=0;
	p->Storagearea[p->UpdateFlag]=value;
}
float AveDate(Filterspace *p)
{
	int i=0;
	int sum=0;
	for(i=0;i<Deep;i++)
		sum+=p->Storagearea[i];
	return sum/Deep;
}
