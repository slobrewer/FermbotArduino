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

  virtual void requestOn();
  virtual void requestOff();

  /* Has someone told us this control should be on? */
  inline bool isRequestedOn() const {
    return requestedOn;
  }

  /* Is the controlled output actually powered on? */
  inline bool isPoweredOn() const {
    return this->poweredOn;
  }

 protected:
  virtual void powerOn();
  virtual void powerOff();

  inline void setPoweredOn(bool poweredOn) {
    this->poweredOn = poweredOn;
  }

  inline void setRequestedOn(bool requestedOn) {
    this->requestedOn = requestedOn;
  }

 private:
  bool requestedOn;
  bool poweredOn;
  const uint8_t digitalPin;
};

} /* namespace Fermbot */
#endif /* CONTROL_H_ */
