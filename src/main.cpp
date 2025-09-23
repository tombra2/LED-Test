#include <Arduino.h>

// put function declarations here:

void setup()
{

  DDRD = 0b11000000;
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(7, HIGH);
}

void loop()
{
  delay(1000);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
}
