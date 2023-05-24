#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include "gps.h"

HardwareSerial GPSSerial(1);
TinyGPSPlus gps;

void GPS::begin() {
    GPSSerial.begin(9600, SERIAL_8N1, 36, 34);

    while(!GPSSerial.available()) {
        delay(100);
    }
};

void GPS::update() {
    while(GPSSerial.available()) {
        if(gps.encode(GPSSerial.read())) {
            this->lon = gps.location.lng();
            this->lat = gps.location.lat();
        }
    }
};