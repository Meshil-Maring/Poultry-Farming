#include <Arduino.h>
#include "servo_motor.h"
#include "webserver.h"

void setup()
{
  Serial.begin(115200);
  setupServo();
  setupWebServer();
}

void loop()
{
}
