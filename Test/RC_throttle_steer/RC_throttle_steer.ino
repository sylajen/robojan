//#include "config.h"
//#include "Metro.h"
//#include "PID_v1"
// int motorState = 0; //0 for off, 1 for on

//RECEIVER INITIALIZATION
const int chA = 5; //channel 1 pin
const int chB = 6; //channel 2 pin
int ch1; //throttle (900 - 2000 VALUE)
int ch2; //steer (900 - 2000 VALUE)
int strPWM = 0; //0-255 VALUE
int thrPWM = 0; //0-255 VALUE

//LEFT MOTOR
int motor1pin1 = 12; // N1 on LEFT motor controller
int motor1pin2 = 13; // N2 on LEFT motor controller
int ENAleft = 11; // PWM for LEFT motor

//RIGHT MOTOR
int motor2pin1 = 7; // N1 on RIGHT motor controller
int motor2pin2 = 8; // N2 on RIGHT motor controller
int ENAright = 9; // PWM for RIGHT motor

//throttling and steering
void throttle(int thr) {
  if (thr > 1550) {
    thrPWM = map(thr, 1550, 2100, 50, 255);
    leftMotorForward(thrPWM);
    rightMotorForward(thrPWM);
  }
  else if (thr < 1350) {
    thrPWM = map(thr, 1350, 850, 50, 255);
    leftMotorBackward(thrPWM);
    rightMotorBackward(thrPWM);
  }
  else {
    leftMotorOff();
    rightMotorOff();
  }
}

void steering(int str) {
  if (str > 1550) {
    strPWM = map(str, 1550, 2000, 50, 255);
    turnLeft(strPWM);
  }
  else if (str < 1350) {
    strPWM = map(str, 1350, 900, 50, 255);
    turnRight(strPWM);
  }
  else {
    return;
  }
}

/****Left Motor Functions****/
void leftMotorBackward(int lbval) {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(ENAleft, lbval);
}
void leftMotorForward(int lfval) {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  analogWrite(ENAleft, lfval);
}
void leftMotorOff() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  analogWrite(ENAleft, 0);
}

/****Right Motor Functions****/
void rightMotorBackward(int rbval) {
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(ENAright, rbval);
}
void rightMotorForward(int rfval) {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  analogWrite(ENAright, rfval);
}
void rightMotorOff() {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  analogWrite(ENAright, 0);
}

/****Steering****/
void turnLeft(int tlval) {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(ENAleft, tlval);
  analogWrite(ENAright, tlval);
}
void turnRight(int trval) {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  analogWrite(ENAleft, trval);
  analogWrite(ENAright, trval);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //setup for receiver
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ch1 = pulseIn(chA, HIGH, 25000); //throttling
  Serial.print("ch1:"); //Prints channel readings on Serial Monitor
  Serial.print(ch1);
  Serial.print("  |  ");

  ch2 = pulseIn(chB, HIGH, 25000); //steering
  Serial.print("ch2:"); //Prints channel readings on Serial Monitor
  Serial.print(ch2);
  Serial.println();

  throttle(ch1);
  steering(ch2);
}
