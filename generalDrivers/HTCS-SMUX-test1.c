#pragma config(Sensor, S1,     HTSMUX,              sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTCS-SMUX-test1.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * HTCS-driver.h provides an API for the HiTechnic Color Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 25 November 2009
 * version 0.2
 */

#include "drivers/common.h"
#include "drivers/HTCS-driver.h"

task main () {
  int _color = 0;
  string _tmp;
  int red = 0;
  int green = 0;
  int blue = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "COLOUR");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and CS to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  // Before using the SMUX, you need to initialise the driver
  HTSMUXinit();

  // Tell the SMUX to scan its ports for connected sensors
  HTSMUXscanPorts(HTSMUX);

  eraseDisplay();
  while (true) {
    // The sensor is connected to the first port
    // of the SMUX which is connected to the NXT port S1.
    // To access that sensor, we must use msensor_S1_1.  If the sensor
    // were connected to 3rd port of the SMUX connected to the NXT port S4,
    // we would use msensor_S4_3

    // Read the currently detected colour from the sensor
    _color = HTCSreadColor(msensor_S1_1);

    // If colour == -1, it implies an error has occurred
    if (_color < 0) {
      nxtDisplayTextLine(4, "ERROR!!");
      nxtDisplayTextLine(5, "HTCSreadColor");
      wait1Msec(2000);
      StopAllTasks();
    }

    // Read the RGB values of the currently colour from the sensor
    // A return value of false implies an error has occurred
    if (!HTCSreadRGB(msensor_S1_1, red, green, blue)) {
      nxtDisplayTextLine(4, "ERROR!!");
      nxtDisplayTextLine(5, "HTCSreadRGB");
      wait1Msec(2000);
      StopAllTasks();
    }

    // Read the RGB values of the currently colour from the sensor
    // A return value of false implies an error has occurred
    nxtDisplayCenteredTextLine(0, "Color: %d", _color);
    nxtDisplayCenteredBigTextLine(1, "R  G  B");

    nxtEraseRect(0,10, 99, 41);
    nxtFillRect( 0, 10, 30, 10 + (red+1)/8);
    nxtFillRect(35, 10, 65, 10 + (green+1)/8);
    nxtFillRect(70, 10, 99, 10 + (blue+1)/8);
    StringFormat(_tmp, " %3d   %3d", red, green);
    nxtDisplayTextLine(7, "%s   %3d", _tmp, blue);

    wait1Msec(100);
  }
}

/*
 * $Id: HTCS-SMUX-test1.c 20 2009-12-08 22:59:13Z xander $
 */
