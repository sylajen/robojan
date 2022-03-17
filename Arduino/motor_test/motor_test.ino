#include "config.h"
#include "Metro.h"

int motorState = 0; //0 for off, 1 for on

//LEFT MOTOR
int motor1pin1 = 2;
int motor1pin2 = 3;
//RIGHT MOTOR
int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  controlTask();
  
}

void controlTask(){
  if controller == forward
}
