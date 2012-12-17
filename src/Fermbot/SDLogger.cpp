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

SDLogger::SDLogger() : sdCardInitialized(false) {
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

} /* namespace Fermbot */
