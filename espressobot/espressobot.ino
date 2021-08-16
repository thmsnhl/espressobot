#include "SevSeg.h" //Die vorher hinzugefügte Library laden

SevSeg sevseg; //Ein sieben Segment Objekt initialisieren

long duration = 5000; // variable to store the value coming from the sensor
int potPin = 2;       // select the input pin for the potentiometer
int relaisPin = A1;   // select the input pin for the potentiometer
long potValue = 0;
int durationInSeconds = 5;

// constants won't change. Used here to set a pin number:
const int ledPin = LED_BUILTIN; // the number of the LED pin

// Variables will change:
int ledState = LOW; // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated

void setup()
{
  Serial.begin(115200);

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(relaisPin, OUTPUT);

  byte numDigits = 2;                                              //Hier wird die Anzahl der Ziffern angegeben
  byte digitPins[] = {4, 5, 2, 3};                                 //Die Pins zu den Ziffern werden festgelegt
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};               //Die Pins zu den //Segmenten werden festgelegt
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); //In diesem
                                                                   //Abschnitt kann man nun entweder testen welche Art von Display man besitzt oder
                                                                   //wenn man es schon weiß angeben ob es sich um ein COMMON_CATHODE oder
                                                                   //COMMON_ANODE Display handelt. Das Display funktioniert nur wenn die richtige
                                                                   //Art eingetragen ist, ansonsten werden alle Segmente gleichzeitig leuchten.

  sevseg.setBrightness(100); //Hier kann die Helligkeit des Displays angepasst
                             //werden. In einem Bereich von 0-100 wobei 100 das Hellste ist. 0 bedeutet
                             //jedoch nicht dass das Display komplett dunkel ist. Für die Anzeige einer Zahl
                             //ist allein die "sevseg.refreshDisplay();" Zeile verantwortlich
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // Value of the poti
  potValue = analogRead(potPin);

  // Do the math for a range of 5-30 Seconds
  duration = (potValue / 40) * 1000 + 5000;

  // Set the time for the display
  durationInSeconds = duration / 1000;

  sevseg.setNumber(durationInSeconds, 4); //Hier können wir nun die gewünschte Zahl eintragen.
  //Wir haben als Beispiel 1234 angegeben. Die Zahl hinter dem Komma steht für den
  //Punkt hinter einer Ziffer. Hierbei ist 3 der Punkt neben der ersten Ziffer und
  //0 wäre der Punkt ganz rechts neben der letzten Ziffer. Wenn man keinen Punkt
  //mit angezeigt haben möcht kann man z.B. 4 angeben.

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= duration)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    digitalWrite(relaisPin, ledState);
  }
  sevseg.refreshDisplay(); // Dieser Teil lässt die Nummer auf dem Display
}