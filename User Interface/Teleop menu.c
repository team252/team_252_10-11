//supress errors
//headers
#include "Teleop menu.h"
#include "LogController.c"
#include"../motorCode/motorControl.c"
/* Current_function values:
0=log
1=menu
*/

//change star location
//param p can be 1 or -1 to indicate moving down or up respectively
void change_menu(int p){
  //precondition
  if(abs(p)!=1){
    p=0;
    NSLog("P must be 1");
  }else{
    //move star in direction of p
    star=star+p;
    //move selection in direction of p
    selection=selection+p;
    //if star is at number of items displayable on screen
    if(star==itemsOnScreenAtATime+1){
      //Find out how many elements
      //If we can scroll more
      //In more technical terms if the top item is lower than the amount of items we will have to scroll of the top we scroll the menu
      //We determine how many lines we will have to scroll by taking the amount of items - the items that can be on screen at a time
      if (top_menu<((sizeof(opt)/sizeof(opt[0]))-itemsOnScreenAtATime+1)){
        //scroll the menu up
		    top_menu++;
		  }
		  //put the star back to 7
		  star--;
	  }
	  //if we go above the visible menu items
	  if(star==-1){
	    //if we have scrolled down the menu
	    if(top_menu>0){
	      //scroll up the menu
	      top_menu--;
	    }
	    //put the star back on the screen
	    star++;
	  }
	  //Draw menu items
	  for(int i = 0; i<=itemsOnScreenAtATime;i++){
	    if(i==star){
	      menu_txt="*"+opt[i+top_menu]+"";
	    }else{
	      menu_txt=" "+opt[i+top_menu]+"";
	    }
	    nxtDisplayTextLine(i,menu_txt);
	  }
  }
}
void drawMenu(){
  //Draw menu items
	  for(int i = 0; i<=itemsOnScreenAtATime;i++){
	    if(i==star){
	      //construct menu text line with star
	      menu_txt="*"+opt[i+top_menu]+"";
	    }else{
	      //construct menu text line without star
	      menu_txt=" "+opt[i+top_menu]+"";
	    }
	    //display text at line
	    nxtDisplayTextLine(i,menu_txt);
	  }
}
void display_menu(){

  //bool we use to keep from redrawing everything
  run_once=false;

  drawMenu();
	wait1Msec(250);
  //while we are not pressing enter
  while(nNxtButtonPressed!=3){
    //if we press the left button
    //and it has been .5 seconds since the last button press
    //and we have an upper menu to go to
    if(nNxtButtonPressed==2 && time1[T1] > 500 && selection > 0){
      time1[T1] = 0; //reset time 1 so that we don't repeat
      change_menu(-1); //decrease selection
    }else if(nNxtButtonPressed==1 && time1[T1] > 500 && selection < 7){ //same as above but with right button and making sure we have a menu item below us
      change_menu(1); //increase selection
      time1[T1] = 0; //reset time
    }
  }
  while(nNxtButtonPressed==3); //do not double read enters so hang while holding enter
  eraseDisplay(); //clear display
  switch(selection) //get delection and make decision
  {
    case 0: //go back
      current_function=previous_function;//go back to prev page
      ClearSounds(); //clear sound buffer. not neccesary probably
    break;
    case 1:
      current_function=0;//log
    break;
  }
  wait1Msec(250); // don't immediately move on wait .25 seconds
}

void menu_init(){ //initialize menu
  isShowingLog = logShowingBegin; //we have a nive var in the header as to whether or not we are showing log
  NSLog("Log"); //just give it an itial entry
}
void menu_main(){
  switch(current_function)//get current function and make decision based on it
  {
    case 0: //function 0 log
      if(!isShowingLog) show_log(); //if the log isnt showing show it
        if(nNxtButtonPressed == 2){ //if we are pressing left
          while(nNxtButtonPressed == 2); //must click and release to scroll another line
          scroll_down();
        }
        if(nNxtButtonPressed == 1){ //if we are pressing right
          while(nNxtButtonPressed==1); //must click and release to scroll another line
          scroll_up();
        }
    break;
    case 1: //function 1 menu
      display_menu();
    break;
  }
  if(nNxtButtonPressed==3 && current_function!=1){ //if we press enter and are not on menu
    while(nNxtButtonPressed==3); //dont allow double reads. you have to release before anything happens
    hide_log(); //hide the menu. cant hurt
    previous_function=current_function; //save the old function number
    current_function=1; //set the current function to menu
  }
}
