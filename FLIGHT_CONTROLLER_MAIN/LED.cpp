#include "LED.h"

LED::LED() {
  pinMode(_pinGreen, OUTPUT);
  pinMode(_pinBlue, OUTPUT);
}

void LED::green() {
  setLED(_pinGreen, 255 * 0.1);  // 10% Intensität
  analogWrite(_pinBlue, 0);      // Blaue LED aus
}

void LED::blue() {
  analogWrite(_pinGreen, 0);    // Grüne LED aus
  setLED(_pinBlue, 255 * 0.1);  // 10% Intensität
}

void LED::greenBlue() {
  setLED(_pinGreen, 255 * 0.1);  // 10% Intensität für Grün
  setLED(_pinBlue, 255 * 0.1);   // 10% Intensität für Blau
}

void LED::setLED(int pin, int intensity) {
  analogWrite(pin, intensity);
}
