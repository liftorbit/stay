#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

class RCS {
    public:
        void begin();
        void testSystem(String system);
        void parseCommand(String command);
};

#endif