#include <Arduino.h>
#include <U8g2lib.h>
#include "display.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 23, 22, U8X8_PIN_NONE);

int scrollOffset = 0;

void initDisplay() {
  u8g2.begin();
}

void showScrollList() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  int y = 24 - scrollOffset;
  int lineSpacing = 16;

  u8g2.drawStr(2, y, "Meshil1"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil2"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil3"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil4"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil5"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil6"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil7"); y += lineSpacing;
  u8g2.drawStr(2, y, "Meshil8");

  u8g2.sendBuffer();
}

void showMessage(const char* msg) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, msg);  // First line
  u8g2.sendBuffer();
}

void scrollDown() {
  scrollOffset += 16;
  if (scrollOffset > 80) scrollOffset = 80;
}

void scrollUp() {
  scrollOffset -= 16;
  if (scrollOffset < 0) scrollOffset = 0;
}
