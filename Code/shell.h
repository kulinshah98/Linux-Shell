#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

extern int pid_job[10005],glob_it;
extern char name_job[10005][100];
char home[1005],curline[1005];

char **splitline_semicolon(char *line);

void printshellprompt();

void readaline();

char **split_line(char *line);

char **splitline_semicolon(char *line);

int executebackground(char **tokens);

int executecommand(char **tokens);

void implementpipe(char *p);
