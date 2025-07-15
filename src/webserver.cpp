#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "webserver.h"
#include "servo_motor.h"
#include "stepperMotor.h"
#include "rtc.h"

#define LED_PIN 21
#define WATER_PIN 19

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

bool isCleaning = false;
CleaningState cleaningState = CLEAN_IDLE;

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                      AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  if (type == WS_EVT_CONNECT)
  {
    Serial.println("Client connected");
    client->text(digitalRead(LED_PIN) ? "ON" : "OFF");
  }
  else if (type == WS_EVT_DATA)
  {
    String msg = "";
    for (size_t i = 0; i < len; i++)
      msg += (char)data[i];
    Serial.println("Received: " + msg);

    if (msg == "ON")
    {
      digitalWrite(LED_PIN, HIGH);
      ws.textAll("ON");
    }
    else if (msg == "OFF")
    {
      digitalWrite(LED_PIN, LOW);
      ws.textAll("OFF");
    }
    else if (msg == "FILL")
    {
      digitalWrite(WATER_PIN, HIGH);
      ws.textAll("FILL");
    }
    else if (msg == "DRAIN")
    {
      digitalWrite(WATER_PIN, LOW);
      ws.textAll("DRAIN");
    }
    else if (msg == "FEED")
    {
      setServoAngle(120);
    }
    else if (msg == "STOP_FEED")
    {
      setServoAngle(0);
    }
    else if (msg == "CLEAN")
    {
      isCleaning = true;
      startMoveForward();
      cleaningState = CLEAN_FORWARD;
    }
    else if (msg == "STOP_CLEAN")
    {
      isCleaning = false;
      stopMotors();
      cleaningState = CLEAN_IDLE;
    }
  }
}

void setupWebServer()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(WATER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.softAP("ESP32-Hotspot", "12345678");
  Serial.println("AP IP: " + WiFi.softAPIP().toString());

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS mount failed.");
    return;
  }

  // Serve current time from RTC
  server.on("/api/time", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    DateTime now = rtc.now();
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d",
             now.hour(), now.minute(), now.second());
    String json = "{\"time\": \"" + String(timeStr) + "\"}";
    request->send(200, "application/json", json); });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
}

void broadcastLEDStatus(bool state)
{
  ws.textAll(state ? "ON" : "OFF");
}

void handleCleaning()
{
  if (!isCleaning)
    return;

  runMotor();

  if (cleaningState == CLEAN_FORWARD && isMoveFinished())
  {
    startMoveBackward();
    cleaningState = CLEAN_BACKWARD;
  }
  else if (cleaningState == CLEAN_BACKWARD && isMoveFinished())
  {
    startMoveForward();
    cleaningState = CLEAN_FORWARD;
  }
}
