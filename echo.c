#include "headers.h"
#include "global.h"
int echo(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		exit(1);
	}
    for(int i=1;i<argc;i++)
	{
		if(i!=1)
			printf(" ");
		printf("%s", argv[i]);
	}
	printf("\n");
	return 0;
}
