#include "prompt.h"
#include "headers.h"
#include "global.h"
#include "execute_main.h"
int gethomedir()
{     
	HOME_DIR = (char*)malloc(sizeof(char)*PATH_MAX);
	CURR_DIR = (char*)malloc(sizeof(char)*PATH_MAX);
	if (getcwd(HOME_DIR, PATH_MAX) == NULL) 
	{
		perror("Unable to get Home directory");
		exit(1);
	}
	return 0;
}
int prompt() {
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) 
	{
		perror("Unable to access current directory");
		return -1;
	}
	if(gethostname(hostname, HOST_NAME_MAX)==-1)
	{
		perror("Error getting system name");
		return -1;
	}
	if(getlogin_r(username, LOGIN_NAME_MAX))
	{
		perror("Error getting username");
		return -1;
	}
	strcpy(CURR_DIR, cwd);
	if(strcmp(cwd, HOME_DIR) == 0)
	{cwd[0] = '~';cwd[1]='\0';}
	else
	{
		int ind=0;
		for(ind=0;ind<(int)strlen(HOME_DIR);ind++)
			if(ind>=(int)strlen(cwd) || cwd[ind]!=HOME_DIR[ind])
				break;
		if(ind==(int)strlen(HOME_DIR))
			sprintf(cwd, "~%s", cwd+ind);
	}
	printf("<%s@%s:%s>", username, hostname, cwd);
	return 0;
}
int parse(char* command, char** args, int* background, char* inp, char* out, int *ap)
{
	char *token;
	char delim[50]=" \n";
	token = strtok(command, delim);
	int ind=0;
	while(token!=NULL)
	{
		if(token[0]!='<' && token[0]!='>')
		{
		args[ind]=token;
		ind++;
		}
		else if(token[0]=='<')
		{
			//inp=(char*)malloc(1024);
			if(strlen(token)>1)
			{
				strcpy(inp, token+1);
			}
			else
			{
				token=strtok(NULL,delim);
				if(token==NULL)
				{
					printf("Error in <\n");
					return 1;
				}
				strcpy(inp, token);
			}
		}
		else if(token[0]=='>')
		{
			int len=2;
			if(strlen(token)>1 && token[1]=='>')
			{
				*ap=1;
				len=2;
			}
			if((int)strlen(token)>len)
			{
				strcpy(out, token+len);
			}
			else
			{
				token=strtok(NULL,delim);
				if(token==NULL)
				{
					printf("Error in >\n");
					return 1;
				}
				strcpy(out, token);
			}
		}

		token = strtok(NULL, delim);
	}
	if(ind>0 && strcmp(args[ind-1],"&")==0)
	{
		*background=1;
		ind--;
	}
	args[ind]=0;
	return 0;
}
int parse_pipeline(char* command, char** commands, int* com)
{
	char *token;
	char delim[50]="|";
	token = strtok(command, delim);
	int ind=0;
	while(token!=NULL)
	{
		commands[ind]=token;
		ind++;
		token = strtok(NULL, delim);
	}
	commands[ind]=0;
	*com=ind;
	return 0;
}
void delete_bg(int pid, int status)
{
		struct bgprocess* curr = root;
		while(curr->pid!=pid && curr->next!=NULL)
		{
			curr=curr->next;
		}
		if(curr->pid!=pid)
			return;
		if(WIFSTOPPED(status)==1)
		{
			curr->st=1;
			return;
		}
		else if(WIFCONTINUED(status)==1)
		{
			curr->st=0;
			return;
		}
		free(pname[pid]);
		if(WIFEXITED(status)==1)
			printf("process %s with pid %d exited normally\n",pname[pid],pid);
		else
			printf("process %s with pid %d exited abnormally\n",pname[pid],pid);

		curr->prev->next=curr->next;
		if(curr->next!=NULL && curr->next->prev!=NULL)
		curr->next->prev=curr->prev;
		free(curr);
}
void add_bg(int pid, char* pnamex)
{
		struct bgprocess* curr = root;
		pname[pid]=(char*)malloc(sizeof(char)*(strlen(pnamex)+1));
		while(curr->next!=NULL)
		{
			curr=curr->next;
		}
		struct bgprocess* newbg=(struct bgprocess*)malloc(sizeof(struct bgprocess));
		strcpy(pname[pid], pnamex);
		newbg->next=NULL;
		newbg->pid=pid;
		newbg->st=0;
		curr->next=newbg;
		newbg->prev=curr;
}


