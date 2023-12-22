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
#include <SD.h>
#include <SPI.h>
#include <FS.h>
#include "logging.h"

char filename[12];

char* Logging::getFilename() {
    this->fileLog.toCharArray(filename, 12);
    return filename;
}

bool Logging::begin(String filename) {
    if(!SD.begin(5)) {
        return false;
    } else if(SD.cardType() == CARD_NONE) {
        return false;
    }

    this->fileLog = "/" + filename + ".log";

    if(SD.exists(this->getFilename())) {
        SD.remove(this->getFilename());
    }

    return true;
};

void Logging::log(int type, int rocketStep, String message) {
    File log = SD.open(this->getFilename(), FILE_APPEND);
    String rawLogMsg;

    rawLogMsg.concat(millis());
    rawLogMsg.concat(',');
    rawLogMsg.concat(type);
    rawLogMsg.concat(',');
    rawLogMsg.concat(rocketStep);
    rawLogMsg.concat(',');
    rawLogMsg.concat(message);

    Serial.println(rawLogMsg);
    log.println(rawLogMsg);
    log.close();
};

void Logging::info(int rocketStep, String message) {
    this->log(LOG_INFO, rocketStep, message);
};

void Logging::error(int rocketStep, String message) {
    this->log(LOG_ERROR, rocketStep, message);
};

String Logging::getLog() {
    File log = SD.open(this->getFilename(), FILE_READ);
    String logs = log.readString();
    log.close();
    return logs;
};