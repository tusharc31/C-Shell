#include"global.h"
#include "headers.h"
void init()
{
	fgprocess=-1;
	root=(struct bgprocess*)malloc(sizeof(struct bgprocess));
	root->prev=NULL;
	root->next=NULL;
	root->pid=-1;
	root->st=0;
}
