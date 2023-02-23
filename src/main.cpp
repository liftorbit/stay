#include <Arduino.h>
#include "logging.h"
#include "barometer.h"
#include "imu.h"
#include "rcs.h"

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
        Serial.println(F("Logging not started"));
        while(true);
    }

    logging.log(S_SETUP, LOG_INFO, F("STAY B Startup"));
    logging.log(S_SETUP, LOG_WAIT, F("Wait RCS connection..."));
    String logDate = rcs.begin();
    logging.log(S_SETUP, LOG_INFO, "Computer startup in " + logDate);

    // starting sensors
    logging.log(S_SETUP, LOG_WAIT, F("Starting sensors..."));
    bool sensorStartupFailed = false;

    if(!imu.begin()) {
        logging.log(S_SETUP, LOG_ERROR, F("Failed to start IMU"));
        sensorStartupFailed = true;
    }

    if(!barometer.begin()) {
        logging.log(S_SETUP, LOG_ERROR, F("Failed to start Barometer"));
        sensorStartupFailed = true;
    }

    if(engineIsOn()) {
        logging.log(S_SETUP, LOG_ERROR, F("Flame detected before launch"));
        sensorStartupFailed = true;
    }

    if(sensorStartupFailed) {
        logging.log(S_SETUP, LOG_ERROR, F("Sensor startup failure"));
        rcs.sendLogs();
        while(true);
    }

    imu.updatePosition();
    String x = String(imu.getAccelerometerX());
    String y = String(imu.getAccelerometerY());
    logging.log(S_SETUP, LOG_INFO, "IMU x(" + x + ") y(" + y + ")");

    String alt = String(barometer.getAltitude());
    String temp = String(barometer.getTemperature());
    logging.log(S_SETUP, LOG_INFO, "BAROMETER alt(" + alt + ") temp(" + temp + ")");
    logging.log(S_SETUP, LOG_SUCCESS, F("All sensors started"));
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
        logging.log(S_READY, LOG_INFO, F("Rocket ready for launch"));

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
            logging.log(S_READY, LOG_INFO, F("Authorized launch"));
            launchCountdown();

            // rocket action sequence
            launch();
        } else if(launchAuth == RCS_DISCONNECTED || launchAuth == NO_AUTHORIZED) {
            logging.log(S_SETUP, LOG_INFO, F("Launch not authorized, restarting"));
            delay(1000);
            ESP.restart();
        }
    } else if(readyForLaunchAuth == RCS_DISCONNECTED || readyForLaunchAuth == NO_AUTHORIZED) {
        logging.log(S_SETUP, LOG_INFO, F("Not ready for launch, restarting"));
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

    logging.log(S_LAUNCH, LOG_INFO, F("Main engine ignite"));
    mainEngineIgnition();
    logging.log(S_LAUNCH, LOG_INFO, F("Liftoff"));

    // wait engine cut off
    while(engineIsOn()) {
        delay(50);
    }

    logging.log(S_LAUNCH, LOG_INFO, F("Main engine cut off"));

    while(true) {
        int currentAltitude = static_cast<int>(barometer.getGroundDistance());
        if(currentAltitude >= maxAltitude) {
            maxAltitude = currentAltitude;
        } else {
            break;
        }
    }

    float temperature = barometer.getTemperature();

    logging.log(S_LAUNCH, LOG_INFO, "Temperature: " + String(temperature) + " °C");
    logging.log(S_LAUNCH, LOG_INFO, "Max altitude: " + String(maxAltitude) + " m");
}

void loop() {

};