#include <Arduino.h>
#include "servo_motor.h"
#include "webserver.h"
#include "stepperMotor.h"
#include "rtc.h"

#define LIMIT_SWITCH_PIN 4

void setup()
{
  Serial.begin(115200);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  setupWebServer();
  setupRTC();
  setupServo();
  setupStepperMotor();
}

void loop()
{
  handleCleaning();
}
