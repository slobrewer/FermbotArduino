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

float TempController::readFermTempF() {
  return fermentationThermometer.readTemperatureF();
}

bool TempController::isFermTempError() const {
  return fermentationThermometer.isInError();
}

void TempController::processTempControl() {
  lastFermTemp = this->fermentationThermometer.readTemperatureF();
  this->lastFermTempIsInError = this->fermentationThermometer.isInError();
  this->lastTargetTemp = this->targetTemp;

  if (this->lastFermTempIsInError) {
    lastDecision = "Error reading temperature.";
    return;
  }

  if (abs(this->lastFermTemp - this->targetTemp) < DEADBAND_RADIUS) {
    this->lastDecision = "Temperature within deadband. Cooling unchanged.";
  } else if (this->lastFermTemp < this->targetTemp) {
    this->lastDecision = "Temperature below target. Cooling disabled.";
    this->coolingControl.requestOff();
  } else {
    this->lastDecision = "Temperature above target. Cooling enabled.";
    this->coolingControl.requestOn();
  }

  lastCoolingRequested = this->coolingControl.isRequestedOn();
  lastCoolingPoweredOn = this->coolingControl.isPoweredOn();
}

void TempController::requestEnableCoolingControl(bool enabled) {
  this->coolingControl.requestOn();
}

bool TempController::getCoolingControlRequested() const {
  return this->coolingControl.isPoweredOn();
}

} /* namespace Fermbot */
