#ifndef BMP_h
#define BMP_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>

class BMP {
public:
  BMP();
  bool begin();
  float getAltitude(float seaLevelhPa = 1013.25);



private:
  Adafruit_BMP280 bmp;
  float startALT;
};

#endif
// WIRD IM HAUPTCODE AUCH MIT IMU.Get.... bezeichnet