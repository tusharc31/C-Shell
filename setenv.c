#include "headers.h"
#include "global.h"
int setenvx(int argc, char** argv)
{
	if(argc!=3 || argc!=2)
	{
		printf("Invalid number of arguments");
		exit(1);
	}
	setenv(argv[1],argv[2]==NULL?"":argv[2], 1);
	return 0;
}
