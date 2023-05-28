#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include "gps.h"

HardwareSerial GPSSerial(1);
TinyGPSPlus tinyGPS;

void GPS::begin() {
    GPSSerial.begin(9600, SERIAL_8N1, 4, 15);

    while(!GPSSerial.available()) {
        delay(100);
    }
};

void GPS::update() {
    while(GPSSerial.available()) {
        if(tinyGPS.encode(GPSSerial.read())) {
            this->lon = tinyGPS.location.lng();
            this->lat = tinyGPS.location.lat();
        }
    }
};

double GPS::getLat() {
    return this->lat;
};

double GPS::getLon() {
    return this->lon;
};