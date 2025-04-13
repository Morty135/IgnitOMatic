#include "variables.h"

void handleCommand(String cmd) 
{
  cmd.trim();

  if (cmd.startsWith("SET")) 
  {
    int firstSpace = cmd.indexOf(' ');
    int secondSpace = cmd.indexOf(' ', firstSpace + 1);
    int thirdSpace = cmd.indexOf(' ', secondSpace + 1);

    // If only two parts, it's likely SET <var> <value>
    if (thirdSpace == -1) 
    {
      String varName = cmd.substring(firstSpace + 1, secondSpace);
      String valueStr = cmd.substring(secondSpace + 1);
      int intValue = valueStr.toInt();
      unsigned long longValue = valueStr.toInt();  // for pulseWidth

      if (varName == "threshold") 
      {
        threshold = intValue;
        Serial.print("threshold set to "); Serial.println(threshold);
      }
      else if (varName == "pulseWidth") 
      {
        pulseWidth = longValue;
        Serial.print("pulseWidth set to "); Serial.println(pulseWidth);
      } 
      else 
      {
        Serial.println("Unknown variable.");
      }
      return;
    }

    // If three parts, it's likely SET angleMap <index> <value>
    String varName = cmd.substring(firstSpace + 1, secondSpace);
    String indexStr = cmd.substring(secondSpace + 1, thirdSpace);
    String valueStr = cmd.substring(thirdSpace + 1);

    int index = indexStr.toInt();
    int value = valueStr.toInt();

    if (varName == "angleMap") 
    {
      if (index < 0 || index >= MAP_SIZE) 
      {
        Serial.println("Index out of range.");
        return;
      }
      angleMap[index] = value;
      Serial.print("angleMap["); Serial.print(index); Serial.print("] = "); Serial.println(value);
    }
    else 
    {
      Serial.println("Unknown array or command.");
    }
  }
  else 
  {
    Serial.println("Invalid command.");
  }
}


