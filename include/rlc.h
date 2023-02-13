#ifndef RLC_h
#define RLC_h

#include <Arduino.h>

class RLC {
    public:
        void begin();
        void send(String text);
        String receive();
};

#endif