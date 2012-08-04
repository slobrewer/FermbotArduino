/*
 * Thermometer.h
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#ifndef THERMOMETER_H_
#define THERMOMETER_H_
#include <OneWire.h>
#include <DallasTemperature.h>

namespace Fermbot {

class Thermometer {
 public:
  static void begin();

 private:
  static bool initialized;

 public:
  Thermometer(const DeviceAddress address);
  virtual ~Thermometer();

  bool isInError() const;
  float readTemperatureF();

 private:
  bool lastReadingError;

  // Address of digital thermometer
  DeviceAddress thermometerAddress;
};

} /* namespace Fermbot */
#endif /* THERMOMETER_H_ */
