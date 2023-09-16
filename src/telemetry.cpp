#include <Arduino.h>
#include <HardwareSerial.h>
#include "telemetry.h"

#define TRANSCEIVER_UART 2
#define TRANSCEIVER_BAUD_RATE 2400

HardwareSerial Transceiver(TRANSCEIVER_UART);

void Telemetry::begin() {
    Transceiver.begin(TRANSCEIVER_BAUD_RATE);
};

void Telemetry::send(String message) {
    Transceiver.println(message);
};

bool Telemetry::dataAvailable() {
    return Transceiver.available() != 0;
};

String Telemetry::receive() {
    String data = Transceiver.readString();
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

    Transceiver.write(motorStatus, sizeof(motorStatus));
    Transceiver.write(temperature, sizeof(temperature));
    Transceiver.write(altitude, sizeof(altitude));
    Transceiver.write(pressure, sizeof(pressure));
    Transceiver.write(acceleration, sizeof(acceleration));
    Transceiver.write(latitude, sizeof(latitude));
    Transceiver.write(longitude, sizeof(longitude));
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

    Transceiver.write(motorStatus, sizeof(motorStatus));
    Transceiver.write(temperature, sizeof(temperature));
    Transceiver.write(altitude, sizeof(altitude));
    Transceiver.write(pressure, sizeof(pressure));
    Transceiver.write(acceleration, sizeof(acceleration));
};