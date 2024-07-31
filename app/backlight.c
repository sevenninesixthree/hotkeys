#include "../local.h"
#include "../config.h"
#include <stdlib.h>
#include <stdio.h>

#define BRPATH "/sys/class/backlight/amdgpu_bl1/"
int blt_max=0;

void bright_init(){
  FILE *file=fopen(BRPATH"max_brightness","r");
  fscanf(file, "%d",&blt_max);
}

int get_bright(){
  FILE *file=fopen(BRPATH"actual_brightness", "r");
  int ans;fscanf(file, "%d",&ans);return ans;
}

void set_bright(char* num){
  char cmd[]="echo %%%%%% >"BRPATH"brightness";
  freplace('%', num, cmd);system(cmd);
}

void itos(unsigned int from,char* to){
  if(from==0){to[0]='0';to[1]='\n';return;}
  char temp[]="%%%%";int i=0;
  while(from){
    temp[i++]=from%10+'0';from/=10;
  }
  for(int j=0;j<i;j++)to[j]=temp[i-j-1];
  to[i]='\n';
}

void show(double bright){
  double percent=bright/blt_max*100;
  char num[]="%%%%";itos(percent, num);
  char cmd[]="xsetroot -name ' 󰛩:!!!%'";
  freplace('!', num, cmd);system(cmd);
}

void sub_backlight(){
  if(blt_max==0)bright_init();
  int bright=get_bright();
  bright-=1;if(bright<0)bright=0;
  char num[]="%%%%";itos(bright, num);
  set_bright(num);show(bright);
}
void add_backlight(){
  if(blt_max==0)bright_init();
  int bright=get_bright();
  bright+=1;if(bright>blt_max)bright=blt_max;
  char num[]="%%%%";itos(bright, num);
  set_bright(num);show(bright);
}
