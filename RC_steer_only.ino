
//#include "config.h"
//#include "Metro.h"
//#include "PID_v1"
// int motorState = 0; //0 for off, 1 for on

const int chA = 13; //channel 1 pin
const int chB = 12; //channel 2 pin

int ch1; //steer
int ch2; //throttle

//LEFT MOTOR
int motor1pin1 = 9; // N1 on LEFT motor controller
int motor1pin2 = 10; // N2 on LEFT motor controller 
int ENAleft = 8; // PWM for LEFT motor

//RIGHT MOTOR
int motor2pin1 = 5; // N1 on RIGHT motor controller
int motor2pin2 = 6; // N2 on RIGHT motor controller
int ENAright = 7; // PWM for RIGHT motor

/****Left Motor Functions****/
void leftMotorBackward(){
  digitalWrite(motor1pin1, HIGH);
  analogWrite(motor1pin2, 0);
}
void leftMotorForward(){
  analogWrite(motor1pin1, 0);
  digitalWrite(motor1pin2, HIGH);
}
void leftMotorOff(){
  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 0);
  digitalWrite(ENAleft, LOW);
}

/****Right Motor Functions****/
void rightMotorBackward(){
  digitalWrite(motor2pin1, HIGH);
  analogWrite(motor2pin2, 0);
}
void rightMotorForward(){
  analogWrite(motor2pin1, 0);
  digitalWrite(motor2pin2, HIGH);
}
void rightMotorOff(){
  analogWrite(motor2pin1, 0);
  analogWrite(motor2pin2, 0);
  digitalWrite(ENAright, LOW);
}

/****Steering****/
void turnLeft(){
  analogWrite(motor1pin1, 0);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  analogWrite(motor2pin2, 0);
}
void turnRight(){
  analogWrite(motor2pin1, 0);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor1pin1, HIGH);
  analogWrite(motor1pin2, 0);
}
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //setup for receiver
  pinMode(chA,INPUT);
  pinMode(chB,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ch1 = pulseIn(chA,HIGH);
  Serial.print("ch1:"); //Prints channel readings on Serial Monitor
  Serial.print(ch1);
  Serial.println();

  ch2 = pulseIn(chB,HIGH);
  //Serial.print("ch2:"); //Prints channel readings on Serial Monitor
  //Serial.print(ch2);
  //Serial.println();

  analogWrite(ENAleft,200); //PVM
  analogWrite(ENAright,200);
  if (ch1 > 1650){
    turnLeft();
  }
  else if (ch1 < 1250){
    turnRight();
  }
  else{
    leftMotorOff();
    rightMotorOff();
  }

  /*if (ch2 > 1650){
    leftMotorForward();
    rightMotorForward();
  }
  else if (ch2 < 1250){
    leftMotorBackward();
    rightMotorBackward();
  }
  else{
    leftMotorOff();
    rightMotorOff();
  }*/
  
}
