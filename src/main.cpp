#include <Arduino.h>

// pin definitions
#define COMCATHODE1 12 // common cathode 1
#define COMCATHODE2 13 // common cathode 2
#define SWITCHPIN A2
#define SWITCHPIN2 A3
#define BUZZER 11
// push button

#define NUMSEGMENTS 7 // Nr of segments of Seven Segment Display (SSD)
#define NUMSIGNS 16   // Nr of Signs to be displayed (0..4)

boolean swPressed = false;  // flag if switch was pressed
boolean swPressed2 = false; // flag if switch was pressed
// function declaration for setting segments of SSD for a specific sign
void setSegments(int signcount);

// pins connected to segments a-g (anodes) in this sequence (see myShield Schematic)
int SegmentPins[] = {4, 6, 2, 3, 5, 8, 7};

// Character Counter, start with Zero
int charcount = 0;

// definition of characters for displaying
byte digits[NUMSIGNS][NUMSEGMENTS] = {
    // a  b  c  d  e  f  g
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}, // 9
    {1, 1, 1, 0, 1, 1, 1}, // A
    {0, 0, 1, 1, 1, 1, 1}, // b
    {1, 0, 0, 1, 1, 1, 0}, // C
    {0, 1, 1, 1, 1, 0, 1}, // d
    {1, 0, 0, 1, 1, 1, 1}, // E
    {1, 0, 0, 0, 1, 1, 1}  // F
};
void setup()
{
  // set both common cathodes as output
  pinMode(COMCATHODE1, OUTPUT);
  pinMode(COMCATHODE2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SWITCHPIN, INPUT);
  // set both common cathodes to LOW
  digitalWrite(COMCATHODE1, LOW);
  digitalWrite(COMCATHODE2, LOW);
  digitalWrite(BUZZER, LOW);

  // all used pins for anodes as output
  for (int i = 0; i < NUMSEGMENTS; i++)
  {
    pinMode(SegmentPins[i], OUTPUT);
  }
}

// endless loop
void loop()
{
  if (charcount > 15)
  {
    charcount = 0;
  }

  if (digitalRead(SWITCHPIN) == HIGH && !swPressed)
  {
    swPressed = true;
    charcount++;
    setSegments(charcount);
    delay(50);
  }
  if (digitalRead(SWITCHPIN) == LOW && swPressed)
  {
    swPressed = false;
  }
}

// Function sets the segments for specific number called signcount
void setSegments(int signcount)
{
  for (int i = 0; i < NUMSEGMENTS; i++)
  {
    digitalWrite(SegmentPins[i], digits[signcount][i]);
  }
}