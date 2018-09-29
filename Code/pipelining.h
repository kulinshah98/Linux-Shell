#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void implementpipe(char *p);

char **split_pipe(char *line);

char **split_line(char *line);
