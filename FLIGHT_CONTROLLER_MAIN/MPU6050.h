#ifndef MPU6050_h
#define MPU6050_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

class MPU6050 {
public:
  MPU6050();
  bool begin();
  void update();
  float getAngleX();
  float getAngleY();
  float getAccX();
  float getAccY();
  float getAccZ();

private:
  Adafruit_MPU6050 mpu;
  unsigned long lastTime;
  float angleX, angleY;
  float accX, accY, accZ;
};

#endif
