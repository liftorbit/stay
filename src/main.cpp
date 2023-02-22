#include <Arduino.h>
#include "logging.h"
#include "barometer.h"
#include "imu.h"
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
IMU imu;
Logging logging;
Barometer barometer;

void launchCountdown();
bool engineIsOn();
void mainEngineIgnition();
void launch();

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
    String logDate = rcs.begin();
    logging.log(setupStatus, LOG_INFO, "Computer startup in " + logDate);

    // starting sensors
    logging.log(setupStatus, LOG_WAIT, "Starting sensors...");
    bool sensorStartupFailed = false;

    if(!imu.begin()) {
        logging.log(setupStatus, LOG_ERROR, "Failed to start IMU");
        sensorStartupFailed = true;
    }

    if(!barometer.begin()) {
        logging.log(setupStatus, LOG_ERROR, "Failed to start Barometer");
        sensorStartupFailed = true;
    }

    if(engineIsOn()) {
        logging.log(setupStatus, LOG_ERROR, "Flame detected before launch");
        sensorStartupFailed = true;
    }

    if(sensorStartupFailed) {
        logging.log(setupStatus, LOG_ERROR, "Sensor startup failure");
        rcs.sendLogs();
        while(true);
    }

    imu.updatePosition();
    String x = String(imu.getAccelerometerX());
    String y = String(imu.getAccelerometerY());
    logging.log(setupStatus, LOG_INFO, "IMU x(" + x + ") y(" + y + ")");

    String alt = String(barometer.getAltitude());
    String temp = String(barometer.getTemperature());
    logging.log(setupStatus, LOG_INFO, "BAROMETER alt(" + alt + ") temp(" + temp + ")");
    logging.log(setupStatus, LOG_SUCCESS, "All sensors started");
    rcs.sendLogs();

    int readyForLaunchAuth = rcs.waitAuthorization();

    while(readyForLaunchAuth == RCS_WITHOUT_DATA) {
        digitalWrite(statusLedPin, HIGH);
        delay(500);
        digitalWrite(statusLedPin, LOW);
        delay(500);
        readyForLaunchAuth = rcs.waitAuthorization();
    }

    if(readyForLaunchAuth == READY_FOR_LAUNCH) {
        logging.log(readyForLaunchStatus, LOG_INFO, "Rocket ready for launch");

        int launchAuth = rcs.waitAuthorization();

        while(launchAuth == RCS_WITHOUT_DATA) {
            digitalWrite(statusLedPin, HIGH);
            delay(100);
            digitalWrite(statusLedPin, LOW);
            delay(100);
            digitalWrite(statusLedPin, HIGH);
            delay(100);
            digitalWrite(statusLedPin, LOW);
            delay(500);
            launchAuth = rcs.waitAuthorization();
        }

        if(launchAuth == LAUNCH_AUTHORIZED) {
            logging.log(readyForLaunchStatus, LOG_INFO, "Authorized launch");
            launchCountdown();

            // rocket action sequence
            launch();
        } else if(launchAuth == RCS_DISCONNECTED || launchAuth == NO_AUTHORIZED) {
            logging.log(setupStatus, LOG_INFO, "Launch not authorized, restarting");
            delay(1000);
            ESP.restart();
        }
    } else if(readyForLaunchAuth == RCS_DISCONNECTED || readyForLaunchAuth == NO_AUTHORIZED) {
        logging.log(setupStatus, LOG_INFO, "Not ready for launch, restarting");
        delay(1000);
        ESP.restart();
    }
};

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
    int maxAltitude = 0;
    barometer.saveGroundAltitude();

    logging.log(launchStatus, LOG_INFO, "Main engine ignite");
    mainEngineIgnition();
    logging.log(launchStatus, LOG_INFO, "Liftoff");

    // wait engine cut off
    while(engineIsOn()) {
        delay(50);
    }

    logging.log(launchStatus, LOG_INFO, "Main engine cut off");

    while(true) {
        int currentAltitude = static_cast<int>(barometer.getGroundDistance());
        if(currentAltitude >= maxAltitude) {
            maxAltitude = currentAltitude;
        } else {
            break;
        }
    }

    float temperature = barometer.getTemperature();

    logging.log(launchStatus, LOG_INFO, "Temperature: " + String(temperature) + " °C");
    logging.log(launchStatus, LOG_INFO, "Max altitude: " + String(maxAltitude) + " m");
}

void loop() {

};