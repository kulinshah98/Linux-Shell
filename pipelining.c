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
//  printf("pipe\n");
  int i=0,debug,pipefd[1005],n,j,in,out,status;
  char *line;
  char **tokens;
  char **tokens_space;
  tokens=split_pipe(p);
  line=tokens[0];
  do {
  //  printf("%s\n",line);
    i++;
    line=tokens[i];
    //i++;
  } while(line!=NULL);
  n=i;
  //printf("%d\n",n);
  debug=0;
  for(i=0;i<n;i++)
  {
    pipe(pipefd+2*i);
    tokens_space=split_line(tokens[i]);
    line=tokens_space[0];
  //  printf("%s\n",line);
    j=0;
    if(fork()==0)
    {
      debug++;
      do {
      //  printf("**%s %d\n",line,j);
        j++;
        line=tokens_space[j];
        if(line!=NULL)
        {
          if(line[0]=='<')
          {
    //        printf("**<*\n");
            tokens_space[j]=tokens_space[j+1];
            //tokens_space[j]=NULL;
          //  printf("%s\n",tokens_space[j]);
            in = open(tokens_space[j],O_RDONLY);
            dup2(in,0);
            tokens_space[j]=NULL;
          }
          if(line[0]=='>')
          {
          //  printf("*>**\n");
            tokens_space[j]=tokens_space[j+1];
          //  printf("%s\n",tokens_space[j]);
            out = open(tokens_space[j],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup2(out,1);
            tokens_space[j]=NULL;
          }
        }
      //  printf("%d\n",j);
      } while(line!=NULL);
  //    printf("***%d\n\n",debug);
    //  printf("%s %s %d\n",tokens_space[0],tokens_space[1],i);
      if(i!=0)
      {
        //printf("%d\n",i);
        dup2(pipefd[2*i-2],0);
        //close(pipefd[2*i-2]);
        //close(pipefd[2*i-1]);
      }
      //printf("**$%d\n",i);
      if(i+1!=n)
      {
//        printf("*%d*\n",i);
        dup2(pipefd[2*i+1],1);
      //  close(pipefd[2*i]);
      //  close(pipefd[2*i+1]);
      }
      for(j=0;j<n;j++)
      {
        close(pipefd[2*j]);
        close(pipefd[2*j+1]);
      }
      //printf("*********%s %s %s\n",tokens_space[0],tokens_space[1],tokens_space[2]);
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
  //printf("***\n");
}
