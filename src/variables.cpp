#include "variables.h"

const int tableLength = 20;
int rpmBins[tableLength] = {0};
int advanceBins[tableLength] = {0};
unsigned int pulseLength = 100;



void saveVariables(String cmd) 
{
  int inputTable[tableLength * 2 + 1] = {0};

  if (cmd.startsWith("SET_VARIABLES:"))
  {
    cmd = cmd.substring(14); // removes the lenght of SET_VARIABLES:
  }

  for (size_t i = 0; i < tableLength * 2 + 1; i++)
  {
    int varlength = cmd.indexOf(",");

    String temp = cmd.substring(0, varlength);

    inputTable[i] = temp.toInt();

    Serial.println(temp);

    cmd = cmd.substring(varlength + 1);
  }

  pulseLength = inputTable[0];

  for (size_t i = 0; i < tableLength; i++)
  {
    rpmBins[i] = inputTable[i + 1];
  }
  
  for (size_t i = 0; i < tableLength; i++)
  {
    advanceBins[i] = inputTable[i + tableLength + 1];
  }
  
  int address = 0;

  EEPROM.put(address, pulseLength);
  address += sizeof(unsigned int);

  for(int i = 0; i < tableLength; i++)
  {
    EEPROM.put(address, rpmBins[i]);
    address += sizeof(int);
  }

  for(int i = 0; i < tableLength; i++)
  {
    EEPROM.put(address, advanceBins[i]);
    address += sizeof(int);
  }
}



void loadVariables()
{
  int address = 0;

  EEPROM.get(address, pulseLength);
  address += sizeof(unsigned int);

  for(int i = 0; i < tableLength; i++)
  {
    EEPROM.get(address, rpmBins[i]);
    address += sizeof(int);
  }

  for(int i = 0; i < tableLength; i++)
  {
    EEPROM.get(address, advanceBins[i]);
    address += sizeof(int);
  }
}

