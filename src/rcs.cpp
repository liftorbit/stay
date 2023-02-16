// RCS - Rocket Communication System

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "logging.h"
#include "rcs.h"

#include "sensors.h"

BluetoothSerial bt;
Logging logging;

GPS gps;
Logging logging;
Pressure bmp;
Acelerometer bmi;

void RCS::begin() {
    bt.begin("STAY B Rocket");

    while(!bt.connected()) {
        delay(100);
    }
};

bool RCS::parseCommand() {
    while(bt.connected()) {
        String command = bt.readString();
        command.replace("\r\n", "");

        int partIndex = 0;
        int maxParts = 2;

        String cmdParts[maxParts];
        String part = "";
        
        for(int i = 0; i < command.length(); i++) {
            if(command[i] != ',') {
                part.concat(command[i]);
            } else {
                cmdParts[partIndex] = part;
                partIndex += maxParts;
                part.clear();
            }
        }

        if(cmdParts[0] == "test") {
            this->testSystem(cmdParts[1]);
        } else if (cmdParts[0] == "close" && cmdParts[1] == "test") {
            return true;
        } else if(cmdParts[0] == "get" && cmdParts[1] == "log") {
            bt.println(logging.getLog());
        }
    }

    return false;
};

void RCS::testSystem(String system) {
    if(system == "accelerometer") {
        if(!bmi.begin()) {
            bt.println("error,BMI160 failed startup");
        } else {
            bmi.updatePosition();
            float x = bmi.getAcelerometerX();
            float y = bmi.getAcelerometerY();
            float fixAngleX = bmi.convertAxesToServoTuning(x);
            float fixAngleY = bmi.convertAxesToServoTuning(y);

            String result = "angleX(" + String(fixAngleX) + ") angleY(" + String(fixAngleY) + ")";
            bt.println("success," + result);
        }
    }
}