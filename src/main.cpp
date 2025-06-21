// STAY: Solid fuel propelled rocket
// Copyright (C) 2024  Liftorbit

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
#include "gps.h"
#include "signals.h"

#define WAIT_DATE '\x30'
#define LOG_SETUP_ERROR '\x31'
#define TEST_SENSORS '\x32'
#define CMD_OK '\x33'
#define CMD_OK_RET '\x34'
#define CMD_INVALID '\x35'

const int buzzerPin = 33;
const int statusLedPin = 25;
const int flameSensorPin = 35;
const int mainEngineIgnitionPin = 26;

const int servoXPin = 2;
const int servoYPin = 32;

IMU imu;
GPS gps;
Logging logging;
Telemetry telemetry;
Barometer barometer;

Signals signals(buzzerPin, statusLedPin);

Servo servoX;
Servo servoY;

TaskHandle_t TelemetryTHandle;

void testSensors();
void handleCommands();
void sendBasicTelemetry(void * pvParameters);
void sendAdvancedTelemetry(void * pvParameters);
bool engineIsOn();
void mainEngineIgnition();
void launch();
void meco();

void setup() {
    pinMode(mainEngineIgnitionPin, OUTPUT);
    pinMode(flameSensorPin, INPUT);

    Serial.begin(9600);
    telemetry.begin();

    signals.startupSignal();

    // wait connection
    while(true) {
        telemetry.send(F("SCS"));

        for(int i = 0; i < 5; i++) {
            if(!telemetry.dataAvailable()) {
                signals.waitBCS();
            } else {
                break;
            }

            delay(1000);
        }

        if(telemetry.dataAvailable() && telemetry.receive() == F("BCS")) {
            signals.receivedBCS();
            break;
        }
    }

    telemetry.send(WAIT_DATE);

    // wait date to use in log file
    while(!telemetry.dataAvailable()) {
        signals.simpleSignal();
        delay(500);
    }

    String logDate = telemetry.receive();

    if(!logging.begin(logDate)) {
        telemetry.send(LOG_SETUP_ERROR);        
        while(true) {
            signals.errorToStartLOG();
            delay(1000);
        };
    }

    telemetry.send(TEST_SENSORS);
    logging.info(S_SETUP, F("STAY Startup"));
    logging.info(S_SETUP, F("Starting sensors..."));

    if(imu.begin()) {
        logging.info(S_SETUP, F("IMU Started"));
    } else {
        logging.error(S_SETUP, F("Failed to start IMU"));
    }

    if(barometer.begin()) {
        logging.info(S_SETUP, F("Barometer Started"));
    } else {
        logging.error(S_SETUP, F("Failed to start Barometer"));
    }

    if(engineIsOn()) {
        logging.error(S_SETUP, F("Flame detected before launch"));
    } else {
        logging.info(S_SETUP, F("Flame sensor in operation"));
    }

    logging.info(S_SETUP, F("Sensors started"));

    gps.begin();
    logging.info(S_SETUP, F("GPS started"));

    servoX.attach(servoXPin);
    servoY.attach(servoYPin);
    servoX.write(90);
    servoY.write(90);

    logging.info(S_SETUP, F("TVC pins attached"));
    logging.info(S_SETUP, "Starting Command Mode ");

    handleCommands();
};

void testSensors() {
    logging.info(S_SETUP, "Start Rocket Sensors Test");

    // Testing IMU
    logging.info(S_SETUP, "Testing IMU...");

    imu.updatePosition();
    String imuX = String(imu.getAccelerometerX());
    String imuY = String(imu.getAccelerometerY());
    logging.info(S_SETUP, "IMU [ x(" + imuX + ") y(" + imuY + ") ]");
    
    // Testing Barometer
    logging.info(S_SETUP, "Testing Barometer...");

    String alt = String(barometer.getAltitude());
    String temp = String(barometer.getTemperature());
    logging.info(S_SETUP, "BAROMETER [ alt(" + alt + ") temp(" + temp + ") ]");

    // Test Flame Detector
    logging.info(S_SETUP, "Testing Flame Sensor...");

    if(engineIsOn()) {
        logging.error(S_SETUP, F("Flame detected before startup"));
    } else {
        logging.info(S_SETUP, F("Flame sensor in operation"));
    }

    // Test GPS
    logging.info(S_SETUP, "Testing GPS...");
    bool isReady = gps.isReady();
    
    if(isReady) {
        logging.error(S_SETUP, "GPS is not ready");
    } else {
        logging.info(S_SETUP, "GPS is ready");
    }

    logging.info(S_SETUP, "Rocket Sensors Test finished");
}

