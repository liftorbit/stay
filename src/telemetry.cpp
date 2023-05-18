#include <Arduino.h>
#include <HardwareSerial.h>
#include "telemetry.h"

const int serialRX = 16;
const int serialTX = 17;

HardwareSerial ConnSerial(1);

void Telemetry::begin() {
    ConnSerial.begin(9600);
};

void Telemetry::send(String message) {
    ConnSerial.println(message);
};

bool Telemetry::dataAvailable() {
    return ConnSerial.available() > 0;
};

String Telemetry::receive() {
    return ConnSerial.readString();
};

void Telemetry::telemetry(bool engine, float temp, float alt, float ps, float acce, float lat, float lon) {
    String sEng = String(engine);
    String sTemp = String(temp);
    String sAlt = String(alt);
    String sPs = String(ps);
    String sAcce = String(acce);
    String sLat = String(lat);
    String sLon = String(lon);

    String dataList[7] = {sEng, sTemp, sAlt, sPs, sAcce, sLat, sLon};
    String fullData = "";

    for(int i = 0; i < 7; i++) {
        fullData.concat(dataList[i]);
        fullData.concat(',');
    }

    ConnSerial.println(fullData);
};

void Telemetry::telemetry(bool engine, float temp, float alt, float ps, float acce) {
    String sEng = String(engine);
    String sTemp = String(temp);
    String sAlt = String(alt);
    String sPs = String(ps);
    String sAcce = String(acce);

    String dataList[5] = {sEng, sTemp, sAlt, sPs, sAcce};
    String fullData = "";

    for(int i = 0; i < 5; i++) {
        fullData.concat(dataList[i]);
        fullData.concat(',');
    }

    ConnSerial.println(fullData);
};