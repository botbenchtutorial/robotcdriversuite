/*!@addtogroup HiTechnic
 * @{
 * @defgroup HTMAG Magnetic Field Sensor
 * HiTechnic Magnetic Field Sensor
 * @{
 */

#ifndef __HTMAG_H__
#define __HTMAG_H__
/** \file hitechnic-magfield.h
 * \brief HiTechnic Magnetic Field Sensor driver
 *
 * hitechnic-magfield.h provides an API for the HiTechnic Magnetic Field Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * \author Xander Soldaat (xander_at_botbench.com)
 * \date 27 July 2010
 * \version 0.1
 * \example hitechnic-magfield-test1.c
 * \example hitechnic-magfield-SMUX-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

short HTMAGreadVal(tSensors link);
short HTMAGreadRaw(tSensors link);
short HTMAGstartCal(tSensors link);
short HTMAGreadCal(tSensors link);
void HTMAGsetCal(tSensors link, short bias);

#ifdef __HTSMUX_SUPPORT__
short HTMAGreadVal(tMUXSensor muxsensor);
short HTMAGreadRaw(tMUXSensor muxsensor);
short HTMAGstartCal(tMUXSensor muxsensor);
short HTMAGreadCal(tMUXSensor muxsensor);
void HTMAGsetCal(tMUXSensor muxsensor, short bias);
#endif

short HTMAG_bias[][] = {{512, 512, 512, 512}, /*!< Array for bias values.  Default is 512 */
                          {512, 512, 512, 512},
                          {512, 512, 512, 512},
                          {512, 512, 512, 512}};

/**
 * Read the value of the Magnetic Field Sensor
 * @param link the HTMAG port number
 * @return the value of the Magnetic Field Sensor (-200 to +200)
 */
short HTMAGreadVal(tSensors link) {
  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SensorType[link] = sensorRawValue;
    sleep(100);
  }

  return (SensorValue[link] - HTMAG_bias[link][0]);
}

/**
 * Read the value of the Magnetic Field Sensor
 * @param muxsensor the SMUX sensor port number
 * @return the value of the Magnetic Field Sensor (-200 to +200)
 */
#ifdef __HTSMUX_SUPPORT__
short HTMAGreadVal(tMUXSensor muxsensor) {
  return HTSMUXreadAnalogue(muxsensor) - HTMAG_bias[SPORT(muxsensor)][MPORT(muxsensor)];
}
#endif // __HTSMUX_SUPPORT__

/**
 * Read the raw value of the Magnetic Field Sensor
 * @param link the HTMAG port number
 * @return the value of the Magnetic Field Sensor (approx 300 to 700)
 */
short HTMAGreadRaw(tSensors link) {
  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SensorType[link] = sensorRawValue;
    sleep(100);
  }

  return SensorValue[link];
}

/**
 * Read the raw value of the Magnetic Field Sensor
 * @param muxsensor the SMUX sensor port number
 * @return the value of the Magnetic Field Sensor (approx 300 to 700)
 */
#ifdef __HTSMUX_SUPPORT__
short HTMAGreadRaw(tMUXSensor muxsensor) {
  return HTSMUXreadAnalogue(muxsensor);
}
#endif // __HTSMUX_SUPPORT__

/**
 * Calibrate the sensor by calculating the average bias of 5 raw readings.
 * @param link the HTMAG port number
 * @return the new bias value for the sensor
 */
short HTMAGstartCal(tSensors link) {
  short _avgdata = 0;

  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SensorType[link] = sensorRawValue;
    sleep(100);
  }

  // Take 5 readings and average them out
  for (short i = 0; i < 5; i++) {
    _avgdata += SensorValue[link];
    sleep(50);
  }

  // Store new bias
  HTMAG_bias[link][0] = (_avgdata / 5);

  // Return new bias value
  return HTMAG_bias[link][0];
}

/**
 * Calibrate the Magnetic Field Sensor by calculating the average bias of 5 raw readings.
 * @param muxsensor the SMUX sensor port number
 * @return the new bias value for the Magnetic Field Sensor
 */
#ifdef __HTSMUX_SUPPORT__
short HTMAGstartCal(tMUXSensor muxsensor) {
  short _avgdata = 0;

  // Take 5 readings and average them out
  for (short i = 0; i < 5; i++) {
    _avgdata += HTSMUXreadAnalogue(muxsensor);
    sleep(50);
  }

  // Store new bias
  HTMAG_bias[SPORT(muxsensor)][MPORT(muxsensor)] = (_avgdata / 5);

  // Return new bias value
  return HTMAG_bias[SPORT(muxsensor)][MPORT(muxsensor)];
}
#endif // __HTSMUX_SUPPORT__

/**
 * Override the current bias for the sensor manually
 * @param link the HTMAG port number
 * @param bias the new bias to be used
 */
void HTMAGsetCal(tSensors link, short bias) {
  HTMAG_bias[link][0] = bias;
}

/**
 * Override the current bias for the sensor manually
 * @param muxsensor the SMUX sensor port number
 * @param bias the new bias to be used
 */
#ifdef __HTSMUX_SUPPORT__
void HTMAGsetCal(tMUXSensor muxsensor, short bias) {
  HTMAG_bias[SPORT(muxsensor)][MPORT(muxsensor)] = bias;
}
#endif // __HTSMUX_SUPPORT__

/**
 * Retrieve the current bias for the sensor
 * @param link the HTMAG port number
 * @return the bias value for the sensor
 */
short HTMAGreadCal(tSensors link) {
  return HTMAG_bias[link][0];
}

/**
 * Retrieve the current bias for the sensor
 * @param muxsensor the SMUX sensor port number
 * @return the bias value for the sensor
 */
#ifdef __HTSMUX_SUPPORT__
short HTMAGreadCal(tMUXSensor muxsensor) {
  return HTMAG_bias[SPORT(muxsensor)][MPORT(muxsensor)];
}
#endif // __HTSMUX_SUPPORT__

#endif // __HTMAG_H__

/* @} */
/* @} */
