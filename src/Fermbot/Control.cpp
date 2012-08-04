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
    : requestedOn(false), poweredOn(false), digitalPin(digitalPin) {
  pinMode(this->digitalPin, OUTPUT);
}

Control::~Control() {
}

void Control::requestOn() {
  this->setRequestedOn(true);
  this->powerOn();
}

void Control::requestOff() {
  this->setRequestedOn(false);
  this->powerOff();
}

void Control::powerOn() {
  this->setPoweredOn(true);
  digitalWrite(this->digitalPin, HIGH);
}

void Control::powerOff() {
  this->setPoweredOn(false);
  digitalWrite(this->digitalPin, LOW);
}

} /* namespace Fermbot */
