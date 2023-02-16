// RCS - Rocket Communication System

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "logging.h"
#include "rcs.h"

BluetoothSerial bt;
Logging testLogging;

void RCS::begin() {
    bt.begin("STAY B Rocket");

    while(!bt.connected()) {
        delay(100);
    }

    bt.print(testLogging.getLog());
};

bool RCS::readyForLaunch() {
    while(bt.connected()) {
        if(bt.available()) {
            String confirm = bt.readString();
            return confirm == "readyForLaunch";
        }
    }

    return false;
}