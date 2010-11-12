#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorNone, openLoop)
/////////////////////////////////////////////////////////////////////
//test_motor.h.c
//unit test for motor.h
//this runs each of the four drive motors forward for one second each
/////////////////////////////////////////////////////////////////////
#include "defines.h"
#include "../../2010-2011 Competition Code/motor.h" //includes the motor.h file which defines the motors and the setMotor function
task updateDisplay(){
  eraseDisplay();
  while(true){
    nxtDisplayTextLine(0, "Right Front: " + getMotor(RIGHT_FRONT)); //Display right front speed
    nxtDisplayTextLine(1, "Left Front: " + getMotor(LEFT_FRONT)); //Display left front speed
    nxtDisplayTextLine(2, "Right Rear: " + getMotor(RIGHT_REAR)); //Display right rear speed
    nxtDisplayTextLine(3, "Left Rear: " + getMotor(LEFT_REAR));  //Display left rear speed
  }
}
task main(){//main task
  StartTask(updateDisplay);
  bMotorReflected[motorE] = true; //flips right front motor
  bMotorReflected[motorG] = true; //flips right rear motor
  setMotor(RIGHT_FRONT,100); //sets right front motor to 100
  wait1Msec(1000); //wait one second
  setMotor(RIGHT_FRONT,0); //stop right front motor
  setMotor(LEFT_FRONT, 100); //set left front to 100
  wait1Msec(1000); //wait one second
  setMotor(LEFT_FRONT,0); //stops left front motor
  setMotor(RIGHT_REAR,100); //sets right rear motot to 100
  wait1Msec(1000); //wait one second
  setMotor(RIGHT_REAR,0); //stops right rear motor
  setMotor(LEFT_REAR,100); //set left rear motor to 100
  wait1Msec(1000); //wait one second
  setMotor(LEFT_REAR,0); //stop left rear motor
  StopAllTasks();
}
