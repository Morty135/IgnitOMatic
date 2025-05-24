#include "variables.h"

const int inputPin = 2;   
const int ignitionPin = 3;

volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseInterval = 0;
volatile bool newPulse = false;



void inputDetected() 
{
  unsigned long currentTime = micros();

  if (currentTime - lastPulseTime > 1000)
  {
    pulseInterval = currentTime - lastPulseTime;
    lastPulseTime = currentTime;
    newPulse = true;
  }
}



float getAdvance(float rpm) {
  for (int i = 0; i < tableLength - 1; i++) {
    if (rpm >= rpmBins[i] && rpm < rpmBins[i + 1]) {
      float t = (rpm - rpmBins[i]) / (rpmBins[i + 1] - rpmBins[i]);
      return advanceBins[i] + t * (advanceBins[i + 1] - advanceBins[i]);
    }
  }
  return advanceBins[tableLength - 1]; // return highest if rpm is too high
}



void setup() 
{
  Serial.begin(9600);
  
  pinMode(ignitionPin, OUTPUT);
  digitalWrite(ignitionPin, LOW);

  attachInterrupt(digitalPinToInterrupt(inputPin), inputDetected, FALLING);
  loadVariables();
}



void loop() 
{
  if (Serial.available()) 
  {
    String cmd = Serial.readStringUntil('\n');
    saveVariables(cmd);
  }

  if (newPulse) 
  {
    noInterrupts(); // Disable interrupts while reading shared variables
    unsigned long interval = pulseInterval;
    newPulse = false;
    interrupts();  // Re-enable interrupts

    // 1. Calculate RPM
    float rpm = 60000000.0 / interval;

    // Get desired advance angle from map
    float advanceAngle = getAdvance(rpm); // in degrees BTDC

    // Convert angle to microseconds delay
    float delayTime = (advanceAngle * 1000000.0) / (rpm * 6.0); // delay in microseconds

    // Delay and fire ignition
    delayMicroseconds((unsigned long)delayTime);

    digitalWrite(ignitionPin, HIGH);
    delayMicroseconds(pulseLength); 
    digitalWrite(ignitionPin, LOW);

    // Serial Debug
    Serial.print("RPM: "); Serial.print(rpm);
    Serial.print(" | Advance: "); Serial.print(advanceAngle);
    Serial.print("° BTDC | Delay: "); Serial.print(delayTime); Serial.println(" µs");
  }
}