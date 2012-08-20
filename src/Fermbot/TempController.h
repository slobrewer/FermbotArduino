/*
 * TempController.h
 *
 * The overall temperature controller class that sets up the components
 * and makes the temperature control decisions.
 *
 *  Created on: Aug 6, 2012
 *      Author: dlouw
 */

#ifndef TEMPCONTROLLER_H_
#define TEMPCONTROLLER_H_

#include "Thermometer.h"
#include "CoolingControl.h"
#include "HeatingControl.h"

namespace Fermbot {

class TempController {
 public:
  TempController();
  virtual ~TempController();

  float readFermTempF();
  bool isFermTempError() const;

  float getTargetTemp() const {
    return targetTemp;
  }

  void setTargetTemp(float targetTemp) {
    this->targetTemp = targetTemp;
  }

  void processTempControl();

  void requestEnableCoolingControl(bool enabled);
  bool getCoolingControlRequested() const;

  void requestEnableHeatingControl(bool enabled);
  bool getHeatingControlRequested() const;

  bool isLastCoolingPoweredOn() const {
    return lastCoolingPoweredOn;
  }

  bool isLastCoolingRequested() const {
    return lastCoolingRequested;
  }

  bool isLastHeatingPoweredOn() const {
    return lastHeatingPoweredOn;
  }

  bool isLastHeatingRequested() const {
    return lastHeatingRequested;
  }

  String getLastDecision() const {
    return lastDecision;
  }

  float getLastFermTemp() const {
    return lastFermTemp;
  }

  bool isLastFermTempIsInError() const {
    return lastFermTempIsInError;
  }

  float getLastTargetTemp() const {
    return lastTargetTemp;
  }

 private:
  Thermometer fermentationThermometer;
  CoolingControl coolingControl;
  HeatingControl heatingControl;
  float targetTemp;

  bool lastFermTempIsInError;
  float lastFermTemp;
  float lastTargetTemp;
  String lastDecision;
  bool lastCoolingRequested;
  bool lastCoolingPoweredOn;
  bool lastHeatingRequested;
  bool lastHeatingPoweredOn;
};

} /* namespace Fermbot */
#endif /* TEMPCONTROLLER_H_ */
