#ifndef Telemetrie_h
#define Telemetrie_h

#include "Arduino.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "MPU6050.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include "BMP.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

#define GPS_TX 17
#define GPS_RX 16
#define GPS_baud 9600

class Telemetrie {
public:
  Telemetrie();
  void begin();
  void sendTelemetry(float AngleX, float AngleY, float AccX, float AccY, float AccZ, float Altitude);
  void GPSinit(uint8_t RX, uint8_t TX, int GPSBaud);
  void sendGPS();
private:
  RF24 radio;
  MPU6050 imu;                     // Achtung: Es sieht so aus, als hättest du zwei MPU6050 Objekte (imu und mpu). Stelle sicher, dass du das richtige Objekt verwendest.
  Adafruit_MPU6050 mpu;            // MPU6050 Objekt
  const uint64_t address = 00001;  // Eindeutige Adresse für die Kommunikation
  BMP bmp260;
  TinyGPSPlus gps;
  HardwareSerial SerialGPS = HardwareSerial(1);
};
#endif