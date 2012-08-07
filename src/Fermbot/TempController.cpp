/*
 * TempController.cpp
 *
 * The overall temperature controller class that sets up the components
 * and makes the temperature control decisions.
 *
 *  Created on: Aug 6, 2012
 *      Author: dlouw
 */

#include "TempController.h"

namespace Fermbot {

const DeviceAddress THERMOMETER_ADDRESS = { 0x28, 0xFA, 0x62, 0x14, 0x04, 0x00,
    0x00, 0x99 };
const uint8_t COOLING_CONTROL_PIN = 5;
const float DEADBAND_RADIUS = 0.5f;
const float DEFAULT_FERM_TEMP = 68.0f;

TempController::TempController()
    : fermentationThermometer(THERMOMETER_ADDRESS),
      coolingControl(COOLING_CONTROL_PIN),
      targetTemp(DEFAULT_FERM_TEMP) {
}

TempController::~TempController() {
}

float TempController::readFermentationTempF() {
  return fermentationThermometer.readTemperatureF();
}

bool TempController::isFermentationTempError() const {
  return fermentationThermometer.isInError();
}

void TempController::processTempControl() {
   float tempF = this->readFermentationTempF();

   if (this->fermentationThermometer.isInError()) {
      Serial.println("Error reading temperature.");
      return;
   }

   Serial.println("Processing Temp Control");
   Serial.print("Current Temperature: ");
   Serial.println(tempF);
   Serial.print("Target Temperature: ");
   Serial.println(this->targetTemp);

   if (abs(tempF - this->targetTemp) < DEADBAND_RADIUS) {
      Serial.println("Temperature within deadband. Cooling unchanged.");
   } else if (tempF < this->targetTemp) {
      Serial.println("Temperature below target. Cooling disabled.");
      this->coolingControl.requestOff();
   } else {
      Serial.println("Temperature above target. Cooling enabled.");
      this->coolingControl.requestOn();
   }
}

void TempController::requestEnableCoolingControl(bool enabled) {
   this->coolingControl.requestOn();
}

bool TempController::getCoolingControlRequested() const {
   return this->coolingControl.isPoweredOn();
}

} /* namespace Fermbot */
