#include <Arduino.h>
#include <BMI160Gen.h>
#include <sensors.h>

const int I2CAddress = 0x69;

void Acelerometer::begin() {
    BMI160.begin(BMI160GenClass::I2C_MODE, I2CAddress);
    while(true) {
        this->updatePosition();
        if(this->getAcelerometerX() != 0) {
            break;
        }
    }
};

void Acelerometer::updatePosition() {
    int rawAx, rawAy, rawAz;
    BMI160.readAccelerometer(rawAx, rawAy, rawAz);

    this->ax = this->convertRaw(rawAx);
    this->ay = this->convertRaw(rawAy);
};

float Acelerometer::convertRaw(int rawData) {
    // -45 and 45 = 90°
    float g = (rawData * 45.0) / 32768.0;
    return g;
};

int Acelerometer::convertAxesToServoTuning(float axis) {
    float angle = map(axis, -23, 22, 0, 90);
    int servoAngle = map(angle, 0, 90, 45, 135);
    return servoAngle;
};

float Acelerometer::getAcelerometerX() {
    return this->ax;
};

float Acelerometer::getAcelerometerY() {
    return this->ay;
};