#include "../config.h"
#include "../local.h"
#include <stdlib.h>

void pickScreen(const Arg *Arg){
  char cmd[]=
    "xwd %%%%%"
    "|magick xwd:- png:-"
    "|xclip "
    "-target image/png "
    "-selection clipboard";
  freplace('%', Arg->c, cmd);
  system(cmd);
}
