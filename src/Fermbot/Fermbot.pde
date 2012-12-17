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

#define CYCLE_TIME 1000ul * 10ul
#define TARGET_TEMP 75.0f
const char *DATA_SEPARATOR = ",";

TempController tempController;
SDLogger logger;

void setup() {
   const char *HEADER =
      "Target Temp,Error,Ferm Temp,Decision,Cooling Requested,Cooling Powered On,Heating Requested,Heating Powered On";

   Serial.begin(9600);

   logger.begin();
   logger.openNewLogFile();

   Serial.println("Initialization complete (build 016)");

   tempController.setTargetTemp(TARGET_TEMP);

   logger.logln(HEADER);
}

void logController() {
   char decisionBuffer[64];

   tempController.getLastDecision().toCharArray(decisionBuffer,
      sizeof(decisionBuffer));

   logger.log((double) tempController.getLastTargetTemp());
   logger.log(DATA_SEPARATOR);
   logger.log((int) tempController.isLastFermTempIsInError());
   logger.log(DATA_SEPARATOR);
   logger.log((double) tempController.getLastFermTemp());
   logger.log(DATA_SEPARATOR);
   logger.log(decisionBuffer);
   logger.log(DATA_SEPARATOR);
   logger.log(tempController.isLastCoolingRequested());
   logger.log(DATA_SEPARATOR);
   logger.log(tempController.isLastCoolingPoweredOn());
   logger.log(DATA_SEPARATOR);
   logger.log(tempController.isLastHeatingRequested());
   logger.log(DATA_SEPARATOR);
   logger.logln(tempController.isLastHeatingPoweredOn());
}

void loop() {
   tempController.processTempControl();
   logController();

   delay(CYCLE_TIME);
}
