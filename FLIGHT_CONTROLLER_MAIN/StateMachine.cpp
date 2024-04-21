#include "StateMachine.h"

StateMachine::StateMachine() {
  Serial.println("StateMachine con");
}
void StateMachine::begin() {
  Serial.println("StateMachine begin");
  bmp260_1.begin();
  imu1.begin();
  rocket.begin();
  activeState = LAUNCH_PAD_IDLE;  // Assigned to activestatus to LAUNCH_PAD_IDLE status.
}

/*
  * ---Your instruction---

  * To switch from PadIdle to Powered Flight, a Liftup Check will be implemented.
  * This checks whether the acceleration in Z, accZ, is greater than -2. If that is the case, Powered Flight is activated.

  * To switch from Powered Flight to Unpowered Flight,
  * it is checked whether the acceleration becomes negative again. Since the fuel has been consumed, and we are no longer actively accelerating.

  * To switch from Unpowered Flight to Descent, it is checked whether the current altitude ALT is less than the Maximum Altitude MaxALT.

  * To switch from Descent to Landed, we need to check if the altitude ALT is below a certain threshold, for example, 12 meters.
*/

void StateMachine::LiftupCheck(float threshold) {      // In this function needs external parameter. this parameter is threshold value.
  switch (activeState) {                               //
    case LAUNCH_PAD_IDLE:                              // Checking if rocket is IDLE mode.
      rocket.padIdle();                                // If it true, execute the padIdle function.
      if (imu1.getAccZ() > 10) {                        // Checking if Z axis acceleration is greater than -2
        activeState = POWERD;                          // Assigns POWERD mode status to activestatus.
      }                                                //
      break;                                           //
    case POWERD:                                       // Checking if rocket is POWERD mode.
      Serial.println("LiftupCheck -> poweredFlight");  //
      rocket.poweredFlight();                          // If it true, execute the poweredFlight function.
      //Serial.println();
      if (imu1.getAccZ() < 5) {                          // Checking if Z axis acceleration is less than 0 (negative acceleration)
        activeState = UNPOWERD;                          // Assigns UNPOWERD mode status to activestatus.
      }                                                  //
      break;                                             //
    case UNPOWERD:                                       // Checking if rocket is UNPOWERD mode.
      Serial.println("LiftupCheck -> unpoweredFlight");  //
      rocket.unpoweredFlight();                          // If it true, execute the unpoweredFlight function.
      if (rocket.maxAlt > bmp260_1.getAltitude()) {      // Checking if current altitude less than maximum altitude.
        activeState = DESCENT;                           // Assigns DESCENT mode status to activestatus.
      }                                                  //
      break;                                             //
    case DESCENT:                                        // Checking if rocket is DESCENT mode.
      Serial.println("LiftupCheck -> DESCENT");          //
      rocket.descent();                         // If it true, execute the decent function and pass the threshold value.
      if (threshold > bmp260_1.getAltitude()) {          // Checking if current altitude less than threshold altitude
        activeState = LANDED;                            // Assigns LANDED mode status to activestatus.
      }                                                  //
      break;                                             //
    case LANDED:                                         // Checking if rocket is LANDED mode.
      Serial.println("LiftupCheck -> LANDED");           //
      rocket.landed();                                   // If it true, execute the land function.
      break;
  }
}