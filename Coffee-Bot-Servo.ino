#include "Arduino.h"
#include <Servo.h>

Servo brewStrengthServo;
Servo brewNowServo;

const int brewPin = 5;
const int onPin = 6;

const int strengthInterruptPin = 2; // 2 on nano, 24 on dragon
const int brewInterruptPin = 3; // 3 on nano, 25 on dragon

volatile int strengthInterrupt = 0;
volatile int brewInterrupt = 0;

// ISR for brew strength servo
void strengthISR() {
  strengthInterrupt = 1;
}

// ISR for turn on brew servo
void brewISR() {
  brewInterrupt = 1;
}

void setup() {
  brewStrengthServo.attach(brewPin);
  brewNowServo.attach(onPin, 1500, 2600);

  pinMode(strengthInterruptPin, INPUT_PULLUP);
  pinMode(brewInterruptPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(strengthInterruptPin), strengthISR, RISING);
  attachInterrupt(digitalPinToInterrupt(brewInterruptPin), brewISR, RISING);
  
}

void loop() {
  if (strengthInterrupt) {
    printf("strengthInterrupt is 1");
    strengthInterrupt = 0;
    strongBrew();
  }
  if (brewInterrupt) {
    brewInterrupt = 0;
    onBrew();
  }
}

void strongBrew() {
  brewStrengthServo.writeMicroseconds(2300); // move servo to on position
  delay(1000); // change this to millis maybe
  brewStrengthServo.writeMicroseconds(2000); // move servo to off position
  delay(4000); // change this to millis maybe
}

void onBrew() {
  brewNowServo.write(180); // move servo to on position
  delay(1000); // change this to millis maybe
  brewNowServo.write(120); // move servo to off position
  delay(4000); // change this to millis maybe
}
