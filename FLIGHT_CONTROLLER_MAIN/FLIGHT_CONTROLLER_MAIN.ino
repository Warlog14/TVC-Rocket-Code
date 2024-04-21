#include "Buzzer.h"  // Inkludiere die Buzzer-Klasse
#include "LED.h"
#include "BMP.h"
#include "MPU6050.h"
#include "TELEMETRIE.h"
#include "SDCard.h"
#include "Rocket.h"
#include "StateMachine.h"

Buzzer buzzer;  // Erstelle ein Buzzer-Objekt
LED led;
BMP bmp260;
MPU6050 imu;
Telemetrie tele;
SDCard sdCard;
Rocket rocket;
StateMachine sm;

void setup() {
  // Stup-Code hier, wenn nötig. Der Buzzer-Konstruktor initialisiert den Pin.
  Serial.begin(115200);
  bmp260.begin();
  imu.begin();
  tele.begin();
  sdCard.begin();
  Serial.println("Rocket not begin");
  rocket.begin();
  Serial.println("Rocket begin");
  Serial.println("StateMachine not begin");
  sm.begin();
  Serial.println("StateMachine begin");
  buzzer.playWelcomeTone();
}

void loop() {

  sm.LiftupCheck(12);
  //rocket.poweredFlight();
  //rocket.descent();
}
