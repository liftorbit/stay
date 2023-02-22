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