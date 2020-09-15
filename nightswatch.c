#include "headers.h"
#include "global.h"
int dead()
{
	fd_set readfds;
    FD_ZERO(&readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    char message[50];
        FD_SET(STDIN_FILENO, &readfds);

        if (select(1, &readfds, NULL, NULL, &timeout))
        {
            scanf("%s", message);
			for(int i=0;i<(int)strlen(message);i++)
				if(message[i]=='q')
					exit(0);
        }
		return 0;
}
int get_newborn()
{
    FILE *fptr;
    char filename[100], *c, prev[100];
	sprintf(filename, "/proc/loadavg");
    fptr = fopen(filename, "r");
    // Read contents from file
	size_t len=0;
    getline(&c, &len,fptr);
	char delim[10];
	sprintf(delim,"\n ");
		char *token=strtok(c, delim);
		while(token!=NULL)
		{
			strcpy(prev, token);
			token = strtok(NULL, delim);
		}
	printf("%s\n", prev);
	free(c);
    fclose(fptr);
	return 0;
}
int newborn(double n)
{
while(1)
{
	get_newborn();
clock_t difference= 0; /* 10ms */
	double time_taken=0;
clock_t before = clock();
do {
	dead();
    difference = (clock() - before);
	time_taken = ((double)difference)/CLOCKS_PER_SEC;
} 
while ( time_taken < n );

}
}
int get_inter(int op)
{
    FILE *fptr;
    char filename[100], *c;
	sprintf(filename, "/proc/interrupts");
    fptr = fopen(filename, "r");
    // Read contents from file
	size_t len=0;
    getline(&c, &len,fptr);
	if(op==1)
	{
		printf("%s\n", c);
		free(c);
		fclose(fptr);
		return 0;
	}
	len=0;
    getline(&c, &len,fptr);
	len=0;
    getline(&c, &len,fptr);
	len=0;
	printf("%s\n", c);
	free(c);
    fclose(fptr);
	return 0;
}
int inter(double n)
{
get_inter(1);
while(1)
{
	get_inter(0);
	clock_t difference= 0; /* 10ms */
	double time_taken=0;
clock_t before = clock();
do {
	dead();
    difference = (clock() - before);
	time_taken = ((double)difference)/CLOCKS_PER_SEC;
} 
while ( time_taken < n );
}
}
int nightswatch(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	double n=1;
	for(int i=0;i<argc-1;i++)
	{
		if(strcmp(argv[i], "-n")==0)
		{
			n=atof(argv[i+1]);
			break;
		}
	}
	for(int i=0;i<argc;i++)
	{
		if(strcmp(argv[i],"interrupt")==0)
		{
			inter(n);
			return 0;
		}
	}
	newborn(n);
	return 0;
}




