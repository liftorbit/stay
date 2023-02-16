#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

class RCS {
    public:
        void begin();
        bool parseCommands();
        void testSystem(String system);
};

#endif