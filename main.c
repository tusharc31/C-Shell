#include "prompt.h"
#include "headers.h"

int run()
{   

	while (1)
    {
		print_dead_bg();
        prompt();
        // TAKE INPUT HERE
		get_user_command();
    }
}
int main()
{
	gethomedir();
	run();
}
