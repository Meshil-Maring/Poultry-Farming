#include <Arduino.h>
#include <AccelStepper.h>
#include "stepperMotor.h"

#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 26

AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);
long forwardTarget = 30000;
long backwardTarget = 0;

void setupStepperMotor()
{
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void startMoveForward()
{
  stepper.moveTo(forwardTarget);
}

void startMoveBackward()
{
  stepper.moveTo(backwardTarget);
}

void runMotor()
{
  stepper.run();
}

bool isMoveFinished()
{
  return stepper.distanceToGo() == 0;
}

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}