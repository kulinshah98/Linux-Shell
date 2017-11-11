
#include "shell.h"


char name_job[10005][100];
int pid_job[10005];
int glob_it;

void handler_sigint(int sig_type)
{
  int flag=0;
  if(flag==0)
  {
    flag=1;
  //  printf("\n");
  //  printshellprompt();
  }
  printf("\n");
  printshellprompt();
  //printf("\n");
  signal(SIGINT,handler_sigint);
  //printf("\n");
  //printshellprompt();
}

char **splitline_semicolon(char *line)
{
  char *p;
  int pos,sz=1005;
  char **semicolon=malloc(1005*sizeof(char *));
  p=strtok(line,";");
  pos=0;
  while(p!=NULL)
  {
    semicolon[pos++]=p;
    p=strtok(NULL,";");
    if(pos>=sz)
    {
      sz+=sz;
      semicolon=realloc(semicolon,sz*sizeof(char *));
    }
  }
  semicolon[pos]='\0';
  return semicolon;
}

int main()
{
  glob_it=0;
  signal(SIGINT,handler_sigint);
  int i,k,flag,j,pipline,lencurline,sz=1005;
  char *t;
  t=getcwd(home,512);
  char **tokens;
  char **semicolon;
  char *p;
  printshellprompt();
  readaline();
  //printf("%s\n",curline);
  semicolon=splitline_semicolon(curline);
  p=semicolon[0];
  i=1;
  while(p!=NULL)
  {
    //printf("%s\n",p );
    pipline=0;
    for(k=0;k<strlen(p);k++)
    {
      if(p[k]=='|'  || p[k]=='>' || p[k]=='<')
      {
        pipline=1;
        break;
      }
    }
  //  printf("%s\n",p );
    if(pipline==0)
    {
    //  printf("%s\n",p );
      if(p[strlen(p)-1]=='&')
      {
        tokens=split_line(p);
          flag=executebackground(tokens);
      //    printf("%s 333dfas\n",name_job[glob_it-1]);
      }
      else
      {
        tokens=split_line(p);
          flag=executecommand(tokens);
      }
    }
    else
    {
      flag=1;
      implementpipe(p);
    }
    p=semicolon[i++];
  }
  while(flag)
  {
    printshellprompt();
    readaline();
    semicolon=splitline_semicolon(curline);
    p=semicolon[0];
    i=1;
    while(p!=NULL)
    {
    //  printf("%d\n",glob_it);
      pipline=0;
      for(k=0;k<strlen(p);k++)
      {
        if(p[k]=='|'  || p[k]=='>' || p[k]=='<')
        {
          pipline=1;
          break;
        }
      }
      //printf("%s\n",p );
      if(pipline==0)
      {
      //  printf("%s\n",p );
        if(p[strlen(p)-1]=='&')
        {
          tokens=split_line(p);
            flag=executebackground(tokens);
        //    printf("*$#%d\n",glob_it);
          //  printf("%s 333dfas\n",name_job[glob_it-1]);
        }
        else
        {
    //      printf("%s 333dfas\n",name_job[glob_it-1]);
          tokens=split_line(p);
            flag=executecommand(tokens);
      //      printf("%s 333dfas\n",name_job[glob_it-1]);
        }
      }
      else
      {
        implementpipe(p);
      }
        p=semicolon[i++];
    }
  }
  return 0;
}
