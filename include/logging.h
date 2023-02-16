#ifndef LOGGING_h
#define LOGGING_h

#define LOG_INFO 1
#define LOG_WAIT 2
#define LOG_SUCCESS 3
#define LOG_ERROR 4

#include <Arduino.h>
#include <SD.h>


class Logging {
    public:
        bool begin();
        void log(int status, int type, String message);

        String getLog();
};

#endif