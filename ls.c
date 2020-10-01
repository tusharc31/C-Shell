#include "headers.h"
#include "global.h"
int get_flags(char *args, int *l, int *a)
{
	for(int i=1;i<(int)strlen(args);i++)
	{
		if(args[i]=='l')
			*l=1;
		else if(args[i]=='a')
			*a=1;
	}
	return 0;
}
int skip(char* name, int a)
{
	if(a==1)
		return 0;
	if(name[0]=='.')
		return 1;
	return 0;
}
char* formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}
void plong(struct stat mystat)
{
	printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
    printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
    printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
	printf(" %s ", getpwuid(mystat.st_uid)->pw_name);
	printf("%s ", getgrgid(mystat.st_gid)->gr_name);
	printf("%lu ", mystat.st_size);
	char date[36];
	printf("%s ", formatdate(date, mystat.st_mtime));
}
int ls(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		exit(1);
	}
	char backdir[PATH_MAX], dirx[PATH_MAX];
	strcpy(backdir, CURR_DIR);
	strcpy(dirx, CURR_DIR);
	int direc=0, l=0, a=0;
	for(int i=1;i<argc;i++)
	{
		if(strlen(argv[i])<1)
			continue;
		int len=strlen(argv[i]);
		if(argv[i][0]=='-')
		{
			get_flags(argv[i],&l,&a);
			continue;
		}
		if(direc==1)
			continue;
		if(len>PATH_MAX)
		{
			perror("File name too long");
			exit(1);
		}
		direc=1;
		strcpy(dirx, argv[i]);
	}
	if(dirx[0]=='~')
	{
		if(strlen(dirx)>1)
		sprintf(dirx, "%s%s", HOME_DIR, dirx+1);
		else
			strcpy(dirx, HOME_DIR);
	}
	if(chdir(dirx)<0)
	{
		perror("Error in cd");
		exit(1);
	}
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;

    mydir = opendir(".");
    while((myfile = readdir(mydir)) != NULL)
    {
		if(skip(myfile->d_name, a))
			continue;
        stat(myfile->d_name, &mystat);
		if(l==1)
			plong(mystat);
        printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
	chdir(backdir);
	return 0;
}
