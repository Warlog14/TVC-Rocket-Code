#ifndef Rocket_h
#define Rocket_h

#include <Wire.h>
#include <Arduino.h>
#include <ESP32Servo.h>
#include "Buzzer.h"
#include "LED.h"
#include "BMP.h"
#include "MPU6050.h"
#include "TELEMETRIE.h"
#include "SDCard.h"
#include <PID_v1.h>

#define X_SERVO_PIN 13
#define Y_SERVO_PIN 2
#define PARACHUTE_SERVO_PIN 4

#define X_SERVO_MIDDLE 90
#define Y_SERVO_MIDDLE 90

#define PARACHUTE_CLOSED 80
#define PARACHUTE_EJECT 0

#define MAX_POSITIVE_SERVO_ROTATION 20
#define MAX_NEGATIVE_SERVO_ROTATION -20

class Rocket {
public:
  Rocket();
  //~Rocket(); // Der Destruktor kann nun leer sein oder ganz entfernt werden, wenn keine weiteren Aufräumarbeiten nötig sind.
  void begin();
  void padIdle();
  void poweredFlight();
  void unpoweredFlight();
  void maxApogee();
  void descent();
  void landed();
  float acceleration = 0.0;  // Store the Z axis acceleration.
  float maxAlt = 0.0;        // Store the Max altitude value.

private:
  MPU6050 imu;
  BMP bmp260;
  double angleX = 0.0, angleY = 0.0;  // Maby the problem ist, that the data from Get.accy etc ist in a format called float. but the Data that the PID controller needs is a Double. I dont know if that is compatible
  double correctedAngleX = 0.0, correctedAngleY = 0.0;

  double Setpoint = 0.0;
  double Kp = 0.9;
  double Ki = 0.005;
  double Kd = 0.03;

  Buzzer buzzer;
  LED led;
  Telemetrie tele;
  SDCard sdCard;

  Servo xServo;
  Servo yServo;
  Servo parachuteServo;

  PID xPID;  // Direkte Deklaration als Mitgliedsvariable
  PID yPID;  // Direkte Deklaration als Mitgliedsvariable

  void initializePID();
};

#endif  // Rocket_h
