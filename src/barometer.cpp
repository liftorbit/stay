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
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>

#include "barometer.h"

const int BMP_SCL = 13;
const int BMP_SDO = 12;
const int BMP_SDA = 14;
const int BMP_CSB = 27;

Adafruit_BMP280 bmp280(BMP_CSB, BMP_SDA, BMP_SDO, BMP_SCL);

bool Barometer::begin() {
    return bmp280.begin();
}

float Barometer::getAltitude() {
    return bmp280.readAltitude(1013.25);
};

float Barometer::getTemperature() {
    return bmp280.readTemperature();
};

float Barometer::getGroundDistance() {
    float currentAltitude = this->getAltitude();
    float distance = currentAltitude - this->groundAltitude;
    distance = (distance < 0) ? 0 : distance;
    return distance;
};

void Barometer::saveGroundAltitude() {
    this->groundAltitude = this->getAltitude();
};

float Barometer::getAverageSpeed(int periodOfTime) {
    float timeInSeconds = periodOfTime / 1000;
    float initialAltitude = this->getAltitude();
    delay(periodOfTime);
    float finalAltitude = this->getAltitude();
    float averageSpeed = (finalAltitude - initialAltitude) / timeInSeconds;
    return averageSpeed;
};