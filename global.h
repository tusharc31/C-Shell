#ifndef GLOBAL_VARS
#define GLOBAL_VARS
char* HOME_DIR;
char* CURR_DIR;
char *pname[40000];
long long int LATEST_EXIT_STATUS;
int pro_stack[40000];
char fgprocessname[4096];
int stack_ind;
int fgprocess;
int SHELL_ID;
struct bgprocess
{
	int pid, st;
	struct bgprocess *next, *prev;
};
struct bgprocess *root;
void init();
#endif
