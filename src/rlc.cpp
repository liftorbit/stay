#include <Arduino.h>
#include <BluetoothSerial.h>
#include "rlc.h"

BluetoothSerial bt;

void RLC::begin() {

};

void RLC::send(String text) {

};

bool hasConnected() {
    return bt.connected();
}

String RLC::receive() {

};