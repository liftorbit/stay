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

const int statusLedPin = 25;
const int flameSensorPin = 35;
const int mainEngineIgnitionPin = 26;

RCS rcs;
Logging logging;
Pressure bmp;
Acelerometer bmi;

void launchCountdown() {
    // 10 seconds countdown
    for(int i = 0; i < 10; i++) {
        digitalWrite(statusLedPin, HIGH);
        delay(500);
        digitalWrite(statusLedPin, LOW);
        delay(500);
    }
}

bool engineIsOn() {
    return !digitalRead(flameSensorPin);
}

void mainEngineIgnition() {
    // waits for ignition and then disconnects the ignition pin
    digitalWrite(mainEngineIgnitionPin, HIGH);
    while(!engineIsOn());
    digitalWrite(mainEngineIgnitionPin, LOW);
}

void launch() {
    logging.log(launchStatus, LOG_INFO, "Main engine ignite");
    mainEngineIgnition();

    // wait engine cut off
    logging.log(launchStatus, LOG_WAIT, "Wait Main Engine Cut Off");
    while(engineIsOn) {
        delay(50);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(statusLedPin, OUTPUT);
    pinMode(mainEngineIgnitionPin, OUTPUT);
    pinMode(flameSensorPin, INPUT);

    if(!logging.begin()) {
        Serial.println("Logging not started");
        while(true);
    }

    logging.log(setupStatus, LOG_INFO, "STAY B Startup");
    logging.log(setupStatus, LOG_WAIT, "Wait RCS connection...");
    rcs.begin();

    // starting sensors
    logging.log(setupStatus, LOG_WAIT, "Starting sensors...");
    bool sensorStartupFailed = false;

    if(!bmi.begin()) {
        logging.log(setupStatus, LOG_ERROR, "Failed to start BMI160");
        sensorStartupFailed = true;
    }

    if(!bmp.begin()) {
        logging.log(setupStatus, LOG_ERROR, "Failed to start BMP280");
        sensorStartupFailed = true;
    }

    if(sensorStartupFailed) {
        logging.log(setupStatus, LOG_ERROR, "Sensor startup failure");
        rcs.sendLogs();
        while(true);
    }

    logging.log(setupStatus, LOG_SUCCESS, "All sensors started");

    rcs.sendLogs();
    bool hasReady = rcs.readyForLaunch();

    if(hasReady) {
        // preparing for launch
        logging.log(readyForLaunchStatus, LOG_INFO, "Rocket ready for launch");
        digitalWrite(statusLedPin, HIGH);
        delay(100);
        digitalWrite(statusLedPin, LOW);
        delay(100);
        digitalWrite(statusLedPin, HIGH);
        delay(100);
        digitalWrite(statusLedPin, LOW);
        delay(500);

        bool authorizedLaunch = rcs.authorizedLaunch();

        if(authorizedLaunch) {
            logging.log(readyForLaunchStatus, LOG_INFO, "Authorized launch");
            launchCountdown();

            // rocket action sequence
            launch();
        }
    } else {
        // restarting if rocket not ready for launch
        logging.log(setupStatus, LOG_INFO, "Not ready for launch, restarting");
        delay(1000);
        ESP.restart();
    }
};

void loop() {

};