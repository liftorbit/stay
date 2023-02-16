// RCS - Rocket Communication System

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "logging.h"
#include "rcs.h"

#include "sensors.h"

BluetoothSerial bt;

GPS testGps;
Logging testLogging;
Pressure testBmp;
Acelerometer testBmi;

void RCS::begin() {
    bt.begin("STAY B Rocket");

    while(!bt.connected()) {
        delay(100);
    }
};

bool RCS::parseCommands() {
    while(bt.connected()) {
        String command = bt.readString();
        command.replace("\r\n", "");

        if(command.startsWith("test:")) {
            this->testSystem(command);
        } else if (command == "close:test") {
            return true;
        } else if(command == "get:log") {
            bt.println(testLogging.getLog());
        }
    }

    return false;
};

void RCS::testSystem(String system) {
    if(system == "test:accelerometer") {
        if(!testBmi.begin()) {
            bt.println("error,BMI160 failed startup");
        } else {
            testBmi.updatePosition();
            float x = testBmi.getAcelerometerX();
            float y = testBmi.getAcelerometerY();
            float fixAngleX = testBmi.convertAxesToServoTuning(x);
            float fixAngleY = testBmi.convertAxesToServoTuning(y);

            String result = "angleX(" + String(fixAngleX) + ") angleY(" + String(fixAngleY) + ")";
            bt.println("success," + result);
        }
    }
}