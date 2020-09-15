#include "headers.h"
#include "global.h"
int pwd(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	printf("%s", CURR_DIR);
	printf("\n");
	return 0;
}
