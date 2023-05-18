#include <Arduino.h>
#include <HardwareSerial.h>
#include "telemetry.h"

const int serialRX = 16;
const int serialTX = 17;

HardwareSerial ConnSerial(1);

void Telemetry::begin() {
    ConnSerial.begin(9600);
};

void Telemetry::send(String message) {
    ConnSerial.println(message);
};

bool Telemetry::dataAvailable() {
    return ConnSerial.available() > 0;
};