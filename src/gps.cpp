#include <Arduino.h>
#include <HardwareSerial.h>
#include "gps.h"

HardwareSerial GPSSerial(1);

void GPS::begin() {
    GPSSerial.begin(9600, SERIAL_8N1, 36, 34);

    while(!GPSSerial.available()) {
        delay(100);
    }
};