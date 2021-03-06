/*!@addtogroup HiTechnic
 * @{
 * @defgroup htang Angle Sensor
 * HiTechnic Angle Sensor
 * @{
 */

#ifndef __HTANG_H__
#define __HTANG_H__
/** \file hitechnic-angle.h
 * \brief HiTechnic Angle Sensor driver
 *
 * hitechnic-angle.h provides an API for the HiTechnic Angle Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Replaced array structs with typedefs
 *
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * \author Xander Soldaat (xander_at_botbench.com)
 * \date 20 February 2011
 * \version 0.2
 * \example hitechnic-angle-test1.c
 * \example hitechnic-angle-SMUX-test1.c
 */

#pragma systemFile
#include "hitechnic-sensormux.h"

#ifndef __COMMON_H__
#include "common.h"
#endif

#define HTANG_I2C_ADDR         0x02      /*!< HTCS2 I2C device address */
#define HTANG_CMD_REG          0x41      /*!< Command register */
#define HTANG_OFFSET           0x42      /*!< Offset for data registers */

// Values contained by registers in active mode
#define HTANG_ANG2             0x00      /*!< Current angle (2 deg increments) */
#define HTANG_ANG1             0x01      /*!< Current angle (1 deg adder) */
#define HTANG_ACC_ANG_B4       0x02      /*!< 32 bit accumulated angle 4th byte */
#define HTANG_ACC_ANG_B3       0x03      /*!< 32 bit accumulated angle 3rd byte */
#define HTANG_ACC_ANG_B2       0x04      /*!< 32 bit accumulated angle 2nd byte */
#define HTANG_ACC_ANG_B1       0x05      /*!< 32 bit accumulated angle 1st byte */
#define HTANG_RPM_H            0x06      /*!< 16 bit rpms, high byte */
#define HTANG_RPM_L            0x07      /*!< 16 bit rpms, low byte */

// Various commands
#define HTANG_CMD_MEASURE      0x00      /*!< Normal angle measurement mode */
#define HTANG_CMD_RST_ANG      0x43      /*!< Resets 0 position to current shaft angle, non-volatile setting */
#define HTANG_CMD_RST_ACC_ANG  0x52      /*!< Resets the accumulated angle */

typedef struct
{
  tI2CData I2CData;
  short angle;
  short accumlatedAngle;
  short rpm;
  ubyte _cmd;
  bool smux;
  tMUXSensor smuxport;
} tHTANG, *tHTANGPtr;

bool initSensor(tHTANGPtr htangPtr, tSensors port);
bool initSensor(tHTANGPtr htangPtr, tMUXSensor muxsensor);
bool readSensor(tHTANGPtr htangPtr);
bool resetSensor(tHTANGPtr htangPtr);
bool resetAccmulatedAngle(tHTANGPtr htangPtr);
bool resetAngle(tHTANGPtr htangPtr);
bool _sensorSendCommand(tHTANGPtr htangPtr);

//short HTANGreadAngle(tSensors link);
//long HTANGreadAccumulatedAngle(tSensors link);
//short HTANGreadRPM(tSensors link);
//bool HTANGresetAngle(tSensors link);
//bool HTANGresetAccumulatedAngle(tSensors link);
//bool _HTANGsendCommand(tSensors link, byte command);

//#ifdef __HTSMUX_SUPPORT__
//short HTANGreadAngle(tMUXSensor muxsensor);
//long HTANGreadAccumulatedAngle(tMUXSensor muxsensor);
//short HTANGreadRPM(tMUXSensor muxsensor);

tConfigParams HTANG_config = {HTSMUX_CHAN_I2C, 8, 0x02, 0x42};  /*!< Array to hold SMUX config data for sensor */
//#endif // __HTSMUX_SUPPORT__

//tByteArray HTANG_I2CRequest;             /*!< Array to hold I2C command data */
//tByteArray HTANG_I2CReply;               /*!< Array to hold I2C reply data */

