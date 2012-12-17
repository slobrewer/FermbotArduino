/*
 * SDLogger.cpp
 *
 *  Created on: Dec 16, 2012
 *      Author: dlouw
 */

#include "SDLogger.h"

namespace Fermbot {

#define HARDWARE_CS_PIN 10
#define SD_CHIP_SELECT_PIN 4

const char* LOG_NAME_FORMAT = "%08d.log";
const long LOG_NAME_LENGTH = 13;
const long MAX_LOG_NUMBER = 100000000;

SDLogger::SDLogger() :
   sdCardInitialized(false), logFile() {
}

SDLogger::~SDLogger() {
}

void SDLogger::begin() {
   Serial.print("Initializing SD card...");
   // make sure that the default chip select pin is set to
   // output, even if you don't use it:
   pinMode(HARDWARE_CS_PIN, OUTPUT);

   // see if the card is present and can be initialized:
   if (!SD.begin(SD_CHIP_SELECT_PIN)) {
      sdCardInitialized = false;
      Serial.println("Card failed, or not present");
   } else {
      sdCardInitialized = true;
      Serial.println("Card initialized.");
   }
}

void SDLogger::openNewLogFile() {
   char logFileName[LOG_NAME_LENGTH] ;
   int logNumber = 0;

   // Iterate to get to the first unused log file
   for (sprintf(logFileName, LOG_NAME_FORMAT, logNumber);
      logNumber < MAX_LOG_NUMBER && SD.exists(logFileName);
      logNumber++, logNumber < MAX_LOG_NUMBER &&
      sprintf(logFileName, LOG_NAME_FORMAT, logNumber)) {
   }

   if (logNumber >= MAX_LOG_NUMBER) {
      Serial.println("Failed to create new log file.  There are already too many existing log files.");
      return;
   }

   logFile = SD.open(logFileName, FILE_WRITE);
   if (logFile) {
      Serial.print("Logging to log file: ");
      Serial.println(logFileName);
   }
   else {
      Serial.print("Failed to open new log file: ");
      Serial.println(logFileName);
      return;
   }
}

void SDLogger::log(const char* logMessage) {
   Serial.print(logMessage);
   logFile.print(logMessage);
}

void SDLogger::logln(const char* logMessage) {
   Serial.println(logMessage);
   logFile.println(logMessage);
   logFile.flush();
}

void SDLogger::log(const double logDouble) {
   Serial.print(logDouble);
   logFile.print(logDouble);
}

void SDLogger::logln(const double logDouble) {
   Serial.println(logDouble);
   logFile.println(logDouble);
   logFile.flush();
}

} /* namespace Fermbot */
