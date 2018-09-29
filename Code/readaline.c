#include "readaline.h"

void readaline()
{
  int size=500;
  int cur=0;
  int flag=1;
  char tmp;
  while(flag==1)
  {
    tmp=getchar();
    if(tmp=='\n' || tmp==EOF)
    {
      flag=0;
      curline[cur]='\0';
    }
    else
    {
      curline[cur++]=tmp;
    }
  }
}

char **split_line(char *line)
{
  int size=1005,pos=0;
  char **tokens=malloc(size*sizeof(char *));
  char *p;
  p=strtok(line," \n\t\r\a");
  while(p!=NULL)
  {
    tokens[pos++]=p;
    p=strtok(NULL," \n\t\r\a");
    if(pos>=size)
    {
      size+=size;
      tokens=realloc(tokens,size*sizeof(char *));
    }
  }
  tokens[pos]='\0';
  sztokens=pos;
  return tokens;
}