///**
// * Return the current angle
// * @param link the HTANG port number
// * @return current angle or -1 if an error occurred.
// */
//short HTANGreadAngle(tSensors link) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  HTANG_I2CRequest[0] = 2;                         // Message size
//  HTANG_I2CRequest[1] = HTANG_I2C_ADDR;            // I2C Address
//  HTANG_I2CRequest[2] = HTANG_OFFSET + HTANG_ANG2; // Start Current angle

//  if (!writeI2C(link, HTANG_I2CRequest, HTANG_I2CReply, 2))
//    return -1;

//  return (HTANG_I2CReply[0] * 2) + HTANG_I2CReply[1];
//}

///**
// * Return the current angle
// * @param muxsensor the SMUX sensor port number
// * @return current angle or -1 if an error occurred.
// */
//#ifdef __HTSMUX_SUPPORT__
//short HTANGreadAngle(tMUXSensor muxsensor) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  if (HTSMUXSensorTypes[muxsensor] != HTSMUXSensorCustom)
//    HTSMUXconfigChannel(muxsensor, HTANG_config);

//  if (!HTSMUXreadPort(muxsensor, HTANG_I2CReply, 2, HTANG_ANG2)) {
//    return -1;
//  }

//  return (HTANG_I2CReply[0] * 2) + HTANG_I2CReply[1];
//}
//#endif // __HTSMUX_SUPPORT__

///**
// * Return the accumulated angle (signed 32 bit value)
// * @param link the HTANG port number
// * @return current angle or -1 if an error occurred.
// */
//long HTANGreadAccumulatedAngle(tSensors link) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  HTANG_I2CRequest[0] = 2;                                // Message size
//  HTANG_I2CRequest[1] = HTANG_I2C_ADDR;                   // I2C Address
//  HTANG_I2CRequest[2] = HTANG_OFFSET + HTANG_ACC_ANG_B4;  // Start accumulated angle

//  if (!writeI2C(link, HTANG_I2CRequest, HTANG_I2CReply, 4))
//    return -1;

//  return (HTANG_I2CReply[0] << 24) +
//         (HTANG_I2CReply[1] << 16) +
//         (HTANG_I2CReply[2] <<  8) +
//          HTANG_I2CReply[3];
//}

///**
// * Return the accumulated angle (signed 32 bit value)
// * @param muxsensor the SMUX sensor port number
// * @return current angle or -1 if an error occurred.
// */
//#ifdef __HTSMUX_SUPPORT__
//long HTANGreadAccumulatedAngle(tMUXSensor muxsensor) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  if (HTSMUXSensorTypes[muxsensor] != HTSMUXSensorCustom)
//    HTSMUXconfigChannel(muxsensor, HTANG_config);

//  if (!HTSMUXreadPort(muxsensor, HTANG_I2CReply, 4, HTANG_ACC_ANG_B4)) {
//    return -1;
//  }

//  return (HTANG_I2CReply[0] << 24) +
//         (HTANG_I2CReply[1] << 16) +
//         (HTANG_I2CReply[2] <<  8) +
//          HTANG_I2CReply[3];
//}
//#endif // __HTSMUX_SUPPORT__

///**
// * Return the rpm that the shaft is currently rotating at
// * @param link the HTANG port number
// * @return the current rpm of the shaft or -1 if an error occurred.
// */
//short HTANGreadRPM(tSensors link) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  HTANG_I2CRequest[0] = 2;                           // Message size
//  HTANG_I2CRequest[1] = HTANG_I2C_ADDR;              // I2C Address
//  HTANG_I2CRequest[2] = HTANG_OFFSET + HTANG_RPM_H;  // Start of rpm

//  if (!writeI2C(link, HTANG_I2CRequest, HTANG_I2CReply, 2))
//    return -1;

//  return (short)(HTANG_I2CReply[0] <<  8) +
//          HTANG_I2CReply[1];
//}

