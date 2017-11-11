#include "shellprompt.h"

char curdir[1005],curline[1005],home[1005],curline2[1005];
char *command[]={"help","cd","quit","pwd","echo","jobs"};
int total=6,sztokens;


void printshellprompt()
{
  FILE * fp;
  char name[1005],systm[1005];
  char * tmp1;
  int tmp,i,flag;
  tmp=getlogin_r(name,100);
  fp=popen("lsb_release -ds","r");
  fgets(systm,50,fp);
  tmp1=strtok(systm,"\n");
  pclose(fp);
  if(tmp==0)
  {
    printf(" [%s@",name);
  }
  if(tmp1!=NULL)
  {
    for(i=1;i<=6;i++)
    {
      printf("%c",tmp1[i]);
    }
  }
  printf(": ");
  char *t=getcwd(curdir,512);
  flag=1;
  for(i=0;i<strlen(home);i++)
  {
    if(curdir[i]!=home[i])
    {
      flag=0;
      break;
    }
    if(curdir[i]=='\0')
    {
      flag=0;
      break;
    }
  }
  //printf("**%d %d**",strlen(home),strlen(curdir));
  if(flag==1)
  {
    curdir[0]='~';
    curdir[1]='/';
    for(i=strlen(home);i<strlen(curdir);i++)
    {
      curdir[i-strlen(home)+1]=curdir[i];
    }
    curdir[i]='\0';
//    printf("%d",i);
    for(i=i;i<=strlen(curdir);i++)
    {
      curdir[i-strlen(home)+1]='\0';
    }
  }
  for(i=0;i<strlen(curdir);i++)
  {
    printf("%c",curdir[i]);
  }
  printf("] ");
}
