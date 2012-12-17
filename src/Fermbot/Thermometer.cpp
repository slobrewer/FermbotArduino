/*
 * Thermometer.cpp
 *
 * A digital thermometer class for the Dallas DS18S20 thermometer
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#include "Thermometer.h"

namespace Fermbot {

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3
#define RESOLUTION 12

// Set up the One Wire singletons
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

bool Thermometer::initialized = false;

void Thermometer::begin() {
   if (!initialized) {
      // Start up the library
      sensors.begin();

      initialized = true;
   }
}

Thermometer::Thermometer(const DeviceAddress address) {
   begin();

   memcpy(this->thermometerAddress, address, sizeof(DeviceAddress));
   sensors.setResolution(this->thermometerAddress, RESOLUTION);

   this->lastReadingError = true;
}

Thermometer::~Thermometer() {
}

bool Thermometer::isInError() const {
   return this->lastReadingError;
}

float Thermometer::readTemperatureF() {
   float tempC = (float)DEVICE_DISCONNECTED;
   this->lastReadingError = true;

   sensors.requestTemperatures();

   tempC = sensors.getTempC(thermometerAddress);
   if (tempC == (float)DEVICE_DISCONNECTED || sensors.getDeviceCount() == 0) {
      this->lastReadingError = true;
   } else {
      this->lastReadingError = false;
   }

   return DallasTemperature::toFahrenheit(tempC);
}

} /* namespace Fermbot */
