#ifndef LOGGING_h
#define LOGGING_h

#include <Arduino.h>
#include <SD.h>

class Logging {
    public:
        bool begin();
        String log(int status, String type, String message);
};

#endif