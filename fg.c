#include "headers.h"
#include "global.h"
int fg(int argc, char** argv)
{
	struct bgprocess* curr=root;
	if(argc<2)
	{
		printf("Error: Less number of arguments\n");
		return 1;
	}
	int cr=atoi(argv[1]);
	if(cr<=0)
	{
		printf("Error in job id.\n");
		return 1;
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
		return 1;
	}
	curr->prev->next=curr->next;
	if(curr->next!=NULL)
	curr->next->prev=curr->prev;
    tcsetpgrp(2, getpgid(curr->pid));
    setpgid (0, getpgid(curr->pid));
    if(kill(curr->pid, SIGCONT)<0)
	{
		printf("Error while killing\n");
		return 1;
	}
	while(waitpid(curr->pid, NULL, 0)!=curr->pid)
	{}
	//tcsetpgrp(2, getpgid(0));
	//getpgid(curr->pid, getpgid(getpid()));
	free(curr);
	return 0;
}
