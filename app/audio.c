#include "../config.h"
#include "../local.h"
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZ 5

char buffer[BUF_SIZ];

void share(){
  FILE* info;
  if(buffer[0]=='-'){
    buffer[0]='0';buffer[1]=0;
  }
  char ocmd[]=
    "amixer set Master %%%%"
    "|grep Mono:"
    "|awk '{print $6}{print $4}'"
    "|tr -d %[]";
  freplace('%', buffer, ocmd);info=popen(ocmd,"r");

  fgets(buffer, BUF_SIZ, info);
  if(buffer[1]=='n'){
    fgets(buffer, BUF_SIZ, info);
    char bar[]="xsetroot -name ' :$$$%'";
    freplace('$', buffer, bar);system(bar);
  }else{
    fgets(buffer, BUF_SIZ, info);
    char bar[]="xsetroot -name ' :$$$%'";
    freplace('$', buffer, bar);system(bar);
  }
}

void deltaAudio(const Arg* delta){
  char cmd[]=
    "amixer get Master"
    "|grep Mono:"
    "|awk '{print $3%%}'";
  freplace('%', delta->c, cmd);
  FILE* info=popen(cmd, "r");
  fgets(buffer, BUF_SIZ, info);pclose(info);
  share();
}

void mute(const Arg* none){
  char* cmd=
    "amixer get Master"
    "|grep Mono:"
    "|awk '{print $6}'"
    "|tr -d []";
  FILE* info=popen(cmd, "r");
  fgets(buffer, BUF_SIZ, info);
  if(buffer[1]=='f'){
    buffer[1]='n';buffer[2]='\n';
  }else{
    buffer[1]='f';buffer[2]='f';buffer[3]='\n';
  }share();
}
