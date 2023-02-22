#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

#define RCS_WITHOUT_DATA 0
#define RCS_DISCONNECTED 1
#define READY_FOR_LAUNCH 2
#define LAUNCH_AUTHORIZED 3
#define NO_AUTHORIZED 4

class RCS {
    public:
        void begin();
        void sendLogs();
        int waitAuthorization();
};

#endif