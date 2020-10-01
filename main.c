#include "prompt.h"
#include "headers.h"
#include "global.h"
static void handle_sigint(int sig);
int run()
{   
	while (1)
	{
		/*
		struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, 0);
*/
		print_dead_bg();
        prompt();
        // TAKE INPUT HERE
		get_user_command();
    }
}

static void handle_sigint(int sig) 
{
	if(getpid() !=SHELL_ID)
		exit(0);
	if(fgprocess!=-1)
	{
		kill(fgprocess, SIGINT);
		fgprocess=-1;
	}
	printf("\n:'(");
	run();
}
static void handle_sigstop(int sig) 
{
	if(fgprocess!=-1)
	{
		kill(fgprocess, SIGSTOP);
		printf("%d", setpgid(fgprocess, 0));
	add_bg(fgprocess, fgprocessname);
	fgprocess=-1;
	}
	printf("\n:'(");
	run();
}



int main()
{
	init();
	SHELL_ID = getpid();
	struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, 0);
	struct sigaction sb = {0};
    sb.sa_handler = handle_sigstop;
    sb.sa_flags = SA_NODEFER;
    sigemptyset(&sb.sa_mask);
    sigaction(SIGTSTP, &sb, 0);

	gethomedir();
	run();
}
