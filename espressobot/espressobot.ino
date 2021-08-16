#include "SevSeg.h" // Necessary library for seven segment display

SevSeg sevseg; // Initialize seven segment display

long duration = 5000; // initialize the duration to grind
long potValue = 0;    // initialize the potentiometer value
int relayState = LOW; // relayState used to set the LED

// constants won't change. Used here to set pin numbers:
const int potPin = 2;           // select the input pin for the potentiometer
const int relayPin = A1;        // select the input pin for the potentiometer
const int ledPin = LED_BUILTIN; // (optional for visual feedback) the number of the LED pin

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated

void setup()
{
  Serial.begin(115200);

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT); // (optional for visual feedback)
  pinMode(relayPin, OUTPUT);

  byte numDigits = 2; // Here we set the number of digits for our seven segment display
  byte digitPins[] = {4, 5, 2, 3};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false;     // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md of SevSeg for options
  bool updateWithDelays = false;        // Default 'false' is Recommended
  bool leadingZeros = false;            // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true;          // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

// Convert the duration into seconds to display it
int durationInSeconds()
{
  return duration / 1000;
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  potValue = analogRead(potPin); // Value of the poti

  duration = (potValue / 40) * 1000 + 5000; // Do the math for a range of 5-30 Seconds

  sevseg.setNumber(durationInSeconds(), 4); // Set the number to be displayed, the parameter '4' defines where to set the decimal point 4 = no decimal point

  sevseg.refreshDisplay(); // This is what actually displays the number

  unsigned long currentMillis = millis(); // Set current time

  if (currentMillis - previousMillis >= duration)
  {

    previousMillis = currentMillis; // Save the last time you triggered the grinder

    // If the LED is off turn it on and vice-versa:
    if (relayState == LOW)
    {
      relayState = HIGH;
    }
    else
    {
      relayState = LOW;
    }

    digitalWrite(ledPin, relayState); // (optional for visual feedback) set the on-board LED with the relayState of the variable:

    digitalWrite(relayPin, relayState); // toggle the grinder relay
  }
}