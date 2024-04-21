#include "Rocket.h"

Rocket::Rocket()
  : xPID(&angleX, &correctedAngleX, &Setpoint, 0.6, 0.04, 0.5, DIRECT), yPID(&angleY, &correctedAngleY, &Setpoint, 0.6, 0.04, 0.5, DIRECT) {
}

void Rocket::begin() {
  // Servos anhängen und initialisieren
  Serial.println("Rocket inside  begin");
  xServo.attach(X_SERVO_PIN);
  yServo.attach(Y_SERVO_PIN);
  parachuteServo.attach(PARACHUTE_SERVO_PIN);

  // Servos in die Mittelposition bringen und Fallschirm schließen
  xServo.write(X_SERVO_MIDDLE);
  yServo.write(Y_SERVO_MIDDLE);
  parachuteServo.write(PARACHUTE_CLOSED);

  bmp260.begin();
  imu.begin();
  tele.begin();
  sdCard.begin();

  // Initialisierung des PID-Reglers
  initializePID();
}

// Der Destruktor ist nun nicht mehr notwendig, da keine dynamische Speicherverwaltung verwendet wird
// Rocket::~Rocket() {}
// We don't need to map the angle. Adding +90 to the output is OK.

void Rocket::initializePID() {
  angleX = double(imu.getAngleX());  // Diese Werte sollten von Ihrem MPU6050-Sensor aktualisiert werden
  angleY = double(imu.getAngleY());
  // PID-Objekte sind bereits initialisiert, hier setzen wir nur den Modus
  xPID.SetMode(AUTOMATIC);
  yPID.SetMode(AUTOMATIC);
  xPID.SetOutputLimits(-5, 5);
  yPID.SetOutputLimits(-5, 5);
}

/*
  * ---Your instruction---
  
  * padIdle()
  * In pad idle, the rocket must read the acceleration in Z direction Accz and turn the LED to green.
*/
void Rocket::padIdle() {
  acceleration = imu.getAccZ();  // Read the acceleration in Z axis.
  led.green();                   // Turn on the green LED.
  Serial.println("Rocket padIdle");
}

/*
  * ---Your instruction---

  * Powered Flight()
  * This is the most important of the functions because it should control the servos via a PID controller. It is important that the angle from GetAngleX and GetAngleY is read, and then modified by the PID. The output value should then be passed to the Xservo and Yservo. It is very important that no matter what value comes from the PID controller, the servos never exceed +5° or -5°. These are also assigned as variables called MAX_POSITIVE_SERVO_ROTATION and MAX_NEGATIVE_SERVO_ROTATION. Also,
  * Sdcard.logData and Send Telemetry must be executed.
*/

void Rocket::poweredFlight() {
  Serial.println("rocket inside powerflight");
  xServo.attach(X_SERVO_PIN);
  yServo.attach(Y_SERVO_PIN);
  // Winkel auslesen
  // Reading the X&Y axis acceleration.

  angleX = double(imu.getAngleX());  // Diese Werte sollten von Ihrem MPU6050-Sensor aktualisiert werden
  angleY = double(imu.getAngleY());
  // PID-Update und Begrenzung
  // Calculating the XPID and YPID values.
  xPID.Compute();
  yPID.Compute();

  Serial.println("Only debug purposes \t getAngleX " + String(imu.getAngleX()) + " \t getAngleY " + String(imu.getAngleY()) + " \t PID angleX " + String(correctedAngleX + 90) + " \t PIDangleY " + String(correctedAngleY + 90));
  // Schreibe die berechneten Werte an die Servos
  xServo.write(int(correctedAngleX + 90));
  yServo.write(int(correctedAngleY + 90));
  sdCard.logData(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());      // Save the data in SD card.
  tele.sendTelemetry(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());  // Send that data through telemetry.
}

/*
  * ---Your instruction---

  * Unpowered Flight()
  * In this step, Sdcard.LogData and tele.SendTelemetry must be executed. Also, it must be calculated whether the maximum altitude MaxAlt > current height ALT. This should be done via the barometer functions.
*/
void Rocket::unpoweredFlight() {
  sdCard.logData(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());      // Save the data in SD card.
  tele.sendTelemetry(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());  // Send that data through telemetry.
  float Altitude = bmp260.getAltitude();                                                                                    // Read the current altitude.
  if (Altitude > maxAlt) {                                                                                                  // Checking if the current altitude value is greater than the maximum altitude value.
    maxAlt = Altitude;                                                                                                      // If is it true. Update the Max altitude value.
  }
}

/*
  * ---Your instruction---

  * Descent()
  * Here, the Data log function should continue to be executed as well as the tele.Send Telemetry function. Also, a calculation must be made whether the current height falls below a THRESHOLD. If the THRESHOLD is undercut, then the Parachute Servo should be given the value for Parachute Eject.
*/
void Rocket::descent() {
  parachuteServo.attach(PARACHUTE_SERVO_PIN);                                                                               // In this function needs external parameter. this parameter is threshold value.
  sdCard.logData(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());      // Save the data in SD card.
  tele.sendTelemetry(imu.getAngleX(), imu.getAngleY(), imu.getAccX(), imu.getAccY(), imu.getAccZ(), bmp260.getAltitude());  // Send that data through telemetry.
  float Altitude = bmp260.getAltitude();                                                                                    // Read the current altitude.
  if (Altitude < 50) {                                                                                                      // Checking if current altitude value is less than threshold altitude value.
    parachuteServo.write(PARACHUTE_EJECT);                                                                                  // If it's true. write the parachuteservo to parachute eject value.
  }
}

/*
  * ---Your instruction---

  * Landed()
  * In the Landed function, the buzzer.PlayPingBeacon should be played.
*/
void Rocket::landed() {
  buzzer.playPingBeacon();
  tele.sendGPS();
  led.greenBlue();  // Playing the PingBeacon tone in buzzer.
}
