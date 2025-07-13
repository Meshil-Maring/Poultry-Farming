#include "StepperMotor.h"

// Initialize the stepper object with proper mode
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setupStepperMotor() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void runStepperMotor() {
  stepper.moveTo(2048);  // One revolution
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000);

  stepper.moveTo(0);  // Rotate back
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000);
}
