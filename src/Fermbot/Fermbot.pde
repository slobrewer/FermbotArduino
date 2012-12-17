/*
 * Fermbot.h
 *
 *  Created on: Aug 2, 2012
 *      Author: dlouw
 */

#include "Fermbot.h"
#include "TempController.h"
#include "SDLogger.h"

using namespace Fermbot;

#define CYCLE_TIME 1000ul * 60ul
#define TARGET_TEMP 75.0f

TempController tempController;
char decisionBuffer[64];
SDLogger logger;

void setup() {
  Serial.begin(9600);

  logger.begin();

  Serial.println("Initialization complete (build 011)");

  tempController.setTargetTemp(TARGET_TEMP);

  Serial.print("Target Temp,Error,Ferm Temp,Decision,Cooling Requested,");
  Serial.println("Cooling Powered On,Heating Requested, Heating Powered On");
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
  Serial.print(tempController.isLastCoolingPoweredOn());
  Serial.print(",");
  Serial.print(tempController.isLastHeatingRequested());
  Serial.print(",");
  Serial.println(tempController.isLastHeatingPoweredOn());
}

void loop() {
  tempController.processTempControl();
  logController();

  delay(CYCLE_TIME);
}
