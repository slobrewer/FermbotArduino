/*
 * SDLogger.h
 *
 *  Created on: Dec 16, 2012
 *      Author: dlouw
 */

#ifndef SDLOGGER_H_
#define SDLOGGER_H_
#include <SD.h>

namespace Fermbot {

class SDLogger {
public:
   SDLogger();
   virtual ~SDLogger();

   void begin();
   void openNewLogFile();
   File getOpenFile() {return logFile;}
   void log(const char* logMessage);
   void logln(const char* logMessage);
   void log(const double logDouble);
   void logln(const double logDouble);

private:
   boolean sdCardInitialized;
   File logFile;
};

} /* namespace Fermbot */
#endif /* SDLOGGER_H_ */
