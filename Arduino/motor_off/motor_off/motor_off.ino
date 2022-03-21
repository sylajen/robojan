
//#include "config.h"
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

void setup() {
  // put your setup code here, to run once  
}

void loop() {
  /***LEFT MOTOR TEST***/
  analogWrite(ENAleft, 200);
  LeftMotorOff();

  /***RIGHT MOTOR TEST***/
  analogWrite(ENAright, 200);
  RightMotorOff();
}

/****Left Motor Functions****/
void LeftMotorOff(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}

/****Right Motor Functions****/
void RightMotorOff(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}
