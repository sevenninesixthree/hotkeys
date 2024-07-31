#include <stdio.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "local.h"
#include "config.h"

void changeMask(struct input_event ev,int *mask){
  for(int i=0;i<Lenth;i++)
    if(ev.code==KeyCode[i]){
      if(ev.value)*mask|=1<<i;
      else *mask&=~(1<<i);
      return;
    }
}

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
