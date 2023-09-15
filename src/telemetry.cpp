#include <Arduino.h>
#include <HardwareSerial.h>
#include "telemetry.h"

// RX16, TX17
HardwareSerial ConnSerial(2);

void Telemetry::begin() {
    ConnSerial.begin(9600);
};

void Telemetry::send(String message) {
    ConnSerial.println(message);
};

bool Telemetry::dataAvailable() {
    return ConnSerial.available() != 0;
};

String Telemetry::receive() {
    String data = ConnSerial.readString();
    data.trim();

    return data;
};

void Telemetry::telemetry(bool engine, float temp, float alt, float ps, float acce, float lat, float lon) {
    // advanced telemetry 
    byte motorStatus[sizeof(bool)];
    byte temperature[sizeof(float)];
    byte altitude[sizeof(float)];
    byte pressure[sizeof(float)];
    byte acceleration[sizeof(float)];
    byte latitude[sizeof(float)];
    byte longitude[sizeof(float)];

    memcpy(motorStatus, &engine, sizeof(bool));
    memcpy(temperature, &temp, sizeof(float));
    memcpy(altitude, &alt, sizeof(float));
    memcpy(pressure, &ps, sizeof(float));
    memcpy(acceleration, &acce, sizeof(float));
    memcpy(latitude, &lat, sizeof(float));
    memcpy(longitude, &lon, sizeof(float));

    ConnSerial.write(motorStatus, sizeof(motorStatus));
    ConnSerial.write(temperature, sizeof(temperature));
    ConnSerial.write(altitude, sizeof(altitude));
    ConnSerial.write(pressure, sizeof(pressure));
    ConnSerial.write(acceleration, sizeof(acceleration));
    ConnSerial.write(latitude, sizeof(latitude));
    ConnSerial.write(longitude, sizeof(longitude));
};

void Telemetry::telemetry(bool engine, float temp, float alt, float ps, float acce) {
    // basic telemetry
    byte motorStatus[sizeof(bool)];
    byte temperature[sizeof(float)];
    byte altitude[sizeof(float)];
    byte pressure[sizeof(float)];
    byte acceleration[sizeof(float)];

    memcpy(motorStatus, &engine, sizeof(bool));
    memcpy(temperature, &temp, sizeof(float));
    memcpy(altitude, &alt, sizeof(float));
    memcpy(pressure, &ps, sizeof(float));
    memcpy(acceleration, &acce, sizeof(float));

    ConnSerial.write(motorStatus, sizeof(motorStatus));
    ConnSerial.write(temperature, sizeof(temperature));
    ConnSerial.write(altitude, sizeof(altitude));
    ConnSerial.write(pressure, sizeof(pressure));
    ConnSerial.write(acceleration, sizeof(acceleration));
};