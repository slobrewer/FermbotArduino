/*
 * Control.cpp
 *
 * A control output used to trigger a power source of some sort.
 *
 *  Created on: Aug 3, 2012
 *      Author: dlouw
 */

#include "Control.h"

namespace Fermbot {

Control::Control(const uint8_t digitalPin)
    : digitalPin(digitalPin) {
  pinMode(this->digitalPin, OUTPUT);
}

Control::~Control() {
}

void Control::turnOn() {
  this->enabled = true;
  digitalWrite(this->digitalPin, HIGH);
}

void Control::turnOff() {
  this->enabled = false;
  digitalWrite(this->digitalPin, LOW);
}

} /* namespace Fermbot */
