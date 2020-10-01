#include "headers.h"
#include "global.h"
int bg(int argc, char** argv)
{
	struct bgprocess* curr=root;
	if(argc<2)
	{
		printf("Error: Less number of arguments\n");
		exit(1);
	}
	int cr=atoi(argv[1]);
	if(cr<=0)
	{
		printf("Error in job id.\n");
		exit(1);
	}
	int cnt=0;
	while(cnt!=cr && curr->next!=NULL)
	{
		curr=curr->next;
		cnt++;
	}
	if(cnt!=cr)
	{
		printf("Job id out of range\n");
		exit(1);
	}
	if(curr->st!=0 && kill(curr->pid, 18)<0)
	{
		printf("Error while killing\n");
		exit(1);
	}
	return 0;
}
