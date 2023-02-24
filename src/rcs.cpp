// STAY B solid fuel propelled rocket
// Copyright (C) 2023  Firlast

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