#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED {
public:
  LED();  // Konstruktor ohne Pin-Parameter
  void green();
  void blue();
  void greenBlue();

private:
  void setLED(int pin, int intensity);
  static const int _pinGreen = 26;  // Definiere den grünen Pin als 26
  static const int _pinBlue = 25;   // Definiere den blauen Pin als 25
};

#endif
