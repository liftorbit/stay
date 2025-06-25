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

void Signals::startupSignal() {
    digitalWrite(this->ledPin, HIGH);
    ledcWriteTone(0, 600);
    delay(500);
    ledcWriteTone(0, 800);
    delay(500);
    ledcWriteTone(0, 1000);
    delay(500);
    ledcWrite(0, 0);
    digitalWrite(this->ledPin, LOW);
    delay(500);
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