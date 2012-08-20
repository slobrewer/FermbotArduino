/*
 * HeatingControl.h
 *
 *  Created on: Aug 19, 2012
 *      Author: dlouw
 */

#ifndef HEATINGCONTROL_H_
#define HEATINGCONTROL_H_

#include "Control.h"

namespace Fermbot {

class HeatingControl : public Fermbot::Control {
 public:
  HeatingControl(const uint8_t digitalPin);
  virtual ~HeatingControl();
};

} /* namespace Fermbot */
#endif /* HEATINGCONTROL_H_ */
