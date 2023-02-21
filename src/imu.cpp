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

float IMU::getAcelerometerX() {
    return this->ax;
};

float IMU::getAcelerometerY() {
    return this->ay;
};