/*
 * Thermometer.h
 *
 *  Created on: Aug 1, 2012
 *      Author: dlouw
 */

#ifndef THERMOMETER_H_
#define THERMOMETER_H_
#include <OneWire.h>
#include <DallasTemperature.h>

class Thermometer {
public:
   static void begin();

private:
   static bool initialized;

public:
   Thermometer();
   virtual ~Thermometer();

   bool isInError();
   float readTemperatureF();

private:
   bool lastReadingError;
};

#endif /* THERMOMETER_H_ */
