/*
 * Fermbot.h
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#include "Fermbot.h"
#include "TempController.h"

using namespace Fermbot;

TempController tempController;

void setup() {
  Serial.begin(9600);

  Serial.println("Initialization complete (build 001)");
}

void loop() {
  float temperature = tempController.readFermentationTempF();

  if (tempController.isFermentationTempError()) {
    Serial.println("Error reading temperature");
  } else {
    Serial.print("The current temperature is: ");
    Serial.println(temperature);
  }

  Serial.println("");

  delay(2000);
}
