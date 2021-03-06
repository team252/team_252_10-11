#pragma config(Sensor, S1,     MSHID,               sensorLowSpeed9v)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: MSHID-test1.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * HTCS-driver.h provides an API for the Mindsensors HID Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 28 November 2009
 * version 0.2
 */

#include "drivers/common.h"
#include "drivers/MSHID-driver.h"

task main () {
  //                      |
  //             1234567890123456789
  string msg1 = "notepad\r\n";
  string msg2 = "hello world";

  // Tell the MSHID you are going to send raw keyboard data
  MSHIDsendCommand(MSHID, MSHID_DDATA);

  // The raw keyboard data (Windows Key + R)
  MSHIDsendKeyboardData(MSHID, MSHID_MOD_LGUI, 0x15);

  /// Transmit the data
  MSHIDsendCommand(MSHID, MSHID_XMIT);

  // Wait the command box to appear
  wait1Msec(1000);

  // Set the MSHID to normal ACSII mode
  MSHIDsendCommand(MSHID, MSHID_ASCII);

  // Send the first command: "notepad" followed by \r\n (enter)
  MSHIDsendString(MSHID, msg1);

  // Wait for notepad to start up
  wait1Msec(2000);

  // Send the second message "hello world"
  MSHIDsendString(MSHID, msg2);
}
