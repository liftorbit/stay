// RCS - Rocket Communication System

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "logging.h"
#include "rcs.h"

BluetoothSerial bt;
Logging testLogging;

String RCS::begin() {
    bt.begin(F("STAY B Rocket"));

    while(!bt.connected()) {
        delay(100);
    }

    return bt.readString();
};

int RCS::waitAuthorization() {
    if(bt.connected()) {
        if(bt.available()) {
            String confirm = bt.readString();
            bt.print(confirm);
            if(confirm == F("rfl")) {
                return READY_FOR_LAUNCH;
            } else if(confirm == F("la")) {
                return LAUNCH_AUTHORIZED;
            } else if(confirm == F("na")) {
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