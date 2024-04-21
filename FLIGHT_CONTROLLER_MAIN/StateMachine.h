#ifndef StateMachine_h
#define StateMachine_h

#include <Arduino.h>
#include "Rocket.h"
#include "Buzzer.h"
#include "LED.h"
#include "BMP.h"
#include "MPU6050.h"
#include "TELEMETRIE.h"
#include "SDCard.h"

enum State {  // We save the state of every task. This means, if we call the function, we saved the function state in activestate.
  LAUNCH_PAD_IDLE,
  POWERD,
  UNPOWERD,
  DESCENT,
  LANDED
};

class StateMachine {
public:
  StateMachine();
  void LiftupCheck(float threshold);
  void begin();
private:
  Buzzer buzzer;
  LED led;
  MPU6050 imu1;
  BMP bmp260_1;
  Telemetrie tele;
  SDCard sdCard;
  Rocket rocket;

  State activeState;  // We save the state of every task. This means, if we call the function, we saved the function state in activestate.
};
#endif