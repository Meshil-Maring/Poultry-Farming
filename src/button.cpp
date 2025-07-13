#include <Arduino.h>
#include "button.h"

const int buttonDownPin = 18;
const int buttonUpPin   = 5;

unsigned long lastDownPress = 0;
unsigned long lastUpPress   = 0;
const unsigned long debounceDelay = 50;

void initButtons() {
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonUpPin, INPUT_PULLUP);
}

bool isScrollDownPressed() {
  static bool lastState = HIGH;
  bool currentState = digitalRead(buttonDownPin);
  bool clicked = false;

  if (lastState == HIGH && currentState == LOW && (millis() - lastDownPress > debounceDelay)) {
    clicked = true;
    lastDownPress = millis();
  }
  lastState = currentState;
  return clicked;
}

bool isScrollUpPressed() {
  static bool lastState = HIGH;
  bool currentState = digitalRead(buttonUpPin);
  bool clicked = false;

  if (lastState == HIGH && currentState == LOW && (millis() - lastUpPress > debounceDelay)) {
    clicked = true;
    lastUpPress = millis();
  }
  lastState = currentState;
  return clicked;
}
