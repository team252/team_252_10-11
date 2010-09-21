#pragma systemFile

#define itemsOnScreenAtATime 7
string opt[] = {"Back", "Log"};
int selection = 0;
int current_function = 0;
bool run_once = false;
bool logShowingBegin = true;
string menu_txt = "";
int previous_function = 0;
int star = 0;
int top_menu = 0;
bool joyOverRide = false;
void change_menu(int p);
void menu_init();
void menu_main();
