#pragma config(Sensor, S1,     HTPB,                sensorLowSpeed9v)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTPB-exp8.c 25 2010-05-11 13:18:02Z xander $
 */

/**
 * HTPB-driver.h provides an API for the HiTechnic Protoboard.  This is program 7
 * for the HTPB experimenter's kit.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 07 May 2010
 * version 0.1
 */

#include "drivers/common.h"
#include "drivers/HTPB-driver.h"

// This is the temperature at which we switch on the LED
#define THRESHOLD 28

long temperature;
long inputdata;

task main() {
  // The data to be written: 0x3F = 111111 binary,
  // makes B4 digital port an output.
  HTPBsetupIO(HTPB, 0x3F);

  while(true) {
    // Read the value from the temp sensor
    inputdata = HTPBreadADC(HTPB, 0, 10);

    // Convert to an actual temperature
    temperature = ((inputdata - 186) * 32 / 99);
    eraseDisplay();
    nxtDisplayTextLine(1, "%d", temperature);

    // If we're above 28 degrees, switch on the LED
    if(temperature > THRESHOLD) {
      HTPBwriteIO(HTPB, 0x10);
    } else {
      HTPBwriteIO(HTPB, 0x00);
    }
    wait1Msec(50);
  }
}

/*
 * $Id: HTPB-exp8.c 25 2010-05-11 13:18:02Z xander $
 */
