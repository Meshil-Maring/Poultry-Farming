#include <Arduino.h>
#include "servo_motor.h"
#include "webserver.h"

void setup() {
  Serial.begin(115200);
  setupServo();  
  setupWebServer();
}

void loop() {
  // setServoAngle(0);
  // delay(1000);

  // setServoAngle(120);
  // delay(1000);
}
