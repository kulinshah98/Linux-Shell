#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

extern int sztokens,total;
extern char *command[];
extern char curdir[1005],curline[1005],home[1005],curline2[1005];

void printshellprompt();
