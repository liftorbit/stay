#include <Arduino.h>
#include "logging.h"
#include "rcs.h"

RCS rcs;

void log(String type, String message) {
    rcs.begin();
    
    String logMsg = "log:" + type + "," + message;
    rcs.send(logMsg);
};