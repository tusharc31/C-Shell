#ifndef __PROMPT_H
#define __PROMPT_H

int prompt();
int gethomedir();
int get_user_command();
void print_dead_bg();
void add_bg(int pid, char* pnamex);
#endif
