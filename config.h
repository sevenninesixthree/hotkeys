#ifndef CONFIG
#define CONFIG

enum MaskValue{Ctrl,Alt,Shift,Lenth};
static const int KeyCode[]={
  29,56,42
};
#define MKY(KEYV) (1<<KEYV)
#define DMASK MKY(Alt)|MKY(Shift)

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
  {DMASK,          65,          deltaAudio,       {.c="-1\n"}},
  {DMASK,          66,          deltaAudio,       {.c="+1\n"}},
  {DMASK,          64,          mute,             {0}},
  {DMASK,          60,          deltaBacklight,   {.i=-1}},
  {DMASK,          61,          deltaBacklight,   {.i=1}}
};

#endif
