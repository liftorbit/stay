#include <Arduino.h>
#include <Servo.h>
#include "signals.h"

Signals::Signals(int buzzerPin, int ledPin) {
    ledcSetup(0, 2000, 8);
    ledcAttachPin(buzzerPin, 0);

    this->buzzerPin = buzzerPin;
    this->ledPin = ledPin;
}