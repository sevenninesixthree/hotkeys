#ifndef CONFIG
#define CONFIG

enum MaskValue{Ctrl,Alt,Shift,Lenth};
static const int KeyCode[]={
  29,56,42
};
#define MKY(KEYV) (1<<KEYV)

void sub_audio();
void add_audio();
void mute();

struct hotkeys{
  int needMask;int needCode;void (*fun)();
}static const keymap[]={
  {MKY(Alt)|MKY(Shift),   65,   sub_audio},
  {MKY(Alt)|MKY(Shift),   66,   add_audio},
  {MKY(Alt)|MKY(Shift),   64,   mute}
};

#endif
