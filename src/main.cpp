#include <Arduino.h>
#include "logging.h"
#include "rcs.h"

#define BUILTIN_LED 13

RCS rcs;


void setup() {
    Serial.begin(9600);

    pinMode(BUILTIN_LED, OUTPUT);

    log("info", "STAY B Startup");

    rcs.begin();
    log("info", "RCS started");
    log("wait", "Wait RCS connection...");

    while (!rcs.hasConnected()) {
        for(int i = 0; i < 4; i++) {
            digitalWrite(BUILTIN_LED, HIGH);
            delay(80);
            digitalWrite(BUILTIN_LED, LOW);
            delay(80);
        }

        delay(500);
    }

    rcs.send("connected");
    log("info", "RCS connected");
};

void loop() {

};