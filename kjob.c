#include "headers.h"
#include "global.h"
int kjob(int argc, char** argv)
{
	struct bgprocess* curr=root;
	if(argc<3)
	{
		printf("Error: Less number of arguments\n");
		exit(1);
	}
	int cr=atoi(argv[1]);
	int sig=atoi(argv[2]);
	if(cr<=0 || sig<0)
	{
		printf("Error in job id or signal no.\n");
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
	if(kill(curr->pid, sig)<0)
	{
		printf("Error while killing\n");
		exit(1);
	}
	return 0;
}
