#include "config.h"

void control(int thr, int str){
  //if the contoller is off, motors are off
  if (thr == 0){
    leftMotorOff();
    rightMotorOff();
  }
  else {
    throttle(thr);
    steering(str);
  }
}

//throttling and steering
void throttle(int thr) {
  if (thr > thrMinForward) {
    thrPWM = map(thr, thrMinForward, thrMaxForward, minPWM, maxPWM);
    leftMotorForward(thrPWM);
    rightMotorForward(thrPWM);
  }
  else if (thr < thrMinBackward) {
    thrPWM = map(thr, thrMinBackward, thrMaxBackward, minPWM, maxPWM); //ch1, 1350, 850, 75, 255
    leftMotorBackward(thrPWM);
    rightMotorBackward(thrPWM);
  }
  else {
    leftMotorOff();
    rightMotorOff();
  }
}

void steering(int str) {
  if (str > strMinLeft) {
    strPWM = map(str, strMinLeft, strMaxLeft, minPWM, maxPWM);
    turnLeft(strPWM);
  }
  else if (str < strMinRight) {
    strPWM = map(str, strMinRight, strMaxRight, minPWM, maxPWM);
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
  digitalWrite(motorShield, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  ch1 = pulseIn(chA, HIGH, 25000); //steer
  Serial.print("| ch1:"); //Prints channel readings on Serial Monitor
  Serial.print(ch1);
  Serial.print("  |  ");

  ch2 = pulseIn(chB, HIGH, 25000); //throttle
  Serial.print("ch2:"); //Prints channel readings on Serial Monitor
  Serial.print(ch2);
  Serial.print(" |");
  Serial.println();

  control(ch1, ch2);
}
