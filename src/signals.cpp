#include <Arduino.h>
#include <Servo.h>
#include "signals.h"

Signals::Signals(int buzzerPin, int ledPin) {
    ledcSetup(0, 2000, 8);
    ledcAttachPin(buzzerPin, 0);

    this->buzzerPin = buzzerPin;
    this->ledPin = ledPin;
}

void Signals::waitBCS() {
    ledcWriteTone(0, 500);
    delay(100);
    ledcWriteTone(0, 700);
    delay(100);
    ledcWriteTone(0, 900);
    delay(100);
    ledcWrite(0, 0);

    for(int i = 0; i < 3; i++) {
        digitalWrite(this->ledPin, HIGH);
        delay(200);
        digitalWrite(this->ledPin, LOW);
        delay(200);
    }
}