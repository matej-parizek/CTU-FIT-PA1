#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#endif /* __PROGTEST__ */

//is substring in string
int isIn(const char *text, const char **replace,int *start)
{
  int i=0;
  int count=0;
  while (text[i]!='\0')
  {
    if(text[i]==replace[0][0])
    {
      *start=i;
      int j=1;
      while (replace[0][j]!='\0')
      {
        if(replace[0][j]==text[i+j])
          count++;
        else
        {
          i+=j;
          count=0;
          break;
        }
        j++;
      }
      if(count==(int)strlen(replace[0])-1)
        return 1;
    }
    i++;
  }
  return 0;
}

int control(const char *(*replace)[2])
{
  int i=0;
  while (replace[i+1][0]!=NULL)
  {
    for(int j=i+1; replace[j][0]!=NULL;j++)
    {
      if(strstr(replace[j][0],replace[i][0])!=NULL || strstr(replace[i][0],replace[j][0])!=NULL)
      {
        return 1;
      }
    }
    i++;
  }
  return 0;
}

//change incorect word
char *change(const char * text, const char **word,int start,char *rep)
{
  int lenWord1=strlen(word[1]);
  int lenWord0=strlen(word[0]);
  free(rep);
  char *repText=(char*)calloc(1+strlen(text)-lenWord0+lenWord1,sizeof(char));
  int i=0;
  while (text[i]!='\0')
  {
    if(i==start)
    {
      strcat(repText,word[1]);
      break;
    }
    repText[i]=text[i];
    i++;
  }
  strcat(repText,text+i+lenWord0);
  return repText;
}
//find incorect words
char *find(const char *text,const char * (*replace)[2])
{
  int i=0; 
  int start=0;
  int len=strlen(text);
  char *repText=(char*)calloc(strlen(text)+1,sizeof(char));
  strcpy(repText,text);
  char *buffer=(char*)calloc(strlen(text)+1,sizeof(char));
  strcpy(buffer,text);
  while (replace[i][0]!=NULL)
  {
    if(isIn(text,replace[i],&start))
    {
      repText=(char *)realloc(repText,(1+(int)strlen(replace[i][0])+
      (int)strlen(replace[i][1])+len)*sizeof(char));
      buffer=(char *)realloc(buffer,(1+(int)strlen(replace[i][0])+
      (int)strlen(replace[i][1])+len)*sizeof(char));
      repText=change(buffer,replace[i],start,repText);
      strcpy(buffer,repText);
      len=strlen(repText);
    }
    i++;
  }
  free(buffer);
  return repText;
}

char * newSpeak ( const char * text, const char * (*replace)[2] )
{
  if(control(replace))
    return NULL;
  char *returnText;
  returnText=find(text,replace); 
  return  returnText;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };


  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };

  
  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
