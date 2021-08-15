#include <Servo.h>

Servo grinder; // Servo, der nickt

int servoInitState = 0;
int pos = 120; // variable to store the servo position

long duration = 0; // variable to store the value coming from the sensor
int potPin = 2;    // select the input pin for the potentiometer
long potValue = 0;

void initServo(Servo &theServo)
{
  grinder.write(servoInitState);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  grinder.attach(8);

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
  delay(10);
  duration = 5000 + (potValue / 40 * 1000);
  delay(10);
  Serial.println("Duration");
  Serial.println(duration);
  Serial.println("PotValue: ");
  Serial.println(potValue);
  Serial.println("");

  return duration;
}

void loop()
{
  potValue = analogRead(potPin);

  // Serial.println(calcDuration());

  turnOn();

  calcDuration();

  delay(calcDuration());
  // delay(calcDuration());

  turnOff();

  delay(5000);

  initServo(grinder);
  delay(10);
}
