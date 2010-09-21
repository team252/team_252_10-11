//TESTS TELEOP MENU
#include "../User Interface/Teleop menu.c"
task main(){
  show_log();//show the log
  NSLog("start");
  menu_init();//init the menu
  while(true){
    menu_main();//run menu
  }
}
