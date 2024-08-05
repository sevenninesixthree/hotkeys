#ifndef CONFIG
#define CONFIG

enum MaskValue{Ctrl,Alt,Shift,Lenth};
static const int KeyCode[]={
  29,56,42
};
#define MKY(KEYV) (1<<KEYV)

typedef union {
  int i;
  char* c;
}Arg;

void deltaAudio(const Arg*);
void mute(const Arg*);
void deltaBacklight(const Arg*);

struct hotkeys{
  int needMask;int needCode;void (*fun)(const Arg*);const Arg Arg;
}static const keymap[]={
  {MKY(Alt),          65,   deltaAudio,       {.c="-1\n"}},
  {MKY(Alt),          66,   deltaAudio,       {.c="+1\n"}},
  {MKY(Alt),          64,   mute,             {0}},
  {MKY(Alt),          60,   deltaBacklight,   {.i=-1}},
  {MKY(Alt),          61,   deltaBacklight,   {.i=1}}
};

#endif
