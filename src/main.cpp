// STAY: Solid fuel propelled rocket
// Copyright (C) 2023  Liftorbit

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Arduino.h>
#include <Servo.h>

#include "telemetry.h"
#include "barometer.h"
#include "logging.h"
#include "imu.h"

const int statusLedPin = 25;
const int flameSensorPin = 35;
const int mainEngineIgnitionPin = 26;

const int servoXPin = 2;
const int servoYPin = 32;

float imuAcce = 0;

IMU imu;
Logging logging;
Telemetry telemetry;
Barometer barometer;

Servo servoX;
Servo servoY;

TaskHandle_t TelemetryTHandle;

void sendTelemetry();
bool engineIsOn();
void mainEngineIgnition();
void launch();
void meco();

void setup() {
    Serial.begin(9600);

    if(!logging.begin()) {
        Serial.println(F("Logging not started"));
        while(true);
    }

    // setup status
    logging.log(S_SETUP, LOG_INFO, F("STAY Startup"));

    pinMode(statusLedPin, OUTPUT);
    pinMode(mainEngineIgnitionPin, OUTPUT);
    pinMode(flameSensorPin, INPUT);

    logging.log(S_SETUP, LOG_INFO, F("Pin mode defined"));
    logging.log(S_SETUP, LOG_WAIT, F("Wait base connection..."));

    telemetry.begin();
    String logDate = telemetry.receive();

    logging.log(S_SETUP, LOG_INFO, "Computer startup in " + logDate);
    logging.log(S_SETUP, LOG_WAIT, F("Starting sensors..."));

    if(imu.begin()) {
        imu.updatePosition();
        String imuX = String(imu.getAccelerometerX());
        String imuY = String(imu.getAccelerometerY());
        logging.log(S_SETUP, LOG_SUCCESS, F("IMU Started"));
        logging.log(S_SETUP, LOG_INFO, "IMU x(" + imuX + ") y(" + imuY + ")");
    } else {
        logging.log(S_SETUP, LOG_ERROR, F("Failed to start IMU"));
    }

    if(barometer.begin()) {
        String alt = String(barometer.getAltitude());
        String temp = String(barometer.getTemperature());
        logging.log(S_SETUP, LOG_SUCCESS, F("Barometer Started"));
        logging.log(S_SETUP, LOG_INFO, "BAROMETER alt(" + alt + ") temp(" + temp + ")");
    } else {
        logging.log(S_SETUP, LOG_ERROR, F("Failed to start Barometer"));
    }

    if(engineIsOn()) {
        logging.log(S_SETUP, LOG_ERROR, F("Flame detected before launch"));
    } else {
        logging.log(S_SETUP, LOG_SUCCESS, F("Flame sensor in operation"));
    }

    logging.log(S_SETUP, LOG_INFO, F("Sensors started"));

    servoX.attach(servoXPin);
    servoY.attach(servoYPin);
    servoX.write(90);
    servoY.write(90);

    logging.log(S_SETUP, LOG_INFO, F("Servos attached"));
    logging.log(S_AUTH, LOG_WAIT, F("Wait launch authorization..."));

    telemetry.send(logging.getLog());

    while(!telemetry.dataAvailable()) {
        digitalWrite(statusLedPin, HIGH);
        delay(100);
        digitalWrite(statusLedPin, LOW);
        delay(100);
        digitalWrite(statusLedPin, HIGH);
        delay(100);
        digitalWrite(statusLedPin, LOW);
        delay(500);
    }

    String launchAuth = telemetry.receive();

    if(launchAuth == "RLA") {
        logging.log(S_AUTH, LOG_INFO, F("Launch authorized. Countdown."));

        // 10 seconds countdown
        for(int i = 0; i < 10; i++) {
            if(!telemetry.dataAvailable()) {
                digitalWrite(statusLedPin, HIGH);
                delay(500);
                digitalWrite(statusLedPin, LOW);
                delay(500);
            } else {
                if(telemetry.receive() == "SLC") {
                    digitalWrite(statusLedPin, HIGH);
                    delay(1000);
                    digitalWrite(statusLedPin, LOW);
                    logging.log(S_SETUP, LOG_INFO, F("Stop launch countdown (SLC). Restarting"));
                    ESP.restart();
                }
            }
        }

        // launch steps
        launch();
        meco();
    } else if(launchAuth == "RLU") {
        logging.log(S_SETUP, LOG_INFO, F("Launch not authorized, restarting"));
        ESP.restart();
    }
};

void sendBasicTelemetry(void * pvParameters) {
    float pressure, alt, temp;

    for(;;) {
        pressure = barometer.getPressure();
        temp = barometer.getTemperature();
        alt = barometer.getAltitude();
        telemetry.telemetry(engineIsOn(), temp, alt, pressure, imuAcce);
        delay(100);
    }
}

bool engineIsOn() {
    return !digitalRead(flameSensorPin);
}

void mainEngineIgnition() {
    digitalWrite(mainEngineIgnitionPin, HIGH);
    while(!engineIsOn());
    digitalWrite(mainEngineIgnitionPin, LOW);
}

void launch() {
    float rawX, rawY;

    xTaskCreate(
        sendBasicTelemetry,
        "sendBasicTelemery",
        10000,
        NULL,
        1,
        &TelemetryTHandle
    );

    barometer.saveGroundAltitude();
    mainEngineIgnition();

    logging.log(S_LAUNCH, LOG_INFO, F("Main engine ignition"));

    // wait main engine cut off
    while(engineIsOn()) {
        imu.updatePosition();
        imuAcce = imu.getAccelerometerZ();
        rawX = imu.getAccelerometerX();
        rawY = imu.getAccelerometerY();

        // control TVC
        servoX.write(imu.convertAxesToServoTuning(rawX));
        servoY.write(imu.convertAxesToServoTuning(rawY));
    }
};

void meco() {
    int maxAltitude = 0, currentAltitude = 0;
    float speed, temperature;

    logging.log(S_LAUNCH, LOG_INFO, F("Main engine cut off"));

    // delete basic telemetry task
    vTaskDelete(TelemetryTHandle);

    // detach TVC servos
    servoX.write(90);
    servoY.write(90);
    servoX.detach();
    servoY.detach();

    // colecting data
    speed = barometer.getAverageSpeed(100);
    temperature = barometer.getTemperature();

    while(true) {
        currentAltitude = barometer.getGroundDistance();
        if(currentAltitude >= maxAltitude) {
            maxAltitude = currentAltitude;
        } else {
            break;
        }

        delay(100);
    }

    logging.log(S_LAUNCH, LOG_INFO, "Temperature: " + String(temperature) + " C");
    logging.log(S_LAUNCH, LOG_INFO, "Max altitude: " + String(maxAltitude) + " m");
    logging.log(S_LAUNCH, LOG_INFO, "MECO in " + String(speed) + " m/s");
};

void loop() {

};