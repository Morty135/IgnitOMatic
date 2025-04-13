#include "variables.h"

const int coilInputPin = A1;
const int ignitionPin = 2;

int threshold = 250;

bool prevHigh = false;
unsigned long lastPulseTime = 0;
unsigned long pulseInterval = 0;
unsigned long pulseWidth = 100;
bool newPulse = false;

int rpmMap[MAP_SIZE] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
int angleMap[MAP_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //when 0 the offset is 22-24

void setup() 
{
  Serial.begin(9600);
  pinMode(ignitionPin, OUTPUT);
  digitalWrite(ignitionPin, LOW);
}

void loop() 
{
  if (Serial.available()) 
  {
    String cmd = Serial.readStringUntil('\n');
    handleCommand(cmd);
  }
  
  int analogVal = analogRead(coilInputPin);
  bool isHigh = analogVal > threshold;

  if (isHigh && !prevHigh) 
  {
    unsigned long currentTime = micros();

    if (currentTime - lastPulseTime > 1000) 
    {
      pulseInterval = currentTime - lastPulseTime;
      lastPulseTime = currentTime;
      newPulse = true;
    }
  }

  prevHigh = isHigh;

  if (newPulse) 
  {
    newPulse = false;

    if (pulseInterval > 0) 
    {
      unsigned long rpm = 60000000UL / pulseInterval;
      Serial.print("RPM: ");
      Serial.println(rpm);

      //Get desired advance angle (degrees)
      float angle = getInterpolatedAngle(rpm);

      //Convert angle to delay in µs: delay = deg * (60,000,000 / RPM / 360)
      unsigned long delayMicros = angle * (166.67 / rpm);

      delayMicroseconds(delayMicros);

      //Fire ignition
      digitalWrite(ignitionPin, HIGH);
      delayMicroseconds(pulseWidth);  // coil pulse width
      digitalWrite(ignitionPin, LOW);
    }
  }
}

//Interpolate ignition angle based on RPM
float getInterpolatedAngle(unsigned long rpm) 
{
  if (rpm <= rpmMap[0]) return angleMap[0];
  if (rpm >= rpmMap[MAP_SIZE - 1]) return angleMap[MAP_SIZE - 1];

  for (int i = 0; i < MAP_SIZE - 1; i++) 
  {
    if (rpm >= rpmMap[i] && rpm < rpmMap[i + 1]) 
    {
      int rpmLow = rpmMap[i];
      int rpmHigh = rpmMap[i + 1];
      int angleLow = angleMap[i];
      int angleHigh = angleMap[i + 1];

      float t = (float)(rpm - rpmLow) / (rpmHigh - rpmLow);
      return angleLow + (angleHigh - angleLow) * t;
    }
  }

  return angleMap[0]; // fallback
}

