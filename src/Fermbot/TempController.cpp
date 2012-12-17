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
const uint8_t COOLING_CONTROL_PIN = 4;
const uint8_t HEATING_CONTROL_PIN = 5;
const float DEADBAND_RADIUS = 0.5f;
const float DEFAULT_FERM_TEMP = 68.0f;

TempController::TempController()
    : fermentationThermometer(THERMOMETER_ADDRESS),
      coolingControl(COOLING_CONTROL_PIN),
      heatingControl(HEATING_CONTROL_PIN),
      targetTemp(DEFAULT_FERM_TEMP), lastFermTempIsInError(false),
      lastFermTemp(0), lastTargetTemp(0), lastDecision(NULL),
      lastCoolingRequested(false), lastCoolingPoweredOn(false),
      lastHeatingRequested(false), lastHeatingPoweredOn(false) {
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
    if (this->lastFermTemp > this->targetTemp &&
        this->coolingControl.isRequestedOn()) {
      this->lastDecision = "Temperature within deadband. Continuing cooling.";
    } else if (this->lastFermTemp < this->targetTemp &&
        this->heatingControl.isRequestedOn()) {
      this->lastDecision = "Temperature within deadband. Continuing heating.";
    } else {
      this->lastDecision = "Temperature within deadband. No output.";
      this->coolingControl.requestOff();
      this->heatingControl.requestOff();
    }

  } else if (this->lastFermTemp < this->targetTemp) {
    this->lastDecision = "Temperature below target. Heating enabled.";
    this->coolingControl.requestOff();
    this->heatingControl.requestOn();
  } else {
    this->lastDecision = "Temperature above target. Cooling enabled.";
    this->coolingControl.requestOn();
    this->heatingControl.requestOff();
  }

  lastCoolingRequested = this->coolingControl.isRequestedOn();
  lastCoolingPoweredOn = this->coolingControl.isPoweredOn();
  lastHeatingRequested = this->heatingControl.isRequestedOn();
  lastHeatingPoweredOn = this->heatingControl.isPoweredOn();
}

void TempController::requestEnableCoolingControl(bool enabled) {
  this->coolingControl.requestOn();
}

bool TempController::getCoolingControlRequested() const {
  return this->coolingControl.isPoweredOn();
}

void TempController::requestEnableHeatingControl(bool enabled) {
  this->heatingControl.requestOn();
}

bool TempController::getHeatingControlRequested() const {
  return this->heatingControl.isPoweredOn();
}

} /* namespace Fermbot */
