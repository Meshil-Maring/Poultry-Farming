#include "rtc.h"
#include <Wire.h>
#include "display.h"
#include <RTClib.h>

RTC_DS3231 rtc;

void rtc_init()
{
  Wire.begin(21, 19); // SDA, SCL
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, setting time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void displayTimeOnScreen()
{
  DateTime now = rtc.now();
  char buffer[32];

  snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d %02d/%02d/%04d",
           now.hour(), now.minute(), now.second(),
           now.day(), now.month(), now.year());

  Serial.println(buffer);
  // Optional: if you want to display time on second line below message
  // Just make a second display function or show together
}
