#include "variables.h"  // <-- Include at the top

void handleCommand(String cmd) {
  cmd.trim();

  if (cmd.startsWith("SET")) {
    int firstSpace = cmd.indexOf(' ');
    int secondSpace = cmd.indexOf(' ', firstSpace + 1);
    int thirdSpace = cmd.indexOf(' ', secondSpace + 1);

    String varName = cmd.substring(firstSpace + 1, secondSpace);
    String indexOrValue = cmd.substring(secondSpace + 1, thirdSpace);
    String valueStr = cmd.substring(thirdSpace + 1);

    if (varName == "threshold") {
      threshold = indexOrValue.toInt();
      Serial.print("threshold set to "); Serial.println(threshold);
      return;
    }

    int index = indexOrValue.toInt();
    int value = valueStr.toInt();

    if (index < 0 || index >= MAP_SIZE) {  // This is where you compare with the constant MAP_SIZE
      Serial.println("Index out of range.");
      return;
    }

    if (varName == "angleMap") {
      angleMap[index] = value;
      Serial.print("angleMap["); Serial.print(index); Serial.print("] = "); Serial.println(value);
    } else {
      Serial.println("Unknown variable.");
    }
  } else {
    Serial.println("Invalid command.");
  }
}

