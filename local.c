#include "local.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFER_LEN 128

int check(char* key, char* string){
  int i=0,j=0;while(string[i])
    if(string[i+j]==key[j])
      if(key[j+1])j++;
      else return i+j+1;
    else {i=i+j+1;j=0;}
  return i;
}

char* getDev(char* key){
  char* path="/proc/bus/input/devices";
  FILE* inputer=NULL;char buffer[BUFER_LEN];
  inputer=fopen(path, "r");
  do{
    do{fgets(buffer, BUFER_LEN, inputer);}
    while(buffer[0]!='N');
  }while(buffer[check(key, buffer)]=='\0');
  do{fgets(buffer, BUFER_LEN, inputer);}
  while(buffer[0]!='H');
  int j=check("event", buffer),i=j-5;
  while(buffer[j]!=' ')j++;j++;
  char* ans=malloc(sizeof(char)*(j-i+1));
  for(j=0;buffer[i+j]!=' ';j++)
    ans[j]=buffer[i+j];
  ans[j]='\0';return ans;
}

int replace(char key, char *num, char *target){
  int i=0,j=0;while(target[i]!=key)i++;
  while('0'<=num[j]&&num[j]<='9')
  {target[i+j]=num[j];j++;}
  return i+j+1;
}

void freplace(char key, char *num, char *target){
  int i=0,j=0;
  while(target[i]!=key)i++;
  while(target[i]==key)i++;
  while('0'<=num[j]&&num[j]<='9')j++;
  for(i--,j--;j>=0;i--,j--)
    target[i]=num[j];
  while(target[i]==key){
    target[i]=' ';i--;
  }
}
