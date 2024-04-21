#include "MPU6050.h"

MPU6050::MPU6050() {
}

bool MPU6050::begin() {
  if (!mpu.begin()) {
    Serial.println(F("Konnte MPU6050 nicht finden, überprüfen Sie die Verkabelung und die Adresse!"));
    while (1) delay(10);
    return false;
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  lastTime = millis();
  return true;
}

void MPU6050::update() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long currentTime = millis();
  float elapsedTime = (currentTime - lastTime) / 1000.0;  // Zeit in Sekunden
  lastTime = currentTime;

  // Berechnung der Winkel basierend auf der Beschleunigung
  angleX = atan2(a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180 / PI;
  angleY = atan2(a.acceleration.z, sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.y * a.acceleration.y)) * 180 / PI;

  // Speichern der Beschleunigungswerte (mit Tausch von X und Y)
  accX = a.acceleration.x;
  accY = a.acceleration.z;
  accZ = (a.acceleration.y + 9.81)*-1;
}


float MPU6050::getAngleX() {
  update();  // Aktualisiere die Sensorwerte
  return angleX;
}

float MPU6050::getAngleY() {
  update();  // Aktualisiere die Sensorwerte
  return angleY;
}

float MPU6050::getAccX() {
  update();  // Aktualisiere die Sensorwerte
  return accX;
}

float MPU6050::getAccY() {
  update();  // Aktualisiere die Sensorwerte
  return accY;
}

float MPU6050::getAccZ() {
  update();  // Aktualisiere die Sensorwerte
  return accZ;
}
