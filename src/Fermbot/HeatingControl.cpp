/*
 * HeatingControl.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: dlouw
 */

#include "HeatingControl.h"

namespace Fermbot {

HeatingControl::HeatingControl(const uint8_t digitalPin)
    : Control(digitalPin) {
}

HeatingControl::~HeatingControl() {
}

} /* namespace Fermbot */
