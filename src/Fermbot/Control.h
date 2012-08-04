/*
 * Control.h
 *
 * A control output used to trigger a power source of some sort.
 *
 *  Created on: Aug 3, 2012
 *      Author: dlouw
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#include <Arduino.h>

namespace Fermbot {

class Control {
 public:
  Control(const uint8_t digitalPin);
  virtual ~Control();

  inline uint8_t getDigitalPin() const {
    return digitalPin;
  }

  void turnOn();
  void turnOff();
  inline bool isOn() const {
    return enabled;
  }

 private:
  const uint8_t digitalPin;

  bool enabled;
};

} /* namespace Fermbot */
#endif /* CONTROL_H_ */
