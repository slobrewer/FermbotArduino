/*
 * Fermbot.h
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#include "Fermbot.h"
#include "Thermometer.h"

using namespace Fermbot;

DeviceAddress thermometerAddress = { 0x28, 0xFA, 0x62, 0x14, 0x04, 0x00, 0x00,
   0x99 };
Thermometer thermometer(thermometerAddress);

void setup() {
   Serial.begin(9600);

   Serial.println("Initialization complete (build 001)");
}

void loop() {
   float temperature = thermometer.readTemperatureF();

   if (temperature == -127.00) {
      Serial.println("Error reading temperature");
   } else {
      Serial.print("The current temperature is: ");
      Serial.println(temperature);
   }

   Serial.println("");

   delay(2000);
}
