#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "solar.h"
#include "rtc.h"
#include "button_action.h"

void setup() {
  Serial.begin(115200);
  initDisplay();
  initButtons();
  initSolar();
  rtc_init();
}

void loop() {
  handleButtonScroll();  

  if (!isButtonScrollActive()) {
    bool charging = isSunlightAvailable();
    showMessage(charging ? "Charging Mode: ON" : "Charging Mode: OFF");
    displayTimeOnScreen();
  }
  delay(100);
}
