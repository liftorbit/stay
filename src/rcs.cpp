// RCS - Rocket Communication System

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "rcs.h"

BluetoothSerial bt;

void RCS::begin() {
    bt.begin("STAY B Rocket");
};

void RCS::send(String text) {
    bt.println(text);
};

bool RCS::hasConnected() {
    return bt.connected();
}

String RCS::receive() {
    while (!bt.available());
    String data = bt.readString();
    data.replace("\r\n", "");

    return data;
};