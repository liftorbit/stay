#include <Arduino.h>
#include "logging.h"

String log(String type, String message) {
    String logMsg = type + ": " + message;
    Serial.println(logMsg);
    return logMsg;
};