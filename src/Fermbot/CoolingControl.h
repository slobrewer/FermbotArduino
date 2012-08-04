/*
 * CoolingControl.h
 *
 * A control output used to trigger power to a refrigerator
 *
 *  Created on: Aug 3, 2012
 *      Author: dlouw
 */

#ifndef COOLINGCONTROL_H_
#define COOLINGCONTROL_H_

#include "Control.h"

namespace Fermbot {

class CoolingControl : public Fermbot::Control {
 public:
  CoolingControl(const uint8_t digitalPin);
  virtual ~CoolingControl();

  virtual void powerOn();

  inline bool isInShortCycle() const {
    return this->inShortCycle;
  }

 private:
  bool inShortCycle;

  inline void setInShortCycle(bool inShortCycle) {
    this->inShortCycle = inShortCycle;
  }

  inline void forcePowerOn() {
    Control::powerOn();
  }
  static CoolingControl *shortCycledController;
  void setShortCycleFuse();
  static void expireShortCycle();
};

} /* namespace Fermbot */
#endif /* COOLINGCONTROL_H_ */
