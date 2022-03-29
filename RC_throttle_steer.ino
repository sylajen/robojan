
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

//encoder calculation variable
double encVal = 0;
int encValInt = 0;

//throttling and steering
void throttle(int encThr, int thr){
  if (thr > 1650){
    leftMotorForward(encThr);
    rightMotorForward(encThr);
  }
  else if (thr < 1250){
    leftMotorBackward(encThr);
    rightMotorBackward(encThr);
  }
  else{
    leftMotorOff();
    rightMotorOff();
  }
}

void steering(int encStr, int str){
  if (str > 1650){
    turnLeft(encStr);
  }
  else if (str < 1250){
    turnRight(encStr);
  }
  else{
    return;
  }  
}

/****Left Motor Functions****/
void leftMotorBackward(int lbval){
  analogWrite(motor1pin1, lbval);
  analogWrite(motor1pin2, 0);
}
void leftMotorForward(int lfval){
  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, lfval);
}
void leftMotorOff(){
  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 0);
  digitalWrite(ENAleft, LOW);
}

/****Right Motor Functions****/
void rightMotorBackward(int rbval){
  digitalWrite(motor2pin1, rbval);
  analogWrite(motor2pin2, 0);
}
void rightMotorForward(int rfval){
  analogWrite(motor2pin1, 0);
  digitalWrite(motor2pin2, rfval);
}
void rightMotorOff(){
  analogWrite(motor2pin1, 0);
  analogWrite(motor2pin2, 0);
  digitalWrite(ENAright, LOW);
}

/****Steering****/
void turnLeft(int tlval){
  analogWrite(motor1pin1, 0);
  digitalWrite(motor1pin2, tlval);
  digitalWrite(motor2pin1, tlval);
  analogWrite(motor2pin2, 0);
}
void turnRight(int trval){
  analogWrite(motor2pin1, 0);
  digitalWrite(motor2pin2, trval);
  digitalWrite(motor1pin1, trval);
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
  ch1 = pulseIn(chA,HIGH); //steering
  Serial.print("ch1:"); //Prints channel readings on Serial Monitor
  Serial.print(ch1);
  Serial.print("  |  ");

  ch2 = pulseIn(chB,HIGH); //throttle
  Serial.print("ch2:"); //Prints channel readings on Serial Monitor
  Serial.print(ch2);
  Serial.println();

  encVal = ((ch1 + ch2) / 20) + 35;

  encValInt = round(encVal);

  Serial.print(encValInt);
  Serial.println();

  analogWrite(ENAleft, encValInt);
  analogWrite(ENAright, encValInt);

  throttle(encValInt, ch2);
  steering(encValInt, ch1);
}