void print_dead_bg()
{
	pid_t pid=-1;
	int status;
	while((pid = waitpid(pid,&status, WNOHANG | WUNTRACED | WCONTINUED))>0)
	{
		delete_bg(pid, status);
	}
}
int  execute(char **argv, int background, char *inp,char *out, int ap, int in, int outt)
{
	pid_t  pid;
	int status;
	pid = fork();
	if (pid < 0)
	{
		perror("*** ERROR: forking child process failed");
		return -1;
	}
	else if (pid == 0)
	{
		if(background!=0)
		{
			setpgid(0, 0);
			//int i=0;
			//for (i=getdtablesize();i>=0;--i) close(i);
			//i=open("/dev/null",O_RDWR); /* open stdin */
			//dup(i); /* stdout */
			//dup(i); /* stderr */
		}
		if(strlen(inp)>0)
		{
			int filefd=open(inp, O_RDONLY);
			if(filefd==-1)
			{
				printf("Error opening input file. Maybe it does not exist");
				exit(0);
			}
			close(0);
			dup(filefd);
		}
		else if(in!=0)
		{
			dup2(in,0);
		}
		if(strlen(out)>0)
		{
			int filefd=0;
			if(!ap)
			filefd = open(out, O_WRONLY|O_CREAT, 0644);
			else
			filefd=open(out, O_APPEND | O_CREAT, 0644);
			close(1);//Close stdout
			dup(filefd);
		}
		else if(outt!=1)
			dup2(outt,1);
		exec_main(*argv, argv);
		exit(0);
	}
	else
	{

		if(background==0)
		{
			fgprocess = pid;
			pid_t x;
			while ((x=wait(&status)) != pid)
			{
				if(x>0)
				{
					delete_bg(x, status);
				}
			}
			fgprocess=-1;
		}
		else
		{
			printf("process started with process id %d\n", pid);
			add_bg(pid, *argv);
			return 0;
		}
	}
	return 0;
}
void add_history(char* command)
{
	FILE *stream;
	char filename[100];
	char command_list[1024*21]="";
	char *c;
	int cnt=0;
	cnt++;
	size_t *siz=(size_t*)(malloc(sizeof(size_t)));
	*siz=0;
	strcat(command_list, command);
	if(strlen(command)<=0 || command[strlen(command)-1]!='\n')
	{
		strcat(command_list,"\n");
	}
	sprintf(filename, "%s/hist_file", HOME_DIR);
	stream =fopen(filename, "r");
	while(getline(&c, siz, stream)>0 && cnt<20)
	{
		*siz=0;
		strcat(command_list, c);
		cnt++;
	}
	fclose(stream);
	stream = fopen(filename, "w");
	fputs(command_list, stream);
	fclose(stream);
}
int get_user_command()
{
	char* command;
	command = (char*)malloc(sizeof(char)*1024);
	size_t  sz=0;
	int x=getline(&command, &sz, stdin);
	if(x==-1)
		exit(0);
	if(strlen(command)==0)
		return 0;
	int background=0;
	add_history(command);
	int com=0;
	char* commands[64];
	parse_pipeline(command,commands, &com);
	int pipefd[2];
	int in = 0;
	int outt=0;
	for(int i=0;i<com;i++)
	{

		char part_command[1024];
		//part_command=(char*)malloc(1024);
		strcpy(part_command, commands[i]);
		char *inp=NULL;
		char* out=NULL;
		out=(char*)malloc(1024);
		inp=(char*)malloc(1024);
		out[0]='\0';
		inp[0]='\0';
		if(i!=com-1)
		{
			pipe(pipefd);
			outt=pipefd[1];
		}
		else
		{
			outt=1;
		}
		int ap=0;
		char *args[64];
		if(parse(part_command, args, &background, inp, out,&ap))
			return 0;
		if(*args==NULL)
			return 0;
		if(strcmp(*args, "exit")==0)
			exit(0);
		if(strcmp(*args, "cd")==0)
			exec_main(*args, args);
		else
		{
			execute(args, background, inp, out, ap, in, outt);
		}
		if(i!=com-1)
		close(pipefd[1]);
		if(in!=0)
			close(in);
		in=pipefd[0];
		free(out);
		free(inp);
	}
	free(command);
	return 0;
}
