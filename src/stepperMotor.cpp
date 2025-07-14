#include "stepperMotor.h"

// Define the stepper object here
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setupStepperMotor() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500); // Optional: for smoother motion
}

void runStepperMotor() {
  Serial.println("Stepper running");

  stepper.moveTo(30000);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000);

  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000);
}
