#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include "local.h"

int main(){
  char* dev=getDev("keyboard");
  char path[]="/dev/input/something";
  int i=check("/dev/input/", path),j=0;
  while(dev[j]){path[i+j]=dev[j];j++;}
  path[i+j]='\0';

  int fd=open(path, O_RDONLY);
  if(fd<0){perror(path);return -fd;}
  struct input_event ev;

  for(;;){
    read(fd, &ev, sizeof(ev));
    printf("\ntype:%d code:%d value:%d",ev.type,ev.code,ev.value);
  }
  return 0;
}
