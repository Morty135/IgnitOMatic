#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>
#include <EEPROM.h>

extern const int tableLength;
extern int rpmBins[];
extern int advanceBins[];
extern unsigned int pulseLength;

void saveVariables(String cmd);
void loadVariables();

#endif