///**
// * Return the rpm that the shaft is currently rotating at
// * @param muxsensor the SMUX sensor port number
// * @return the current rpm of the shaft or -1 if an error occurred.
// */
//#ifdef __HTSMUX_SUPPORT__
//short HTANGreadRPM(tMUXSensor muxsensor) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  if (HTSMUXSensorTypes[muxsensor] != HTSMUXSensorCustom)
//    HTSMUXconfigChannel(muxsensor, HTANG_config);

//  if (!HTSMUXreadPort(muxsensor, HTANG_I2CReply, 2, HTANG_RPM_H)) {
//    return -1;
//  }

//  // return HTANG_I2CReply[0] * 2 + HTANG_I2CReply[1];

//  return (HTANG_I2CReply[0] <<  8) +
//          HTANG_I2CReply[1];
//}
//#endif // __HTSMUX_SUPPORT__

///**
// * Reset the 0 position to the current shaft angle.<br>
// * Note: this will also reset the accumulated angle counter
// * @param link the HTANG port number
// * @return true if no error occured, false if it did
// */
//bool HTANGresetAngle(tSensors link) {
//  return _HTANGsendCommand(link, HTANG_CMD_RST_ANG);
//}

///**
// * Reset the accumulated angle
// * @param link the HTANG port number
// * @return true if no error occured, false if it did
// */
//bool HTANGresetAccumulatedAngle(tSensors link) {
//  return _HTANGsendCommand(link, HTANG_CMD_RST_ACC_ANG);
//}

///**
// * Send a command to the sensor
// *
// * Note: this is an internal function and should not be called directly.
// * @param link the HTANG port number
// * @param command the command to be sent to the sensor
// * @return true if no error occured, false if it did
// */
//bool _HTANGsendCommand(tSensors link, byte command) {
//  memset(HTANG_I2CRequest, 0, sizeof(tByteArray));

//  HTANG_I2CRequest[0] = 3;              // Message size
//  HTANG_I2CRequest[1] = HTANG_I2C_ADDR; // I2C Address
//  HTANG_I2CRequest[2] = HTANG_CMD_REG;  // Command register
//  HTANG_I2CRequest[3] = command;        // Command to be sent

//  return writeI2C(link, HTANG_I2CRequest);
//}

/**
 * Initialise the sensor's data struct and port
 *
 * @param htangPtr pointer to the sensor's data struct
 * @param port the sensor port
 * @return true if no error occured, false if it did
 */
bool initSensor(tHTANGPtr htangPtr, tSensors port)
{
  memset(htangPtr, 0, sizeof(tHTANGPtr));
  htangPtr->I2CData.address = HTANG_I2C_ADDR;
  htangPtr->I2CData.port = port;
  htangPtr->I2CData.type = sensorI2CCustom;
  htangPtr->_cmd = HTANG_CMD_MEASURE;
  htangPtr->smux = false;

  // Ensure the sensor is configured correctly
  if (SensorType[htangPtr->I2CData.port] != htangPtr->I2CData.type)
    SensorType[htangPtr->I2CData.port] = htangPtr->I2CData.type;

  // Make sure the sensor is in the measurement mode
  return _sensorSendCommand(htangPtr);
}

/**
 * Initialise the sensor's data struct and MUX port
 *
 * @param htangPtr pointer to the sensor's data struct
 * @param muxsensor the sensor MUX port
 * @return true if no error occured, false if it did
 */
bool initSensor(tHTANGPtr htangPtr, tMUXSensor muxsensor)
{
  memset(htangPtr, 0, sizeof(tHTANGPtr));
  htangPtr->I2CData.address = HTANG_I2C_ADDR;
  htangPtr->I2CData.type = sensorI2CCustom;
  htangPtr->smux = true;
  htangPtr->smuxport = muxsensor;

  // Ensure the sensor is configured correctly
  if (SensorType[htangPtr->I2CData.port] != htangPtr->I2CData.type)
    SensorType[htangPtr->I2CData.port] = htangPtr->I2CData.type;

  return HTSMUXconfigChannel(muxsensor, HTANG_config);
}

