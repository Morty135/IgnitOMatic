#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>
#include <EEPROM.h>

extern const int tableLength; //20 not changable by serial
extern int rpmBins[]; //20 values for RPM
extern int advanceBins[]; //20 values for advance as an angle
extern unsigned int pulseLength; //lenght in us

void saveVariables(String cmd);
void loadVariables();

#endif