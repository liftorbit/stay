#ifndef RLC_h
#define RLC_h

#include <Arduino.h>

class RLC {
    public:
        void begin();
        void send(String text);
        bool hasConnected();
        String receive();
};

#endif