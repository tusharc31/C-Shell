#include "headers.h"
#include "global.h"
int startswith(char *a, char *b)
{
	if(strlen(a)<strlen(b))
		return 0;
	for(int i=0;i<(int)strlen(b);i++)
		if(a[i]!=b[i])
			return 0;
	return 1;
}
int pinfo(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	int pid=getppid();
	if(argc>=2)
		pid=atoi(argv[1]);
	FILE *fptr;
    char filename[100], *c;
	c=(char*)malloc(1000);
	sprintf(filename, "/proc/%d/status", pid);
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Maybe process does not exist\n");
        return 1;
    }
    // Read contents from file

	size_t *siz=(size_t*)malloc(sizeof(size_t));
    *siz=0;
	printf("pid -- %d\n", pid );
    while(getline(&c, siz, fptr)>0)
    {
        if(startswith(c, "State:"))
		{
			printf("Process Status -- %s", c+7);
		}
		if(startswith(c, "VmSize:"))
		{
			printf("memory -- %s", c+8);
		}

    }
    fclose(fptr);
	fflush(stdout);
	char *tempBuffer = (char*)malloc(1000*sizeof(char));
sprintf(tempBuffer,"/proc/%d/exe", pid);
char exe[1024];

 int ret = readlink(tempBuffer,exe,1024);
printf("Executable Path -- ");
if(ret ==-1) {
    printf("ERROR\n");
    return 0;;
}
exe[ret] = 0;
printf("%s\n",exe);
free(siz);
free(tempBuffer);
	return 0;
}
