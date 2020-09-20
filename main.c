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
	if(fgprocess!=-1)
	{
		kill(fgprocess, 9);
	}
	printf("\n");
	run();
}

int main()
{
	init();
	struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, 0);
	gethomedir();
	run();
}
