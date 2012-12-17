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

private:
   boolean sdCardInitialized;
};

} /* namespace Fermbot */
#endif /* SDLOGGER_H_ */
