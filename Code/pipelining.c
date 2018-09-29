#include "pipelining.h"


char **split_pipe(char *line)
{
  char *p;
  int pos,sz=1005;
  char **semicolon=malloc(1005*sizeof(char *));
  p=strtok(line,"|");
  pos=0;
  while(p!=NULL)
  {
    semicolon[pos++]=p;
    p=strtok(NULL,"|");
    if(pos>=sz)
    {
      sz+=sz;
      semicolon=realloc(semicolon,sz*sizeof(char *));
    }
  }
  semicolon[pos]='\0';
  return semicolon;
}

void implementpipe(char *p)
{
  int i=0,debug,pipefd[1005],n,j,in,out,status;
  char *line;
  char **tokens;
  char **tokens_space;
  tokens=split_pipe(p);
  line=tokens[0];
  do {
    i++;
    line=tokens[i];
  } while(line!=NULL);
  n=i;
  debug=0;
  for(i=0;i<n;i++)
  {
    pipe(pipefd+2*i);
    tokens_space=split_line(tokens[i]);
    line=tokens_space[0];
    j=0;
    if(fork()==0)
    {
      debug++;
      do {
        j++;
        line=tokens_space[j];
        if(line!=NULL)
        {
          if(line[0]=='<')
          {
            tokens_space[j]=tokens_space[j+1];
            in = open(tokens_space[j],O_RDONLY);
            dup2(in,0);
            tokens_space[j]=NULL;
          }
          if(line[0]=='>')
          {
            tokens_space[j]=tokens_space[j+1];
            out = open(tokens_space[j],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup2(out,1);
            tokens_space[j]=NULL;
          }
        }
      } while(line!=NULL);

      if(i!=0)
      {
        dup2(pipefd[2*i-2],0);
      }
      if(i+1!=n)
      {
        dup2(pipefd[2*i+1],1);
      }

      for(j=0;j<n;j++)
      {
        close(pipefd[2*j]);
        close(pipefd[2*j+1]);
      }

      execvp(tokens_space[0],tokens_space);
    }
  }
  for(i=0;i<n;i++)
  {
    close(pipefd[2*i]);
    close(pipefd[2*i+1]);
  }
  for(i=0;i<n;i++)
  {
    wait(&status);
    wait(&status);
  }
}
