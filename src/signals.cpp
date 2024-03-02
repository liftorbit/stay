#include <Arduino.h>
#include <Servo.h>
#include "signals.h"

Signals::Signals(int buzzerPin, int ledPin) {
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    ledcSetup(0, 2000, 8);
    ledcAttachPin(buzzerPin, 0);

    this->buzzerPin = buzzerPin;
    this->ledPin = ledPin;
}

void Signals::simpleSignal() {
    ledcWriteTone(0, 900);
    digitalWrite(this->ledPin, HIGH);
    delay(200);
    digitalWrite(this->ledPin, LOW);
    ledcWrite(0, 0);
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

void Signals::receivedBCS() {
    for(int i = 0; i < 3; i++) {
        ledcWriteTone(0, 900);
        digitalWrite(this->ledPin, HIGH);
        delay(100);
        ledcWrite(0, 0);
        digitalWrite(this->ledPin, LOW);
        delay(100);
    }
}

void Signals::errorToStartLOG() {
    for(int i = 0; i < 3; i++) {
        ledcWriteTone(0, 1200);
        digitalWrite(this->ledPin, HIGH);
        delay(50);
        ledcWrite(0, 0);
        digitalWrite(this->ledPin, LOW);
        delay(100);
    }
}

void Signals::waitLaunchAuthorization() {
    ledcWriteTone(0, 1200);
    digitalWrite(this->ledPin, HIGH);
    delay(500);
    ledcWrite(0, 0);
    digitalWrite(this->ledPin, LOW);
}