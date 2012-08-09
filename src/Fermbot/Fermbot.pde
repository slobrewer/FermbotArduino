/*
 * Fermbot.h
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#include "Fermbot.h"
#include "TempController.h"

using namespace Fermbot;

#define CYCLE_TIME 1000 * 60
#define TARGET_TEMP 68.0f

TempController tempController;
char decisionBuffer[64];

void setup() {
  Serial.begin(9600);

  Serial.println("Initialization complete (build 002)");

  tempController.setTargetTemp(TARGET_TEMP);

  Serial.print("Target Temp,Error,Ferm Temp,Decision,Cooling Requested,");
  Serial.println("Cooling Powered On");
}

void logController() {
  Serial.print((double)tempController.getLastTargetTemp());
  Serial.print(",");
  Serial.print((int)tempController.isLastFermTempIsInError());
  Serial.print(",");
  Serial.print((double)tempController.getLastFermTemp());
  Serial.print(",");
  tempController.getLastDecision().toCharArray(decisionBuffer,
                                            sizeof(decisionBuffer));
  Serial.print(decisionBuffer);
  Serial.print(",");
  Serial.print(tempController.isLastCoolingRequested());
  Serial.print(",");
  Serial.println(tempController.isLastCoolingPoweredOn());
}

void loop() {
  tempController.processTempControl();
  logController();

  delay(CYCLE_TIME);
}
