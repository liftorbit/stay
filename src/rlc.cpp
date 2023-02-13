#include <Arduino.h>
#include <BluetoothSerial.h>
#include "rlc.h"

BluetoothSerial bt;

void RLC::begin() {
    bt.begin("STAY B Rocket");
};

void RLC::send(String text) {
    bt.println(text);
};

bool hasConnected() {
    return bt.connected();
}

String RLC::receive() {
    while (!bt.available());
    String data = bt.readString();
    data.replace("\r\n", "");

    return data;
};