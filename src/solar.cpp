#include <Arduino.h>
#include "solar.h"

#define SOLAR_PIN 15
#define NUM_SAMPLES 10  // Number of readings to average

void initSolar() {
  pinMode(SOLAR_PIN, INPUT);
}

bool isSunlightAvailable() {
  long total = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    total += analogRead(SOLAR_PIN);
    delay(5); // Short delay between samples
  }

  float avgAdc = total / (float)NUM_SAMPLES;
  float solarVoltage = (avgAdc / 4095.0) * 3.3;

  Serial.print("Avg Solar Voltage: ");
  Serial.print(solarVoltage);
  Serial.println(" V");

  if (solarVoltage > 1.2) {  // Set threshold above noise
    Serial.println("Charging Mode: ON");
    return true;
  } else {
    Serial.println("Charging Mode: OFF");
    return false;
  }
}