/**
 * Read all the sensor's data
 *
 * @param htangPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */
bool readSensor(tHTANGPtr htangPtr)
{
  memset(htangPtr->I2CData.request, 0, sizeof(htangPtr->I2CData.request));

  if (htangPtr->smux)
  {
    if (!HTSMUXreadPort(htangPtr->smuxport, htangPtr->I2CData.reply, 8, HTANG_ANG2))
      return false;
  }
  else
  {
    // Read all of the data available on the sensor
    htangPtr->I2CData.request[0] = 2;                    // Message size
    htangPtr->I2CData.request[1] = htangPtr->I2CData.address; // I2C Address
    htangPtr->I2CData.request[2] = HTANG_OFFSET + HTANG_ANG2;
    htangPtr->I2CData.replyLen = 8;
    htangPtr->I2CData.requestLen = 2;

    if (!writeI2C(&htangPtr->I2CData))
      return false;
  }

  // Populate the struct with the newly retrieved data
  htangPtr->angle = (htangPtr->I2CData.reply[0] * 2) + htangPtr->I2CData.reply[1];
  htangPtr->accumlatedAngle = (htangPtr->I2CData.reply[2] << 24) +
                               (htangPtr->I2CData.reply[3] << 16) +
                               (htangPtr->I2CData.reply[4] <<  8) +
                               htangPtr->I2CData.reply[5];
  htangPtr->rpm = (short)(htangPtr->I2CData.reply[6] <<  8) + htangPtr->I2CData.reply[7];

  return true;
}

/**
 * Send a command to the sensor
 *
 * Note: this is an internal function and should not be called directly.
 * @param htangPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */
bool resetSensor(tHTANGPtr htangPtr)
{
  // Operation not supported on a SMUX
  if (htangPtr->smux)
    return false;

  // First reset the accumulated angle
  if (!resetAccmulatedAngle(htangPtr))
    return false;

   // Next, reset the angle
  return resetAngle(htangPtr);
}

/**
 * Send a command to the sensor
 *
 * Note: this is an internal function and should not be called directly.
 * @param htangPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */
bool resetAccmulatedAngle(tHTANGPtr htangPtr)
{
  // Operation not supported on a SMUX
  if (htangPtr->smux)
    return false;

  htangPtr->_cmd = HTANG_CMD_RST_ACC_ANG;
  return _sensorSendCommand(htangPtr);
}

/**
 * Send a command to the sensor
 *
 * Note: this is an internal function and should not be called directly.
 * @param htangPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */
bool resetAngle(tHTANGPtr htangPtr)
{
  // Operation not supported on a SMUX
  if (htangPtr->smux)
    return false;

  htangPtr->_cmd = HTANG_CMD_RST_ANG;
  return _sensorSendCommand(htangPtr);
}

/**
 * Send a command to the sensor
 *
 * Note: this is an internal function and should not be called directly.
 * @param htangPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */
bool _sensorSendCommand(tHTANGPtr htangPtr) {
  bool retVal = false;

  memset(htangPtr->I2CData.request, 0, sizeof(htangPtr->I2CData.request));

  htangPtr->I2CData.request[0] = 3;              // Message size
  htangPtr->I2CData.request[1] = HTANG_I2C_ADDR; // I2C Address
  htangPtr->I2CData.request[2] = HTANG_CMD_REG;  // Command register
  htangPtr->I2CData.request[3] = htangPtr->_cmd;        // Command to be sent

  retVal = writeI2C(&htangPtr->I2CData);
  htangPtr->_cmd = HTANG_CMD_MEASURE;

  return retVal;
}

#endif // __HTANG_H__

/* @} */
/* @} */
