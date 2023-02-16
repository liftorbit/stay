#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

class RCS {
    public:
        void begin();
        void sendLogs();
        bool readyForLaunch();
};

#endif