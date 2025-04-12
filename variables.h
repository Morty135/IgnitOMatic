#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>

extern int threshold;

extern unsigned long lastPulseTime;
extern unsigned long pulseInterval;
extern unsigned long pulseWidth;

#define MAP_SIZE 10

extern int angleMap[MAP_SIZE];

void handleCommand(String cmd);

#endif