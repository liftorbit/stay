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

Adafruit_BMP280 bmp280(BMP_CSB, BMP_SDA, BMP_SDO, BMP_SCL);

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

// BMP280

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