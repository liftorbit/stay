#include <Arduino.h>
#include <BMI160Gen.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "sensors.h"

const int BMI160Address = 0x69;

const int BMP_SCL = 13;
const int BMP_SDO = 12;
const int BMP_SDA = 14;
const int BMP_CSB = 27;

Adafruit_BMP280 bmp(BMP_CSB, BMP_SDA, BMP_SDO, BMP_SCL);

void Acelerometer::begin() {
    return BMI160.begin(BMI160GenClass::I2C_MODE, BMI160Address);
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

// BMP280

bool Pressure::begin() {
    return bmp.begin();
}

float Pressure::getAltitude() {
    return bmp.readAltitude(1013.25);
};

float Pressure::getTemperature() {
    return bmp.readTemperature();
};

float Pressure::getGroundDistance() {
    float currentAltitude = this->getAltitude();
    return currentAltitude -  this->groundDistance;
};

void Pressure::saveGroundAltitude() {
    this->groundAltitude = this->getAltitude();
};