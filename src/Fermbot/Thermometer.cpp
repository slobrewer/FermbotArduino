/*
 * Thermometer.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: dlouw
 */

#include "Thermometer.h"

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3
#define RESOLUTION 12

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Address of digital thermometer
DeviceAddress thermometerAddress = { 0x28, 0xFA, 0x62, 0x14, 0x04, 0x00, 0x00,
   0x99 };

bool Thermometer::initialized = false;

void Thermometer::begin() {
   if (!initialized) {
      // Start up the library
      sensors.begin();
      sensors.setResolution(thermometerAddress, RESOLUTION);

      initialized = true;
   }
}

Thermometer::Thermometer() {
   this->lastReadingError = true;
}

Thermometer::~Thermometer() {
}

bool Thermometer::isInError() {
   return this->lastReadingError;
}

float Thermometer::readTemperatureF() {
   float tempC = (float)DEVICE_DISCONNECTED;
   this->lastReadingError = true;

   sensors.requestTemperatures();

   tempC = sensors.getTempC(thermometerAddress);
   if (tempC == (float)DEVICE_DISCONNECTED) {
      this->lastReadingError = true;
   } else {
      this->lastReadingError = false;
   }

   return DallasTemperature::toFahrenheit(tempC);
}
