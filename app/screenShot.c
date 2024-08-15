#include "../config.h"
#include <stdlib.h>

void pickScreen(const Arg *Arg){
  char* cmd=
    "xwd -root"
    "|magick xwd:- png:-"
    "|xclip "
    "-target image/png "
    "-selection clipboard";
  system(cmd);
}
