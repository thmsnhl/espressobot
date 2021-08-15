#include <Servo.h>
#include "SevSeg.h" //Die vorher hinzugefügte Library laden

SevSeg sevseg; //Ein sieben Segment Objekt initialisieren
Servo grinder; // Servo, der nickt

int servoInitState = 0;
int pos = 120; // variable to store the servo position

long duration = 0; // variable to store the value coming from the sensor
int potPin = 2;    // select the input pin for the potentiometer
long potValue = 0;
int durationInSeconds = 5;

void initServo(Servo &theServo)
{
  grinder.write(servoInitState);
}

void setup()
{
  byte numDigits = 2;                                              //Hier wird die Anzahl der Ziffern angegeben
  byte digitPins[] = {4, 5, 2, 3};                                 //Die Pins zu den Ziffern werden festgelegt
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};               //Die Pins zu den //Segmenten werden festgelegt
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); //In diesem
                                                                   //Abschnitt kann man nun entweder testen welche Art von Display man besitzt oder
                                                                   //wenn man es schon weiß angeben ob es sich um ein COMMON_CATHODE oder
                                                                   //COMMON_ANODE Display handelt. Das Display funktioniert nur wenn die richtige
                                                                   //Art eingetragen ist, ansonsten werden alle Segmente gleichzeitig leuchten.

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  grinder.attach(1);

  initServo(grinder);
}

void turnOn()
{
  digitalWrite(LED_BUILTIN, HIGH);
  grinder.write(120);
  delay(15);
  // for (pos = 120; pos <= 0; pos -= 2)
  // { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   grinder.write(pos); // tell servo to go to position in variable 'pos'
  //   delay(15);          // waits 15ms for the servo to reach the position
  // }
}

void turnOff()
{
  digitalWrite(LED_BUILTIN, LOW);
  grinder.write(servoInitState);
  delay(15);

  // for (pos = 0; pos <= 120; pos += 2)
  // { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   grinder.write(pos); // tell servo to go to position in variable 'pos'
  //   delay(15);          // waits 15ms for the servo to reach the position
  // }
}

long calcDuration()
{
  // Serial.println("PotValue:" + potValue);
  // 40 = 1023 / 25 (seconds)
  duration = (potValue / 40) * 1000 + 5000;
  Serial.println("Duration");
  Serial.println(duration);
  Serial.println("PotValue: ");
  Serial.println(potValue);
  Serial.println("");

  durationInSeconds = duration / 1000;

  return duration;
}

void loop()
{
  potValue = analogRead(potPin);

  duration = (potValue / 40) * 1000 + 5000;

  durationInSeconds = duration / 1000;
  // calcDuration();

  // Serial.println(calcDuration());

  // ######## ######## ######## ########

  sevseg.setNumber(durationInSeconds, 4); //Hier können wir nun die gewünschte Zahl eintragen.
  //Wir haben als Beispiel 1234 angegeben. Die Zahl hinter dem Komma steht für den
  //Punkt hinter einer Ziffer. Hierbei ist 3 der Punkt neben der ersten Ziffer und
  //0 wäre der Punkt ganz rechts neben der letzten Ziffer. Wenn man keinen Punkt
  //mit angezeigt haben möcht kann man z.B. 4 angeben.
  sevseg.refreshDisplay(); // Dieser Teil lässt die Nummer auf dem Display
  //erscheinen.
  sevseg.setBrightness(100); //Hier kann die Helligkeit des Displays angepasst
                             //werden. In einem Bereich von 0-100 wobei 100 das Hellste ist. 0 bedeutet
                             //jedoch nicht dass das Display komplett dunkel ist. Für die Anzeige einer Zahl
                             //ist allein die "sevseg.refreshDisplay();" Zeile verantwortlich

  // ######## ######## ######## ########
  // turnOn();

  // calcDuration();

  // // delay(calcDuration());
  // // delay(calcDuration());

  // turnOff();

  // delay(50);

  // initServo(grinder);
  // delay(10);
}
