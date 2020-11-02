#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void checkalloc(void *ptr){
  if (ptr==NULL){
    perror("bad alloc");
    exit(EXIT_FAILURE);
  }
}
char ** resize(char **sa, int cursz, int newsz)
{
  printf("realloc[%d]->[%d]: ",cursz,newsz);
  char **tmp = malloc(newsz*sizeof (char *));
  if (tmp == NULL){
    perror("realloc fail");
    //free(sa);
    exit(EXIT_FAILURE);
  }
  //printf("line [%d]\n",19);
  // cp sa elems to tmp
  for(int i=0;i< cursz;++i){
    tmp[i] = sa[i];
//    strcpy(tmp[i],(*sa)[i]);
    printf("copying %s\n",tmp[i]);
  }
  //printf("line [%d]\n",24);
  //free(sa);
  //printf("line [%d]\n",26);
  return tmp;
}

int main(int argc, char** argv){


  int sz=2;
  char buf[101];
  char *str;
  int cnt=0;
  char **sa = malloc(sz*sizeof (char*));
  checkalloc(sa);
  char *sp;
  char *next=NULL;
  const char delims[] = "., !\n";

  while(fgets(buf,100,stdin) != NULL){
    int len = strlen(buf);
    for(sp=buf; *sp!= '\0';++sp){
      if(*sp=='\n'){
        *sp=' ';
      }
    }
    next=NULL;
    char *token=strtok_r(buf,delims,&next);
    while(token != NULL){
      int tlen = strlen(token);
      printf("strlen=%d\n",tlen);
      sp=malloc((strlen(token)+1));
      //checkalloc(sp);
      strcpy(sp,token);
      sa[cnt++]=sp;
      if(cnt>sz){
        sz*=2;
//        resize(&sa,cnt-1,sz);
//        printf("realloc[%d]\n",sz);
        sa = resize(sa,cnt-1,sz);
//        sa = realloc(NULL,10);
      }
      printf("[%s]\n",token);
      token =strtok_r(NULL,delims,&next);
    }
  }
  for(int i=0;i< cnt;++i){
      printf("%p,[%d]:[%s]\n",sa[i],i,sa[i]);
      free(sa[i]); sa[i]=NULL;

  }
  free(sa); sa=NULL;
}
