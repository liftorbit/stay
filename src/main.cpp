#include <Arduino.h>
#include "logging.h"
#include "sensors.h"
#include "rcs.h"

RCS rcs;
GPS gps;
Pressure bmp;
Acelerometer bmi;

void setup() {
    Serial.begin(9600);
    log("info", "STAY B Startup");

    rcs.begin();
    log("info", "RCS started");
    log("wait", "Wait RCS connection...");

    while (!rcs.hasConnected()) {
        delay(50);
    }

    rcs.send(log("info", "RCS connected"));

    // starting sensors
    rcs.send(log("wait", "Starting sensors..."));
    bool sensorStartupFailed = false;

    if(!bmi.begin()) {
        rcs.send(log("eror", "Failed to start BMI160"));
        sensorStartupFailed = true;
    }

    if(!bmp.begin()) {
        rcs.send(log("error", "Failed to start BMP280"));
        sensorStartupFailed = true;
    }

    if(sensorStartupFailed) {
        rcs.send(log("error", "Sensor startup failure"));
        while(true);
    }

    rcs.send(log("success", "All sensors started"));

    // starting GPS
    rcs.send(log("wait", "Wait satellites..."));
    gps.begin();

    rcs.send(log("success", "GPS started"));
};

void loop() {

};