void handleCommands() {
    while (true) {
        while(!telemetry.dataAvailable()) {
            signals.simpleSignal();
            delay(1500);
        }

        String command = telemetry.receive();

        if(command == "RLA") {
            logging.info(S_AUTH, F("Launch authorized. Countdown."));

            // 10 seconds countdown
            for(int i = 0; i < 10; i++) {
                if(!telemetry.dataAvailable()) {
                    digitalWrite(statusLedPin, HIGH);
                    delay(500);
                    digitalWrite(statusLedPin, LOW);
                    delay(500);
                } else if(telemetry.receive() == "SLC") {
                    digitalWrite(statusLedPin, HIGH);
                    delay(1000);
                    digitalWrite(statusLedPin, LOW);
                    logging.info(S_SETUP, F("Stop launch countdown (SLC). Restarting"));
                    ESP.restart();
                }
            }

            logging.info(S_AUTH, F("Start rocket launch steps"));

            // launch steps
            launch();
            meco();
        } else if(command == "RESTART") {
            telemetry.send(CMD_OK);
            logging.info(S_SETUP, F("Restarting"));
            ESP.restart();
        } else if(command == "TEST") {
            testSensors();
            telemetry.send(CMD_OK);
        } else if(command == "GETLOG") {
            telemetry.send(CMD_OK_RET);
            telemetry.sendLog(logging.getLog());
        } else {
            telemetry.send(CMD_INVALID);
        }
    }
}

void sendBasicTelemetry(void * pvParameters) {
    // 0x01 used as telemetry data start indicator
    telemetry.send("\x01");

    float pressure, alt, temp, accel;

    for(;;) {
        imu.updatePosition();
        accel = imu.getAccelerometerZ();

        pressure = barometer.getPressure();
        temp = barometer.getTemperature();
        alt = barometer.getGroundDistance();

        telemetry.telemetry(engineIsOn(), temp, alt, pressure, accel);
        delay(100);
    }
}

void sendAdvancedTelemetry(void * pvParameters) {
    // 0x01 used as telemetry data start indicator
    telemetry.send("\x01");

    float pressure, alt, temp, accel;
    double lat, lon;

    for(;;) {
        gps.update();
        lat = gps.getLat();
        lon = gps.getLon();

        imu.updatePosition();
        accel = imu.getAccelerometerZ();

        pressure = barometer.getPressure();
        temp = barometer.getTemperature();
        alt = barometer.getGroundDistance();

        telemetry.telemetry(engineIsOn(), temp, alt, pressure, accel, lat, lon);
        delay(500);
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
    barometer.saveGroundAltitude();

    xTaskCreate(
        sendBasicTelemetry,
        "sendBasicTelemery",
        10000,
        NULL,
        1,
        &TelemetryTHandle
    );

    mainEngineIgnition();

    logging.info(S_LAUNCH, F("Main engine ignition"));

    // wait main engine cut off
    while(engineIsOn()) {
        imu.updatePosition();
        rawX = imu.getAccelerometerX();
        rawY = imu.getAccelerometerY();

        // control TVC
        servoX.write(imu.rawToServoAngle(rawX));
        servoY.write(imu.rawToServoAngle(rawY));
        delay(50);
    }
};

void meco() {
    int maxAltitude = 0, currentAltitude = 0;
    float speed, temperature, pressure;

    logging.info(S_MECO, F("Main engine cut off"));

    // delete basic telemetry task
    vTaskDelete(TelemetryTHandle);

    // create advanced telemetry task
    xTaskCreate(
        sendAdvancedTelemetry,
        "sendAdvancedTelemetry",
        10000,
        NULL,
        1,
        &TelemetryTHandle
    );

    // detach TVC servos
    servoX.write(90);
    servoY.write(90);
    servoX.detach();
    servoY.detach();

    // colecting data
    speed = barometer.getAverageSpeed(100);
    temperature = barometer.getTemperature();
    pressure = barometer.getPressure();

    // detecting free fall
    float acceZ = imu.getAccelerometerZ();

    while(true) {
        if(acceZ <= 0) {
            break;
        }

        acceZ = imu.getAccelerometerZ();
        delay(100);
    }

    logging.info(S_MECO, "Free fall started");
    
    double lat = gps.getLat();
    double lon = gps.getLon();

    logging.info(S_MECO, "Rocket speed in MECO: " + String(speed));
    logging.info(S_MECO, "Temperature: " + String(temperature));
    logging.info(S_MECO, "Pressure: " + String(pressure));
    logging.info(S_MECO, "Max altitude: " + String(maxAltitude));
    logging.info(S_MECO, "Latitude: " + String(lat));
    logging.info(S_MECO, "Longitude: " + String(lon));
    logging.info(S_MECO, "MECO finished");
};

void loop() {

};