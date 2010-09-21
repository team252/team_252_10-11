#include "LogController.h"
//SCROLLING
void scroll_down(){
  //If there is atleast one log line at the top so we don't scroll all text off the screen
  if(top<14){
    //scroll down
    //Technically top line is higher index
    top++;
  }
  drawLog();
}
void scroll_up(){
  //if we have an entry associated with the top line on the screen
  //technically if the top is associated with an index of more than 7 so that we can associate it with line 7 or lower
  if(top>7){
    //scroll up
    //Technically top line is lower index so a more recent log item is at top of screen
    top--;
  }
  drawLog();
}
//VISUAL INTERFACE
void hide_log(){
  //set variable so nothing is drawn
  isShowingLog=false;
  //clear the display
  eraseDisplay();
}
void show_log(){
  //set to draw log on update
  isShowingLog=true;
  //clear the display
  eraseDisplay();
  //set log to show mose recent entry
  top = 7;
  drawLog();
}
void drawLog(){
  //If the log isnt showing then skip this
  if(!isShowingLog) return;
  //for each line visible
  for(int i=0;i<=7;i++){
    //if we are writing a line that is linked to an index and not a blank line due to scrolling
    //technically if the top line index - the line we are drawing is < 15 it is a valid index associated line so use the text in the index
    if(top-i<15){
      //display the log entry at index the first lines index -
      nxtDisplayTextLine(i,screenText[top-i]);
    }else{
      nxtDisplayTextLine(i,"");
    }
  }
}
void NSLogClear() {
  logHasBeenInitiated = false;//dont display
  eraseDisplay();//clear
  isShowingLog = false;//dont show
}
//DATA MANAGING
void NSLog(int sFormatStrings) {
  string sFormatString = ""+sFormatStrings+"";//make string from int
  NSLog(sFormatString);//log the string
}
void NSLog(string sFormatString) {
  if (!logHasBeenInitiated) {//if log not init
    for (int i=0;i<15;i++){//init log
      #if fillWithNumbers//debug
      screenText[i] = "";
      #else
      screenText[i] = ""+i;
      #endif
    }
    logHasBeenInitiated=true;//set log to initiated
  }
  if (isShowingLog) {//if showing log
    eraseDisplay();//clear display
    drawLog();//draw the log
  }
  string screenTextTemp[15];//make string array for temp
  for (int i=0;i<15;i++) {//put text in it
    screenTextTemp[i] = screenText[i];
  }
  string text;//make text string
  StringFormat(text, sFormatString);//format it
  screenText[0] = text;//set it to first index
  for (int i=0;i<14;i++) {//restore temp array to main array
    screenText[i+1] = screenTextTemp[i];
  }

  if (isShowingLog) {//if the log is showing
    top = 7;//reset to normal height
    drawLog();//draw the log
  }
}
