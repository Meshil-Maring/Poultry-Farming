#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebSocket ws;

const int trigPin = 22;
const int echoPin = 23;

void setupUltrasonic() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void updateUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  int percentage = ((18.2 - distance) * 100) / 15.5;
  ws.textAll(String(percentage));
}
