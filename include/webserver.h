#ifndef WEBSERVER_H
#define WEBSERVER_H

void setupWebServer();
void broadcastLEDStatus(bool state);
void handleCleaning();

enum CleaningState
{
    CLEAN_IDLE,
    CLEAN_FORWARD,
    CLEAN_BACKWARD
};

extern bool isCleaning;
extern CleaningState cleaningState;

#endif