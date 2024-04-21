#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

#define BUZZER_PIN 27

class Buzzer {
public:
  Buzzer();                // Konstruktor ohne Parameter
  void playWelcomeTone();  // Funktion zum Abspielen des Willkommens-Sounds
  void playPingBeacon();
  void playSDKardAlert();
  void playTelemetryAlert();  // Funktion zum Abspielen des Ping-Beacon-Signals
};

#endif
