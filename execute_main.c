#include "headers.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "pinfo.h"
#include "nightswatch.h"
#include "history.h"
#include "jobs.h"
#include "kjob.h"
int exec_main(char *name, char ** argv)
{
	int argc=0;
	while(argv[argc]!=NULL)
		argc++;
	if(strcmp(name, "kjob") == 0)
	{
		kjob(argc, argv);
		return 0;
	}
	if(strcmp(name, "nightswatch")==0)
	{
		nightswatch(argc,argv);
		return 0;
	}
	if(strcmp(name, "history")==0)
	{
		history(argc,argv);
		return 0;
	}



	if(strcmp(name, "ls")==0)
	{
		ls(argc,argv);
		return 0;
	}
	if(strcmp(name, "pinfo")==0)
	{
		pinfo(argc,argv);
		return 0;
	}


	if(strcmp(name, "cd")==0)
	{
		cd(argc,argv);
		return 0;
	}
	if(strcmp(name, "echo")==0)
	{
		echo(argc,argv);
		return 0;
	}	
	if(strcmp(name, "pwd")==0)
	{
		pwd(argc,argv);
		return 0;
	}
	if(strcmp(name, "jobs")==0)
	{
		jobs(argc, argv);
		return 0;
	}
	pid_t pd;
	pd = fork();
	if(pd<0)
	{
		perror("Forking failed");
		return 0;
	}
	if(pd==0)
	{
	if(execvp(name,argv)<0)
	{perror("Exec failed");}
	}
	else
	{
		pid_t x=0;
		while((x=wait(NULL))!=pd)
		{
			printf("%d", x);
		}
	}
	return 0;
}
