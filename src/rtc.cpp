#include "rtc.h"
#include <Wire.h>
RTC_DS3231 rtc;

void setupRTC()
{
  Wire.begin(0, 2); // SDA, SCL for ESP32

  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, setting time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set compile time
  }
}

DateTime getRTCTime()
{
  return rtc.now();
}
