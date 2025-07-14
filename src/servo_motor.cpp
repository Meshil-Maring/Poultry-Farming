#include <Arduino.h>
#include <ESP32Servo.h>

static Servo myServo;
const int SERVO_PIN = 27;
const int PWM_CHANNEL = 0;

void setupServo() {
  ledcSetup(PWM_CHANNEL, 50, 16);
  ledcAttachPin(SERVO_PIN, PWM_CHANNEL);
  myServo.attach(SERVO_PIN);
}

void setServoAngle(int angle) {
  myServo.write(angle);
}
