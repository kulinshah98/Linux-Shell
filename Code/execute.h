#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

extern int total;
extern char *command[];
extern int pid_job[10005],glob_it;
extern char name_job[10005][100];

extern int (*execute[])(char **);

int execute_cd(char **tokens);

int execute_help(char **tokens);

int execute_quit(char **tokens);

int execute_jobs(char **tokens);

int execute_pwd(char **tokens);

int execute_echo(char **tokens);

int execut(char **tokens);

int executebackground(char **tokens);

int executecommand(char **tokens);
