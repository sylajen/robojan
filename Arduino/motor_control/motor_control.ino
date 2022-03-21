#include "config.h"
#include "Metro.h"
//#include "PID_v1"
// int motorState = 0; //0 for off, 1 for on

//LEFT MOTOR
int motor1pin1 = 7; // N1 on LEFT motor controller
int motor1pin2 = 8; // N2 on LEFT motor controller 
int ENAleft = 9; // PWM for LEFT motor

//RIGHT MOTOR
int motor2pin1 = 10; // N1 on RIGHT motor controller
int motor2pin2 = 11; // N2 on RIGHT motor controller
int ENAright = 12; // PWM for RIGHT motor

//CONTROLLER
int thrPin = 17;
int strPin = 19;
char thrVal = 0;
char strVal = 0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600); // Serial to PC
}

void loop() {
  thrVal = Serial2.read();
  if (thrVal > 0){
    LeftMotorForward();
    RightMotorForward();
  }
  else if (thrVal < 0){
    LeftMotorBackward();
    RightMotorBackward();
  }
  else{
    LeftMotorOff();
    RightMotorOff();
  }
}

/****Left Motor Functions****/
void LeftMotorForward(){
 digitalWrite(motor1pin1, HIGH);
 digitalWrite(motor1pin2, LOW);
}

void LeftMotorBackward(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
}

void LeftMotorOff(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}

/****Right Motor Functions****/
void RightMotorForward(){
 digitalWrite(motor1pin1, HIGH);
 digitalWrite(motor1pin2, LOW);
}

void RightMotorBackward(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
}

void RightMotorOff(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}
// CONTROLLER STUFF
/*void Throttle(){
  Serial.read(thrPin);
  if (thrPin > 0){
    LeftMotorForward();
    RightMotorForward();
  }
  else if (thrPin < 0){
    LeftMotorBackward();
    RightMotorBackward();
  }
  else{
    LeftMotorOff;
    RightMotorOff;
  }
}
/*
void Steering(){        // this is kind of messed rn, cause if it's not steering, the motors are off
  Serial.read(strPin);
  if (strPin > 0){
    LeftMotorForward();
    RightMotorBackward();
  }
  else if (strPin < 0){
    LeftMotorBackward();
    RightMotorForward();
  }
  else{
    LeftMotorOff;
    RightMotorOff;
  }
}
*/
