#include "headers.h"
#include "global.h"
int overkill(int argc, char** argv)
{
	struct bgprocess* curr=root;
	int cnt=0;
	while(curr!=NULL)
	{
		if(cnt!=0)
		{
			kill(curr->pid, SIGKILL);
		}
		curr=curr->next;
		cnt++;
	}
	root->next=NULL;
	return 0;
}
