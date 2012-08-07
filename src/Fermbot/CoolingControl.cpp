/*
 * CoolingControl.cpp
 *
 * A control output used to trigger power to a refrigerator
 *
 *  Created on: Aug 3, 2012
 *      Author: dlouw
 */

#include "CoolingControl.h"
#include <MsTimer2.h>

#define SHORT_CYCLE_LENGTH_MS 5ul * 60ul * 1000ul

namespace Fermbot {

CoolingControl *CoolingControl::shortCycledController = NULL;

CoolingControl::CoolingControl(const uint8_t digitalPin)
    : Control(digitalPin),
      inShortCycle(false) {
}

CoolingControl::~CoolingControl() {
}

void CoolingControl::powerOn() {
  if (!(this->isInShortCycle()) && !(this->isPoweredOn())) {
    Control::powerOn();
    setShortCycleFuse();
  }
}

void CoolingControl::setShortCycleFuse() {
  this->setInShortCycle(true);
  this->shortCycledController = this;

  MsTimer2::set(SHORT_CYCLE_LENGTH_MS, expireShortCycle);
  MsTimer2::start();
}

void CoolingControl::expireShortCycle() {
  MsTimer2::stop();

  if (shortCycledController != NULL) {
    if (shortCycledController->isRequestedOn()) {
      shortCycledController->forcePowerOn();
      shortCycledController->setShortCycleFuse();
    } else {
      shortCycledController->setInShortCycle(false);
      shortCycledController = NULL;
    }
  }
}

} /* namespace Fermbot */
