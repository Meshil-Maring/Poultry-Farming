#ifndef DISPLAY_H
#define DISPLAY_H

void initDisplay();
void showScrollList();           // Scrollable list
void scrollDown();
void scrollUp();
void showMessage(const char*);   // Dynamic text (charging/time)

#endif
