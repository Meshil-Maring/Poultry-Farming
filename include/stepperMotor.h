#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>

// Define pins
#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 26

// Declare the stepper object (definition must be in .cpp file)
extern AccelStepper stepper;

void setupStepperMotor();
void runStepperMotor();

#endif
