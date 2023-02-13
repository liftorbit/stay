#include <Arduino.h>
#include "logging.h"

void log(String type, String message) {
    Serial.println(type + ": " + message);
};