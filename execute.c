#include "execute.h"

int execute_cd(char **tokens)
{
  int tmp;
  if(tokens[1]==NULL)
  {
    fprintf(stderr, "Give correct command\nGive directory name\n");
    //perror("Give correct command\nGive directory name\n");
  }
  else
  {
    tmp=chdir(tokens[1]);
    if(tmp!=0)
    {
      fprintf(stderr, "Error in chdir\n");
      //perror("Error in chdir\n");
    }
  }
  return 1;
}

int execute_help(char **tokens)
{
  fprintf(stderr, "Type the correct command and see the output\n");
  //perror("Type the correct command and see the output\n");
  return 1;
}

int execute_quit(char **tokens)
{
  return 0;
}

int execute_jobs(char **tokens)
{
  int i;
  printf("%d\n",glob_it);
  for(i=0;i<glob_it;i++)
  {
    printf("[ %d ] ", i+1);
    printf("%s", name_job[i]);
    fprintf(stdout, " [ %d ]\n",pid_job[i]);
  }
  return 1;
}

int execute_pwd(char **tokens)
{
  //printf("88\n");
    char *t;
    char c[1005];
    t=getcwd(c,520);
    if(t!=NULL)
    {
      printf("%s\n",c);
    }
    return 1;
}

int execute_echo(char **tokens)
{
  //printf("%s\n",curline);
  int i=1;
  while(tokens[i]!=NULL)
  {
    printf("%s ",tokens[i]);
    i++;
  }
  printf("\n");
  return 1;
}

int (*execute[])(char **)={&execute_help,&execute_cd,&execute_quit,&execute_pwd,&execute_echo,&execute_jobs};

int execut(char **tokens)
{
  int i,pos;
  if(tokens[0]==NULL)
  {
    return 1;
  }
  else
  {
    pos=0;
//    printf("%d\n",total);
    for(i=0;i<total;i++)
    {
      //printf("%d %d\n",i,strcmp(command[i],tokens[0]));
    //  printf("%s %s \n",command[i],tokens[0]);
      if(strcmp(command[i],tokens[0])==0)
      {
    //    printf("88\n");
        return (*execute[i])(tokens);
      }
    }
  }
  return -1;
}


int executebackground(char **tokens)
{
  //printf("background\n");
  int pos,i,flag,pid,status;
  pid_t processid;
  flag=execut(tokens);
  if(flag!=-1)
  {
    return flag;
  }
  processid=fork();
  //pid=getpid();
//  printf("***\n\n");
  if(processid<0)
  {
    fprintf(stderr, "Error in fork process");
    //perror("Error in fork process");
  }
  if(processid==0)
  {
    //printf("%s\n",tokens[0]);
    //printf("**%s\n",tokens[1]);
    pid=getpid();
    pid_job[glob_it]=pid;
  //  name_job[glob_it]=tokens[0];
    //name_job[glob_it]=tokens[0];
    glob_it++;
    //printf("%d %d %s %s %s\n",glob_it,pid_job[glob_it-1],name_job[glob_it-1],tokens[0],tokens[1]);
    //tokens[1]=NULL;
    flag=execvp(tokens[0],tokens);
  //  printf("%d ---- %d\n",glob_it,flag);
    if(flag==-1)
    {
      fprintf(stderr, "Error in execvp process\n");
  //    perror("Error in execvp process\n");
    }
  }
  wait(&status);
  pid_job[glob_it]=getpid();
  for(i=0;i<strlen(tokens[0]);i++)
  {
    name_job[glob_it][i]=tokens[0][i];
  }
  //name_job[glob_it]=tokens[0];
  glob_it++;
//  printf("****%d %d ---- %d %s %s\n",glob_it,pid,pid_job[glob_it-1],name_job[glob_it-1],tokens[0]);
  return 1;
}


int executecommand(char **tokens)
{

  int status,pos,i,flag;
  pid_t processid;
  flag=execut(tokens);
  if(flag!=-1)
  {
    return flag;
  }
  processid=fork();
//  printf("***\n\n");
  if(processid<0)
  {
    fprintf(stderr, "Error in fork process");
    //perror("Error in fork process");
  }
  if(processid==0)
  {
    //printf("%s\n",tokens[0]);
    //printf("**%s\n",tokens[1]);
    flag=execvp(tokens[0],tokens);
    if(flag==-1)
    {
      fprintf(stderr, "Error in execvp process\n");
    //  perror("Error in execvp process\n");
    }
  }
  return 1;
}
