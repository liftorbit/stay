#include <Arduino.h>
#include "logging.h"
#include "sensors.h"
#include "rcs.h"

const int setupStatus = 1;
const int readyForLaunchStatus = 2;
const int launchStatus = 3;
const int tankChangeStatus = 4;
const int waitAltitudeStatus = 5;
const int landingStatus = 6;
const int landedStatus = 7;

RCS rcs;
GPS gps;
Pressure bmp;
Acelerometer bmi;
Logging logging;

void setup() {
    Serial.begin(9600);
    
    if(!logging.begin()) {
        Serial.println("Logging not started");
        while(true);
    }

    logging.log(setupStatus, "info", "STAY B Startup");

    rcs.begin();
    logging.log(setupStatus, "info", "RCS started");
    logging.log(setupStatus, "wait", "Wait RCS connection...");

    while (!rcs.hasConnected()) {
        delay(50);
    }

    rcs.send(logging.log(setupStatus, "info", "RCS connected"));

    // starting sensors
    rcs.send(logging.log(setupStatus, "wait", "Starting sensors..."));
    bool sensorStartupFailed = false;

    if(!bmi.begin()) {
        rcs.send(logging.log(setupStatus, "error", "Failed to start BMI160"));
        sensorStartupFailed = true;
    }

    if(!bmp.begin()) {
        rcs.send(logging.log(setupStatus, "error", "Failed to start BMP280"));
        sensorStartupFailed = true;
    }

    if(sensorStartupFailed) {
        rcs.send(logging.log(setupStatus, "error", "Sensor startup failure"));
        while(true);
    }

    rcs.send(logging.log(setupStatus, "success", "All sensors started"));

    // starting GPS
    rcs.send(logging.log(setupStatus, "wait", "Wait satellites..."));
    gps.begin();
    rcs.send(logging.log(setupStatus, "success", "GPS started"));
};

void loop() {

};