/*!@addtogroup mindsensors
 * @{
 * @defgroup msrmux RCX Sensor MUX
 * RCX Sensor MUX
 * @{
 */

/*
 * $Id: MSRXMUX-driver.h 29 2010-06-25 12:55:41Z xander $
 */

/** \file MSRXMUX-driver.h
 * \brief Mindsensors MSRXMUX RCX Sensor MUX Sensor driver
 *
 * MSRXMUX-driver.h provides an API for the Mindsensors MSRXMUX RCX Sensor MUX Sensor
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 30 August 2009
 * \version 0.1
 * \example MSRXMUX-test1.c
 */

#pragma systemFile

#ifndef __MSRXMUX_H__
#define __MSRXMUX_H__

#ifndef __COMMON_H__
#include "common.h"
#endif

#define MSRXMUX_I2C_ADDR  0x7E      /*!< I2C address for sensor */
#define MSRXMUX_CHAN1     0xFE      /*!< Select MUX channel 1 */
#define MSRXMUX_CHAN2     0xFD      /*!< Select MUX channel 2 */
#define MSRXMUX_CHAN3     0xFB      /*!< Select MUX channel 3 */
#define MSRXMUX_CHAN4     0xF7      /*!< Select MUX channel 4 */
#define MSRXMUX_NONE      0xFF      /*!< Deselect all MUX channels */

tByteArray MSRXMUX_I2CRequest;       /*!< Array to hold I2C command data */

TSensorTypes RCXSensorTypes[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
TSensorModes RCXSensorModes[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
byte RCXSensorDelays[4][4] =        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

/**
 * Send a direct command to the PFMate sensor
 *
 * Note: this is an internal command and should not be called directly.
 * @param link the PFMate port number
 * @param chan the channel to be configured
 * @param chantype the sensor type connected to the channel
 * @param chanmode the sensor mode of the sensor
 * @param delay the initialisation delay time
 * @return true if no error occured, false if it did
 */
void MSRXMUXsetupChan(tSensors link, byte chan, TSensorTypes chantype, TSensorModes chanmode, byte delay) {
  if (chan < 1 || chan > 4)
    return;

  RCXSensorTypes[link][chan-1] = chantype;
  RCXSensorModes[link][chan-1] = chanmode;
  RCXSensorDelays[link][chan-1] = delay;
}

int MSRXMUXreadChan(tSensors link, byte chan) {
  if (SensorType[link] != sensorLowSpeed9v) {
    SensorType[link] = sensorLowSpeed9v;
    wait1Msec(3);
  }

  MSRXMUX_I2CRequest.arr[0] = 2;
  MSRXMUX_I2CRequest.arr[1] = MSRXMUX_I2C_ADDR;
  switch(chan) {
    case 0: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_NONE; break;
    case 1: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_CHAN1; break;
    case 2: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_CHAN2; break;
    case 3: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_CHAN3; break;
    case 4: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_CHAN4; break;
    default: MSRXMUX_I2CRequest.arr[2] =  MSRXMUX_NONE;
  }

  if (!writeI2C(link, MSRXMUX_I2CRequest, 0))
    return -1;

  wait10Msec(3+RCXSensorDelays[link][chan-1]);
  SensorType[link] = RCXSensorTypes[link][chan-1];
  SensorMode[link] = RCXSensorModes[link][chan-1];
  return(SensorValue(link));
}

#endif // __MSRXMUX_H__

/*
 * $Id: MSRXMUX-driver.h 29 2010-06-25 12:55:41Z xander $
 */
/* @} */
/* @} */
