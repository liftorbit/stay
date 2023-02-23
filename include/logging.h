#ifndef LOGGING_h
#define LOGGING_h

#define LOG_INFO 1
#define LOG_WAIT 2
#define LOG_SUCCESS 3
#define LOG_ERROR 4

#define S_SETUP 1
#define S_READY 2
#define S_LAUNCH 3
#define S_TANK_CHANGE 4
#define S_WAIT_ALT 5
#define S_LANDING 6
#define S_LANDED 7

#include <Arduino.h>

class Logging {
    private:
        String fileLog;

    public:
        bool begin();
        void log(int status, int type, String message);

        String getLog();
};

#endif