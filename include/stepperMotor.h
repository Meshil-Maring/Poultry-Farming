#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>

// Define pins
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

// Create AccelStepper object in HALF4WIRE mode
extern AccelStepper stepper;

void setupStepperMotor();
void runStepperMotor();

#endif
