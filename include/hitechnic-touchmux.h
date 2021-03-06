/*!@addtogroup HiTechnic
 * @{
 * @defgroup httmux Touch Sensor MUX
 * HiTechnic Touch Sensor MUX
 * @{
 */

#ifndef __HTTMUX_H__
#define __HTTMUX_H__
/** \file hitechnic-touchmux.h
 * \brief HiTechnic Touch Sensor Multiplexer Sensor driver
 *
 * hitechnic-touchmux.h provides an API for the HiTechnic Touch Sensor Multiplexer Sensor.
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
 * \date 15 March 2009
 * \version 0.1
 * \example hitechnic-touchmux-test1.c
 */

#pragma systemFile

short HTTMUXgetActive(tSensors link);
bool HTTMUXisActive(tSensors link, short touch);

/**
 * Read the value of all of the currently connected touch sensors.  The status is logically OR'd
 * together. Touch 1 = 1, Touch 2 = 2, Touch 3 = 4, Touch 4 = 8.  If Touch 1 and 3 are active,
 * the return value will be 1 + 4 == 5.
 * @param link the HTTMUX port number
 * @return the value of the switches status
 */
short HTTMUXgetActive(tSensors link) {
  long muxvalue = 0;
  long switches = 0;

  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SensorType[link] = sensorRawValue;
    sleep(100);
  }

  // Voodoo magic starts here.  This is taken straight from the Touch MUX pamphlet.
  // No small furry animals were hurt during the calculation of this algorithm.
  muxvalue = 1023 - SensorRaw[link];
  switches = 339 * muxvalue;
  switches /= (1023 - muxvalue);
  switches += 5;
  switches /= 10;

  return (short)switches;
}

/**
 * Read the value of specific touch sensor.
 * @param link the HTTMUX port number
 * @param touch the touch sensor to be checked, numbered 1 to 4.
 * @return the value of the switches status
 */
bool HTTMUXisActive(tSensors link, short touch) {
  if (HTTMUXgetActive(link) & (1 << (touch - 1)))
    return true;
  else
    return false;
}

#endif // __HTTMUX_H__

/* @} */
/* @} */
