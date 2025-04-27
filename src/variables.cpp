#include "variables.h"

const int tableLength = 20;
int rpmBins[tableLength] = {0};
int advanceBins[tableLength] = {0};
unsigned int pulseLength = 100;



void saveVariables(String cmd) 
{


  int address = 0;

  EEPROM.put(address, pulseLength);
  address += sizeof(unsigned int);

  if (cmd.startsWith("SET_RPM:"))
  {
    
  }
  
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

