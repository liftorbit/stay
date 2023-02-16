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

    if(SD.exists("/computer.log")) {
        SD.remove("/computer.log");
    }

    return true;
}

String Logging::log(int status, int type, String message) {
    File log = SD.open("/computer.log", FILE_APPEND);

    String rawLogMsg = String(status) + "," + type + "," + message;
    Serial.println(rawLogMsg);
    log.println(rawLogMsg);
    log.close();

    return rawLogMsg;
};