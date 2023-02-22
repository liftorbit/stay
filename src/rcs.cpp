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
};

int RCS::waitAuthorization() {
    if(bt.connected()) {
        if(bt.available()) {
            String confirm = bt.readString();
            bt.print(confirm);
            if(confirm == "rfl") {
                return READY_FOR_LAUNCH;
            } else if(confirm == "la") {
                return LAUNCH_AUTHORIZED;
            } else if(confirm == "na") {
                return NO_AUTHORIZED;
            }
        } else {
            return RCS_WITHOUT_DATA;
        }
    } else {
        return RCS_DISCONNECTED;
    }
}

void RCS::sendLogs() {
    bt.print(testLogging.getLog());
}