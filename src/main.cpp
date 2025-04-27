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



void setup() 
{
  Serial.begin(9600);
  
  pinMode(ignitionPin, OUTPUT);
  digitalWrite(ignitionPin, LOW);

  attachInterrupt(digitalPinToInterrupt(inputPin), inputDetected, RISING);
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

    if (interval > 0) 
    {
      digitalWrite(ignitionPin, HIGH);
      delayMicroseconds(pulseLength); 
      digitalWrite(ignitionPin, LOW);
    }
  }
}