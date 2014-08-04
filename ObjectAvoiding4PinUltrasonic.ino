#include "Servo.h"
#include <Time.h>

Servo rightServo;
Servo leftServo;
const int pingPinTrig = 3;
const int pingPinEcho = 2;
long duration, inches, cm;

void setup()
{
  rightServo.attach(9);  // attaches the servo on pin 9 to the servo object
  leftServo.attach(10); 
}

void loop()
{
  leftServo.write(140);
  rightServo.write(140);

  pinMode(pingPinTrig, OUTPUT);
  digitalWrite(pingPinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinTrig, LOW);
  pinMode(pingPinEcho, INPUT);
  duration = pulseIn(pingPinEcho, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  delay(100);
  
  if(inches < 12)
  {
    stopServo(rightServo, leftServo, 500);
    turnRight(rightServo, leftServo, 1000);
  }  
}

void turnRight(Servo servo1, Servo servo2, int timeInMilliseconds)
{
  timer(servo1, servo2, 120, 70, timeInMilliseconds);
}

void turnLeft(Servo servo1, Servo servo2, int timeInMilliseconds)
{
  timer(servo1, servo2, 70, 120, timeInMilliseconds);
}

void stopServo(Servo servo1, Servo servo2, int timeInMilliseconds)
{
  timer(servo1, servo2, 90, 90, timeInMilliseconds);
}

void reverse(Servo servo1, Servo servo2, int timeInMilliseconds)
{
  timer(servo1, servo2, 60, 60, timeInMilliseconds);
}

void timer(Servo servo1, Servo servo2, int servo1PWM, int servo2PWM, int timeInMilliseconds)
{
  float timeNow = millis();
  float value = timeNow;

  while(value < timeNow + timeInMilliseconds)
  {
    servo1.write(servo1PWM);
    servo2.write(servo2PWM);
    value = millis();
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
