#pragma config(Sensor, S1,     MSANG,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-angle.h provides an API for the Mindsensors Angle Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * date 31 November 2012
 * version 0.1
 */

#define debounce() while (nNxtButtonPressed != kNoButton) EndTimeSlice()

#include "mindsensors-angle.h"

// This is the value when I calibrated it, yours may vary
float gramsPerUnit = 1.084507;

// Get the current weight of the object
short weighObject()
{
  return max2(0, round(MSANGreadRaw(MSANG) * gramsPerUnit));
}

// Allow the user to calibrate the scales
void calibrateScales()
{
  short calibrateWeight = 0;

  eraseDisplay();
  displayCenteredTextLine(0, "GlideWheel-AS");
  displayCenteredTextLine(2, "Place the object");
  displayCenteredTextLine(3, "on the scales");
  displayCenteredTextLine(4, "and press");
  displayCenteredTextLine(5, "[enter]");
  displayCenteredTextLine(6, "to calibrate");
  while (nNxtButtonPressed != kEnterButton) EndTimeSlice();
  debounce();
  eraseDisplay();
  calibrateWeight = weighObject();
  displayCenteredTextLine(0, "GlideWheel-AS");
  displayCenteredTextLine(2, "Enter the weight");
  displayCenteredTextLine(3, "in grams");
  displayCenteredTextLine(7, "-     OK     +");
  while (true)
  {
    displayCenteredBigTextLine(5, "%d", calibrateWeight);
    switch(nNxtButtonPressed)
    {
      case kLeftButton: playTone(500,10); calibrateWeight--; calibrateWeight = max2(0, calibrateWeight); break;
      case kRightButton: playTone(1000,10); calibrateWeight++; break;
      case kEnterButton: playTone(1500,10);gramsPerUnit = (float)calibrateWeight / (float)MSANGreadRaw(MSANG); eraseDisplay(); return;
    }
    sleep(20);
    debounce();
  }
}

task main () {
  nNxtButtonTask  = -2;
  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "Angle");
  displayCenteredTextLine(3, "Test 2");
  displayCenteredTextLine(5, "Connect sensor");
  displayCenteredTextLine(6, "to S1");
  MSANGresetAngle(MSANG);
  sleep(2000);

  eraseDisplay();

  while (true) {
    // Reset the angle to 0
    if (nNxtButtonPressed == kEnterButton)
    {
      debounce();
      calibrateScales();
      debounce();
    }
    displayCenteredTextLine(0, "GlideWheel-AS");
    displayCenteredTextLine(1, "Weighing scale");
    displayTextLine(7, "[enter] to calib.");

    displayCenteredBigTextLine(4, "%d g", weighObject());

    sleep(20);
  }
}
