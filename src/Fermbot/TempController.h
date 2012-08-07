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

namespace Fermbot {

class TempController {
 public:
  TempController();
  virtual ~TempController();

  float readFermentationTempF();
  bool isFermentationTempError() const;


  float getTargetTemp() const {
     return targetTemp;
  }

  void setTargetTemp(float targetTemp) {
     this->targetTemp = targetTemp;
  }

  void processTempControl();

  void requestEnableCoolingControl(bool enabled);
  bool getCoolingControlRequested() const;

 private:
  Thermometer fermentationThermometer;
  CoolingControl coolingControl;
  float targetTemp;
};

} /* namespace Fermbot */
#endif /* TEMPCONTROLLER_H_ */
