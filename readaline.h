#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

void readaline();

char **split_line(char *line);

extern int sztokens;
extern char curline[1005];
