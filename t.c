#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmpstringp(const void *p1, const void *p2){
  return strcmp(* (char * const *) p1, * (char * const *) p2);
}
void checkalloc(void *ptr){
  if (ptr==NULL){
    perror("bad alloc");
    exit(EXIT_FAILURE);
  }
}
char ** resize(char **sa, int cursz, int newsz){
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
void rm_newlines(char * buf){
  char * sp;
  for(sp=buf; *sp!= '\0';++sp){
    if(*sp=='\n'){
      *sp=' ';
    }
  }
}
void  print_strings(char **sa,int cnt){
  for(int i=0;i< cnt;++i){
      //printf("sa=[%p], &sa[%d]=[%p], sa[%d]=[%p],[%s]\n",sa,i,&sa[i],i,sa[i],sa[i]);
      //printf("&sa[%d]=[%p], sa[%d]=[%p],[%s]\n",i,&sa[i],i,sa[i],sa[i]);
      //printf("[%2d]=[%s]\n",i,sa[i]);
      printf("%s\n",sa[i]);
  }
}
void  free_strings(char **sa,int cnt){
  for(int i=0;i< cnt;++i){
      free(sa[i]); sa[i]=NULL;
  }
  free(sa); sa=NULL;
}

int main(int argc, char** argv){

  int sz=256;
  //int sz=2;
  char buf[101];
  int cnt=0;
  char **sa = malloc(sz*sizeof (char*));
  checkalloc(sa);
  char *sp;
  char *next=NULL;
  const char delims[] = "., !\n";

  // put a line into the buffer
  while(fgets(buf,100,stdin) != NULL){

    // replace newlines with space
    rm_newlines(buf);

    next=NULL;
    char *token=strtok_r(buf,delims,&next);
    while(token != NULL){
      sp=malloc((strlen(token)+1));
      checkalloc(sp);
      strcpy(sp,token);
      sa[cnt++]=sp;
      if(cnt>sz){
        sz*=2;
        //printf("realloc[%d]\n",sz);
        char ** tmp = realloc(sa, sz* sizeof (char *));
        checkalloc(tmp);
        sa = tmp;
      }
      //printf("[%2d / %2d] = [%s] \n",cnt,sz,sa[cnt-1]);
      token =strtok_r(NULL,delims,&next);
    }
  }

  // sort the string array
  qsort(sa, cnt, sizeof(char *), cmpstringp);

  print_strings(sa,cnt);
  free_strings(sa,cnt);
}
