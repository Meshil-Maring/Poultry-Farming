#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

void setupStepperMotor();
void startMoveForward();
void startMoveBackward();
void runMotor();
bool isMoveFinished();
void stopMotors();

#endif
