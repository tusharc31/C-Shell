#include "headers.h"
#include "global.h"
int cd(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("Invalid number of arguments");
		return 1;
	}
		char act[4097];
		strcpy(act, argv[1]);
	if(strcmp(argv[1],"-")==0)
	{
		if(strlen(LAST_DIR)!=0)
		{
			sprintf(act, "%s", LAST_DIR);
		}
		else
			return 0;
	}
	else if(strcmp(argv[1],"~")==0)
		sprintf(act,"%s", HOME_DIR);
	else if(argv[1]!=NULL && argv[1][0]=='~')
	{
			sprintf(act,"%s%s", HOME_DIR, argv[1]+1);
    }
    if(chdir(act)<0)
	{
		perror("Error in cd");
		return 1;
	}
	strcpy(LAST_DIR, CURR_DIR);
	return 0;
}
