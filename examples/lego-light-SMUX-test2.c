#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * lego-light.h provides an API for the Lego Light Sensor.  This program
 * demonstrates how to use that API to calibrate the sensor connected to a SMUX.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.2
 */

#include "hitechnic-sensormux.h"
#include "lego-light.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor LEGOLS = msensor_S1_4;

task main () {
  short raw = 0;
  short nrm = 0;
  // Get control over the buttons
  nNxtButtonTask  = -2;

  // Turn the light on
  LSsetActive(LEGOLS);

  eraseDisplay();
  displayTextLine(0, "Light Sensor Cal.");
  displayTextLine(2, "Left:  set black");
  displayTextLine(3, "Right: set white");
  displayTextLine(7, "Grey:  exit");

  while (true) {
    switch(nNxtButtonPressed) {
      // if the left button is pressed calibrate the black value for the sensor
      case kLeftButton:
                        LScalLow(LEGOLS);
                        playSound(soundBeepBeep);
                        while(bSoundActive) EndTimeSlice();
                        break;
      // if the left button is pressed calibrate the white value for the sensor
      case kRightButton:
                        LScalHigh(LEGOLS);
                        playSound(soundBeepBeep);
                        while(bSoundActive) EndTimeSlice();
                        break;
    }
    displayClearTextLine(5);
    displayClearTextLine(6);

    // Read the raw value of the sensor
    raw = LSvalRaw(LEGOLS);

    // Read the normalised value of the sensor
    nrm = LSvalNorm(LEGOLS);

    // Display the raw and normalised values
    displayTextLine(5, "R: %4d N: %4d", raw, nrm);

    // Display the values for black and white
    displayTextLine(6, "B: %4d W: %4d", lslow[LEGOLS], lshigh[LEGOLS]);
    sleep(50);
  }
}
