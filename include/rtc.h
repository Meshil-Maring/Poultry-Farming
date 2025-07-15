#ifndef RTC_H
#define RTC_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

void setupRTC();
DateTime getRTCTime(); // Optional wrapper
#endif
