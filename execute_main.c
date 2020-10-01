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
#include "bg.h"
#include "fg.h"
#include "setenv.h"
#include "unsetenv.h"
#include "overkill.h"
int exec_main(char *name, char ** argv)
{
	int argc=0;
	while(argv[argc]!=NULL)
		argc++;
	if(strcmp(name, "setenv")==0)
	{
		return setenvx(argc, argv);
	}
	if(strcmp(name, "unsetenv")==0)
	{
		return unsetenvx(argc, argv);
	}
	if(strcmp(name, "overkill")==0)
	{
		return overkill(argc, argv);
		return 0;
	}
	if(strcmp(name, "kjob") == 0)
	{
		return kjob(argc, argv);
		printf("YOX");
		return 0;
	}
	if(strcmp(name, "fg") == 0)
	{
	    return fg(argc, argv);
		return 0;
	}

	if(strcmp(name, "bg") == 0)
	{
		return bg(argc, argv);
		return 0;
	}

	if(strcmp(name, "nightswatch")==0)
	{
		return nightswatch(argc,argv);
		return 0;
	}
	if(strcmp(name, "history")==0)
	{
		return history(argc,argv);
		return 0;
	}
	if(strcmp(name, "ls")==0)
	{
		return ls(argc,argv);
		return 0;
	}
	if(strcmp(name, "pinfo")==0)
	{
		return pinfo(argc,argv);
		return 0;
	}
	if(strcmp(name, "cd")==0)
	{
		return cd(argc,argv);
		return 0;
	}
	if(strcmp(name, "echo")==0)
	{
		return echo(argc,argv);
		return 0;
	}	
	if(strcmp(name, "pwd")==0)
	{
		return pwd(argc,argv);
		return 0;
	}
	if(strcmp(name, "jobs")==0)
	{
		return jobs(argc, argv);
		return 0;
	}
	if(execvp(name,argv)<0)
	{perror("Exec failed"); return 1;}
	return 0;
}
