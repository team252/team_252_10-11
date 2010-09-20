#pragma config(Sensor, S1,     cam,                 sensorI2CCustomFastSkipStates)
#pragma config(Sensor, S2,     killswitch,          sensorTouch)
#pragma config(Motor,  motorA,          M_TILT,        tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          M_PAN,         tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: NXTCAM-test3.c 25 2010-05-11 13:18:02Z xander $
 */

/**
 * NXTCAM-driver.h provides an API for the Mindsensors NXTCam.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Gordon Wyeth for writing the original driver and cam_display program
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 28 November 2009
 * version 0.2
 */

#include "drivers/common.h"
#include "drivers/NXTCAM-driver.h"

// int xscale(int x) - Scales x values from camera coordinates to screen coordinates.
int xscale(int x) {
  return ((x - 12) * 99) / 175;
}

// int yscale(int y) - Scales y values from camera coordinates to screen coordinates.
int yscale(int y) {
  return ((143 - y) * 63) / 143;
}

/*
 Main task
 */
task main () {
  blob_array _blobs;
  memset(_blobs, 0, sizeof(blob_array));

  //blob_array _blobs;
  int _x, _y, _x1, _y1;
  int _nblobs;
  eraseDisplay();

  // pid variables
  float pwr_x, err_x, perr_x, aerr_x, sp_x, p_x, i_x, d_x = 0.0;
  float pwr_y, err_y, perr_y, aerr_y, sp_y, p_y, i_y, d_y = 0.0;

  sp_y = sp_x = 87;
  p_y = p_x = 0.5;
  d_y = d_x = 1.8;
  i_y = i_x = 0.05;

  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorB] = 0;

  // Initialise the camera
  NXTCAMinit(cam);
  while(true) {
    eraseDisplay();
    // Fetch all the blobs, have the driver combine all
    // the colliding blobs.
    _nblobs = NXTCAMgetBlobs(cam, _blobs);
    nxtDisplayTextLine(1, "%d, %f", _nblobs, perr_x);

    if (_nblobs == 0) {
      if ((perr_x > 0) && (nMotorEncoder[motorB] > 660)) {
	      motor[motorA] = 0;
	      motor[motorB] = 0;
	    } else if ((perr_x < 0) && (nMotorEncoder[motorB] < -660)) {
				motor[motorA] = 0;
				motor[motorB] = 0;
			}
	  } else {
	    _x = (_blobs[0].x2 + _blobs[0].x1)/2;
	    _y = (_blobs[0].y2 + _blobs[0].y1)/2;


	    err_x = _x - sp_x;
	    aerr_x += err_x;
	    pwr_x = (err_x * p_x) + ((err_x - perr_x) * d_x) + (aerr_x * i_x);


	    err_y = _y - sp_y;
	    aerr_y += err_y;
	    pwr_y = (err_y * p_y) + ((err_y - perr_y) * d_y) + (aerr_y * i_y);


	    motor[motorA] = round(pwr_y);
      motor[motorB] = round(pwr_x);

	    _x1 = xscale(_x);
	    _y1 = yscale(_y);
	    nxtEraseRect(_x1-6, _y1-6, _x1+6, _y1+6);

	    nxtDrawLine(_x1, _y1+3, _x1, _y1-3);
	    nxtDrawLine(_x1+3, _y1, _x1-3, _y1);

	    perr_y = err_y;
	    perr_x = err_x;
	  }
	  wait1Msec(50);
  }
}

/*
 * $Id: NXTCAM-test3.c 25 2010-05-11 13:18:02Z xander $
 */
