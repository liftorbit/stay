// STAY: Solid fuel propelled rocket
// Copyright (C) 2024  Liftorbit

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
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include "gps.h"

HardwareSerial GPSSerial(1);
TinyGPSPlus tinyGPS;

void GPS::begin() {
    GPSSerial.begin(9600, SERIAL_8N1, 4, 15);
};

bool GPS::isReady() {
    this->update();
    double lat = this->getLat();
    return lat <= 0 ? false : true;
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