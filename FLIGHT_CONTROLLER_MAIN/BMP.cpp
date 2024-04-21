#include "BMP.h"

BMP::BMP() {
}

bool BMP::begin() {
  if (!bmp.begin(0x76)) {  // Verwende die Adresse 0x76
    Serial.println(F("Konnte BMP280 nicht finden, überprüfen Sie die Verkabelung und die Adresse!"));
    while (1) delay(10);
    return false;
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,      // Betriebsmodus
                  Adafruit_BMP280::SAMPLING_X2,      // Temp. sampling
                  Adafruit_BMP280::SAMPLING_X16,     // Druck sampling
                  Adafruit_BMP280::FILTER_X16,       // Filtern
                  Adafruit_BMP280::STANDBY_MS_500);  // Standby-Zeit

  // Setze startALT einmalig bei der Initialisierung
  startALT = bmp.readAltitude(1013.25);

  return true;
}

float BMP::getAltitude(float seaLevelhPa) {
  float currentAltitude = bmp.readAltitude(seaLevelhPa);
  return currentAltitude - startALT;  // Berechne die relative Höhe zur Startaltitude
}
