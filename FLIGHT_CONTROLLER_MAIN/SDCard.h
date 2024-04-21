#ifndef SDCard_h
#define SDCard_h

#include "Arduino.h"
#include "FS.h"  // Hinzu
#include "SD.h"
#include "SPI.h"
#include "MPU6050.h"
#include "BMP.h"
#include "Buzzer.h"
#include "LED.h"

class SDCard {
public:
  SDCard();  // Keine externen Objekte als Parameter

  void begin();
  void logData();
  void logData(float AngleX, float AngleY, float AccX, float AccY, float AccZ, float Altitude);

  MPU6050 imu;  // Direkte Instanziierung
  BMP bmp260;   // Direkte Instanziierung
  Buzzer buzzer;
  LED led;

private:
  const int CS = 5;  // Chip-Select für die SD-Karte
};

#endif
