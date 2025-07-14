#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "webserver.h"

#define LED_PIN 21
#define WATER_PIN 19
#define FEED_PIN 18

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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
      Serial.println("Start draning");
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
      digitalWrite(FEED_PIN, HIGH);
      ws.textAll("FEED");
    }
    else if (msg == "STOP_FEED")
    {
      digitalWrite(FEED_PIN, LOW);
      ws.textAll("STOP_FEED");
    }
  }
}

void setupWebServer()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(WATER_PIN, OUTPUT);
  pinMode(FEED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.softAP("ESP32-Hotspot", "12345678");
  Serial.println("AP IP: " + WiFi.softAPIP().toString());

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS mount failed.");
    return;
  }

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
}

void broadcastLEDStatus(bool state)
{
  ws.textAll(state ? "ON" : "OFF");
}
