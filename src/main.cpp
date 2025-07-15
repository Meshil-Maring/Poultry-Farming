#include <Arduino.h>
#include "servo_motor.h"
#include "webserver.h"
#include "stepperMotor.h"
#include "rtc.h"
#include "ultrasonic.h"

#define LIMIT_SWITCH_PIN 4

void setup()
{
  Serial.begin(115200);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  setupWebServer();
  setupServo();
  setupStepperMotor();
  setupUltrasonic();
  setupRTC();
}

void loop()
{
  updateUltrasonic();
  handleCleaning();
  delay(200);
}
