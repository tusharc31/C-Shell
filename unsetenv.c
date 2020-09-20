#include "headers.h"
#include "global.h"
int unsetenvx(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	unsetenv(argv[1]);
	return 0;
}
