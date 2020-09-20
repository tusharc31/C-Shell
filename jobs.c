#include "headers.h"
#include "global.h"
char* rem(int x)
{
	if(x==1)
		return "STOPPED";
	else
		return "RUNNING ";
}
int jobs(int argc, char** argv)
{
	struct bgprocess* curr=root;
	int cnt=0;
	while(curr!=NULL)
	{
		if(cnt!=0)
		{
			printf("%d. %s [%d] %s\n", cnt, rem(curr->st), curr->pid, pname[curr->pid]);
		}
		curr=curr->next;
		cnt++;
	}
	return 0;
}
