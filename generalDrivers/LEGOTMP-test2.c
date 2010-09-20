#pragma config(Sensor, S1,     LEGOTMP,             sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * LEGOTMP-driver.h provides an API for the Lego Temperature Sensor.  This program
 * demonstrates how to use that API to use the sensor in single-shot mode.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Sylvain Cacheux for writing the initial drivers.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 16 february 2010
 * version 0.1
 */

#include "drivers/common.h"
#include "drivers/LEGOTMP-driver.h"

// Small function to convert the accuracy level into something humans can read
void accuracyToString(tLEGOTMPAccuracy _accuracy, string &text) {
  strcpy(text, "");
  switch (_accuracy) {
    case A_MIN:
      text = "A_MIN";
      break;
    case A_MEAN1:
      text = "A_MEAN1";
      break;
    case A_MEAN2:
      text = "A_MEAN2";
      break;
    case A_MAX:
      text = "A_MAX";
      break;
  }
}


task main() {
  float temp;
  tLEGOTMPAccuracy accuracy;
  string strAcc;

  nxtDisplayCenteredTextLine(0, "LEGO");
  nxtDisplayCenteredBigTextLine(1, "Temp");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();


  // Setup the sensor for Single shot mode
  LEGOTMPsetSingleShot(LEGOTMP);

  //setting minimum accuracy
  accuracy = A_MIN;
  if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
    nxtDisplayTextLine(0, "Error setAccuracy");
    wait1Msec(5000);
    StopAllTasks();
  }

  //reads the current accuracy of the sensor
  if (!LEGOTMPreadAccuracy(LEGOTMP, accuracy)) {
    nxtDisplayTextLine(0, "Error readAccuracy");
    wait1Msec(5000);
    StopAllTasks();
  }

  accuracyToString(accuracy, strAcc);
  nxtDisplayTextLine(0, "Accuracy: %s", strAcc);

  //loop to read temp
  while (true) {
    switch(nNxtButtonPressed) {
      // If the left button is pressed, decrease the accuracy
      case kLeftButton:
        switch(accuracy) {
          case A_MIN:   accuracy = A_MAX;   break;
          case A_MEAN1: accuracy = A_MIN;   break;
          case A_MEAN2: accuracy = A_MEAN1; break;
          case A_MAX:   accuracy = A_MEAN2; break;
        }
        if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
          nxtDisplayTextLine(0, "Error setAccuracy");
          wait1Msec(5000);
          StopAllTasks();
        }
        accuracyToString(accuracy, strAcc);
        nxtDisplayTextLine(0, "Accuracy: %s", strAcc);

        // debounce the button
        while (nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;

      // If the right button is pressed, increase the accuracy
      case kRightButton:
        switch(accuracy) {
          case A_MIN:   accuracy = A_MEAN1; break;
          case A_MEAN1: accuracy = A_MEAN2; break;
          case A_MEAN2: accuracy = A_MAX;   break;
          case A_MAX:   accuracy = A_MIN;   break;
        }
        if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
          nxtDisplayTextLine(0, "Error setAccuracy");
          wait1Msec(5000);
          StopAllTasks();
        }
        accuracyToString(accuracy, strAcc);
        nxtDisplayTextLine(0, "Accuracy: %s", strAcc);

        // debounce the button
        while (nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;
    }
    if (!LEGOTMPreadTemp(LEGOTMP, temp)) {
      eraseDisplay();
      nxtDisplayTextLine(0, "Temp reading pb");
      wait10Msec(100);
      StopAllTasks();
    }

    nxtDisplayCenteredBigTextLine(2, "Temp:");
    // Depending on the level of accuracy, you need to change the
    // the formatting of the float, makes it look nicer.
    switch(accuracy) {
      case A_MIN:   nxtDisplayCenteredBigTextLine(4, "%4.1f", temp); break;
      case A_MEAN1: nxtDisplayCenteredBigTextLine(4, "%5.2f", temp); break;
      case A_MEAN2: nxtDisplayCenteredBigTextLine(4, "%6.3f", temp); break;
      case A_MAX:   nxtDisplayCenteredBigTextLine(4, "%7.4f", temp); break;
    }
  }
}
