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

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <FS.h>
#include "logging.h"

bool Logging::begin() {
    if(!SD.begin(5)) {
        return false;
    } else if(SD.cardType() == CARD_NONE) {
        return false;
    }

    this->fileLog = "/" + String(random(10000, 99999)) + ".log";
    return true;
};

void Logging::log(int status, int type, String message) {
    char filename[this->fileLog.length()];
    this->fileLog.toCharArray(filename, this->fileLog.length());
    File log = SD.open(filename, FILE_APPEND);

    String rawLogMsg = String(status) + "," + type + "," + message;
    Serial.println(rawLogMsg);
    log.println(rawLogMsg);
    log.close();
};

String Logging::getLog() {
    char filename[this->fileLog.length()];
    this->fileLog.toCharArray(filename, this->fileLog.length());
    File log = SD.open(filename, FILE_READ);
    String logs = log.readString();
    log.close();
    return logs;
};