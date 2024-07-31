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
void sub_backlight();
void add_backlight();

struct hotkeys{
  int needMask;int needCode;void (*fun)();
}static const keymap[]={
  {MKY(Alt)|MKY(Shift),   65,   sub_audio},
  {MKY(Alt)|MKY(Shift),   66,   add_audio},
  {MKY(Alt)|MKY(Shift),   64,   mute},
  {MKY(Alt)|MKY(Shift),   60,   sub_backlight},
  {MKY(Alt)|MKY(Shift),   61,   add_backlight}
};

#endif
