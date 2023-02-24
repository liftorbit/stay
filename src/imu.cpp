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
#include <BMI160Gen.h>
#include <Wire.h>

#include "imu.h"

const int BMI160Address = 0x69;

bool IMU::begin() {
    Wire.begin();
    Wire.beginTransmission(BMI160Address);

    if (Wire.endTransmission () == 0) {
        return BMI160.begin(BMI160GenClass::I2C_MODE, BMI160Address);
    } else {
        return false;
    }
};

void IMU::updatePosition() {
    int rawAx, rawAy, rawAz;
    BMI160.readAccelerometer(rawAx, rawAy, rawAz);

    this->ax = this->convertRaw(rawAx);
    this->ay = this->convertRaw(rawAy);
    this->az = this->convertRaw(rawAz);
};

float IMU::convertRaw(int rawData) {
    // -45 and 45 = 90°
    float g = (rawData * 45.0) / 32768.0;
    return g;
};

int IMU::convertAxesToServoTuning(float axis) {
    float angle = map(axis, -23, 22, 0, 90);
    int servoAngle = map(angle, 0, 90, 45, 135);
    return servoAngle;
};

float IMU::getAccelerometerX() {
    return this->ax;
};

float IMU::getAccelerometerY() {
    return this->ay;
};

float IMU::getAccelerometerZ() {
    return this->az;
};