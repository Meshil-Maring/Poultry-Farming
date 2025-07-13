#ifndef RTC_SETUP_H
#define RTC_SETUP_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

void rtc_init();
void displayTimeOnScreen();  

#endif
