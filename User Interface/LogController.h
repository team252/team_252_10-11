#define fillWithNumbers 1
string screenText[15];
bool isShowingLog = false;
bool logHasBeenInitiated = false;
int top = 7;
void scroll_down();
void scroll_up();
void hide_log();
void show_log();
void drawLog();
void NSLog(int sFormatStrings);
void NSLog(string sFormatString);
void NSLogClear();
