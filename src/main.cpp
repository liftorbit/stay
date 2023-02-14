#include <Arduino.h>
#include "logging.h"
#include "rcs.h"
#include "sensors.h"

#define BUILTIN_LED 13

RCS rcs;
Acelerometer bmi;


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

    rcs.send(log("info", "RCS connected"));

    // starting sensors
    rcs.send(log("wait", "Starting sensors..."));
    bmi.begin();
};

void loop() {

};