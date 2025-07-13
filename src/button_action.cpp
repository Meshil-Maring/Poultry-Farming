#include <Arduino.h>
#include "button_action.h"
#include "button.h"
#include "display.h"

static bool wasButtonPressed = false;
static unsigned long lastButtonTime = 0;

void handleButtonScroll() {
  if (isScrollDownPressed()) {
    Serial.println("Scroll Down");
    scrollDown();
    showScrollList();
    wasButtonPressed = true;
    lastButtonTime = millis();
  } else if (isScrollUpPressed()) {
    Serial.println("Scroll Up");
    scrollUp();
    showScrollList();
    wasButtonPressed = true;
    lastButtonTime = millis();
  }

  // Auto reset scroll view after timeout
  if (wasButtonPressed && millis() - lastButtonTime > 3000) {
    wasButtonPressed = false;
  }
}

bool isButtonScrollActive() {
  return wasButtonPressed;
}
