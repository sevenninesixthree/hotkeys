#include <linux/input-event-codes.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "local.h"

enum MaskValue{Ctrl,Alt,Shift,Lenth};
int KeyCode[]={
  29,56,42
};

#define BUF_SIZ 5
char buffer[BUF_SIZ];

void add_audio(){
  char* cmd=
    "amixer get Master"
    "|grep Mono:"
    "|awk '{print $3+1}'";
  FILE* info=popen(cmd, "r");
  fgets(buffer, BUF_SIZ, info);pclose(info);

  char ocmd[]=
    "amixer set Master %%%%"
    "|grep Mono:"
    "|awk '{print $4}'"
    "|tr -cd 0-9";
  freplace('%', buffer, ocmd);info=popen(ocmd,"r");

  fgets(buffer, BUF_SIZ, info);pclose(info);
  char bar[]="xsetroot -name audio:%%%%";
  int i=replace('%', buffer, bar);
  bar[i]=0;system(bar);
}
void sub_audio(){
  char* cmd=
    "amixer get Master"
    "|grep Mono:"
    "|awk '{print $3-1}'";
  FILE* info=popen(cmd, "r");
  fgets(buffer, BUF_SIZ, info);pclose(info);

  char ocmd[]=
    "amixer set Master %%%%"
    "|grep Mono:"
    "|awk '{print $4}'"
    "|tr -cd 0-9";
  freplace('%', buffer, ocmd);info=popen(ocmd,"r");

  fgets(buffer, BUF_SIZ, info);pclose(info);
  char bar[]="xsetroot -name audio:%%%%";
  int i=replace('%', buffer, bar);
  bar[i]=0;system(bar);
}

struct hotkeys{
  int needMask;
  int needCode;
  void (*fun)();
};

void changeMask(struct input_event ev,int *mask){
  for(int i=0;i<Lenth;i++)
    if(ev.code==KeyCode[i]){
      if(ev.value)*mask|=1<<i;
      else *mask&=~(1<<i);
      return;
    }
}

struct hotkeys keymap[]={
  {1<<Alt,  65,   sub_audio},
  {1<<Alt,  66,   add_audio}
};

int main(){
  char* dev=getDev("keyboard");
  char path[]="/dev/input/something";
  int i=check("/dev/input/", path),j=0;
  while(dev[j]){path[i+j]=dev[j];j++;}
  path[i+j]='\0';

  int fd=open(path, O_RDONLY);
  if(fd<0){perror(path);return -fd;}
  struct input_event ev;

  int Mask=0;
  for(;;){
    read(fd, &ev, sizeof(ev));
    changeMask(ev, &Mask);
    for(int i=0;i<sizeof(keymap)/sizeof(struct hotkeys);i++){
      if(ev.value&&keymap[i].needMask==Mask&&keymap[i].needCode==ev.code)
        keymap[i].fun();
    }
  }
  return 0;
}
