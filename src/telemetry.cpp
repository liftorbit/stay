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
#include "telemetry.h"

#define TRANSCEIVER_UART 2
#define TRANSCEIVER_BAUD_RATE 2400

HardwareSerial Transceiver(TRANSCEIVER_UART);

void Telemetry::begin() {
    Transceiver.begin(TRANSCEIVER_BAUD_RATE);
};

void Telemetry::sendLog(String log) {
    // 0x1C as log start
    Transceiver.print('\x1C');
    Transceiver.print(log);
    // 0x1B as log end
    Transceiver.print('\x1B');
};

void Telemetry::send(String message) {
    Transceiver.println(message);
};

void Telemetry::send(char code) {
    Transceiver.write(code);
};

bool Telemetry::dataAvailable() {
    return Transceiver.available() != 0;
};

String Telemetry::receive() {
    String data = Transceiver.readString();
    data.trim();

    return data;
};

void Telemetry::mecoTelemetry(bool engine, float temp, float alt, float ps, float lat, float lon, float acZ, float acX, float acY) {
    byte motorStatus[sizeof(bool)];
    byte temperature[sizeof(float)];
    byte altitude[sizeof(float)];
    byte pressure[sizeof(float)];
    byte latitude[sizeof(float)];
    byte longitude[sizeof(float)];
    byte accelerationZ[sizeof(float)];
    byte accelerationY[sizeof(float)];
    byte accelerationX[sizeof(float)];

    memcpy(motorStatus, &engine, sizeof(bool));
    memcpy(temperature, &temp, sizeof(float));
    memcpy(altitude, &alt, sizeof(float));
    memcpy(pressure, &ps, sizeof(float));
    memcpy(latitude, &lat, sizeof(float));
    memcpy(longitude, &lon, sizeof(float));
    memcpy(accelerationZ, &acZ, sizeof(float));
    memcpy(accelerationY, &acY, sizeof(float));
    memcpy(accelerationX, &acZ, sizeof(float));

    Transceiver.write('\x02');
    Transceiver.write(motorStatus, sizeof(motorStatus));
    Transceiver.write(temperature, sizeof(temperature));
    Transceiver.write(altitude, sizeof(altitude));
    Transceiver.write(pressure, sizeof(pressure));
    Transceiver.write(latitude, sizeof(latitude));
    Transceiver.write(longitude, sizeof(longitude));
    Transceiver.write(accelerationZ, sizeof(accelerationZ));
    Transceiver.write(accelerationY, sizeof(accelerationY));
    Transceiver.write(accelerationX, sizeof(accelerationX));
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

    Transceiver.write('\x02');
    Transceiver.write(motorStatus, sizeof(motorStatus));
    Transceiver.write(temperature, sizeof(temperature));
    Transceiver.write(altitude, sizeof(altitude));
    Transceiver.write(pressure, sizeof(pressure));
    Transceiver.write(acceleration, sizeof(acceleration));
};