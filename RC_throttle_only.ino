
//#include "config.h"
//#include "Metro.h"
//#include "PID_v1"
// int motorState = 0; //0 for off, 1 for on

const int chA = 12; //channel 1 pin
const int chB = 24; //channel 2 pin

int ch1; //throttle
int ch2; //steer

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
 digitalWrite(motor1pin2, LOW);
}
void leftMotorForward(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
}
void leftMotorOff(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(ENAleft, HIGH);
}

/****Right Motor Functions****/
void rightMotorBackward(){
 digitalWrite(motor2pin1, HIGH);
 digitalWrite(motor2pin2, LOW);
}
void rightMotorForward(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}
void rightMotorOff(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(ENAright, HIGH);
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

  //ch2 = pulseIn(chB,HIGH);
  //Serial.print("ch2:"); //Prints channel readings on Serial Monitor
  //Serial.print(ch2);
  //Serial.print("|");

  analogWrite(ENAleft,200); //PVM
  analogWrite(ENAright,200);

  if (ch1 > 1850){
    leftMotorForward();
    rightMotorForward();
  }
  else if (ch1 < 1550){
    leftMotorBackward();
    rightMotorBackward();
  }
  else{
    leftMotorOff();
    rightMotorOff();
  }
}
