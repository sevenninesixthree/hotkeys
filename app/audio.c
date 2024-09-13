#include "../config.h"
#include "../local.h"
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZ 5

char buffer[BUF_SIZ];

void share(){
  FILE* info;
  if(buffer[0]=='-'){
    buffer[0]='0';buffer[1]='\n';
  }
  char ocmd[]=
    "amixer set Master %%%%"
    "|grep Mono:"
    "|awk '{print $6}{print $4}'"
    "|tr -d %[]";
  freplace('%', buffer, ocmd);info=popen(ocmd,"r");

  char bar[]="xsetroot -name ' !!!:$$$%'";
  fgets(buffer, BUF_SIZ, info);
  if(buffer[1]=='n')freplace('!', "\n", bar);
  else freplace('!', "\n", bar);

  fgets(buffer, BUF_SIZ, info);
  freplace('$', buffer, bar);
  system(bar);
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

int speaker=-1;
void toggleAudio(const Arg* none){
  if(speaker<0){
    char* cmd=
      "amixer get Speaker"
      "|grep Left:"
      "|awk '{print $7}'"
      "|tr -d []";
    FILE* info=popen(cmd, "r");
    fgets(buffer, BUF_SIZ, info);
    if(buffer[1]=='f')speaker=0;
    else speaker=1;
  }
  if(speaker){
    char* cmd=
      "amixer set Speaker off get;"
      "amixer set Headphone on get;"
      "xsetroot -name '  '";
    system(cmd);speaker=0;
  }else{
    char* cmd=
      "amixer set Speaker on get;"
      "amixer set Headphone off get;"
      "xsetroot -name '  '";
    system(cmd);speaker=1;
  }
}
