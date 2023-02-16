#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

class RCS {
    public:
        void begin();
        bool parseCommand();
        void testSystem(String system);
};

#endif