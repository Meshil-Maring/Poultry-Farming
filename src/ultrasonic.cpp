#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebSocket ws;

const int trigPin = 12;
const int echoPin = 13;

// Define your known tank range in cm
const float maxDistance = 18.2;
const float minDistance = 2.7;

void setupUltrasonic()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 1000; // Update every 1 second

void updateUltrasonic()
{
  unsigned long now = millis();
  if (now - lastUpdate < updateInterval)
    return;

  lastUpdate = now;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  if (duration == 0)
  {
    Serial.println("Ultrasonic: No echo received");
    if (ws.count() > 0)
      ws.textAll("error");
    return;
  }

  float distance = duration * 0.034 / 2;
  distance = constrain(distance, minDistance, maxDistance);
  int percentage = round(((maxDistance - distance) * 100) / (maxDistance - minDistance));

  Serial.printf("Ultrasonic: Distance=%.2f cm, Percentage=%d%%\n", distance, percentage);
  if (ws.count() > 0)
    ws.textAll(String(percentage));
}
