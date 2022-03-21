//#include "config.h"
#include "Metro.h"
//#include "PID_v1"
// int motorState = 0; //0 for off, 1 for on

// note, Pin 11 is fried on the ODrive

//LEFT MOTOR
int motor1pin1 = 7; // N1 on LEFT motor controller
int motor1pin2 = 8; // N2 on LEFT motor controller 
int ENAleft = 9; // PWM for LEFT motor

//RIGHT MOTOR
int motor2pin1 = 5; // N1 on RIGHT motor controller
int motor2pin2 = 6; // N2 on RIGHT motor controller
int ENAright = 4; // PWM for RIGHT motor

//Counter for motor test
int counter = 1;

void setup() {
  // put your setup code here, to run once
    Serial.begin(9600);
}

void loop() {
    /** *LEFT MOTOR TEST***/
    analogWrite(ENAleft, 200);
    LeftMotorForward(); // We turn to direction 1 for 3s then stop for 2s
    delay(3000);
    LeftMotorBrake();
    delay(5000);
    LeftMotorBackward(); // We turn to direction 2 for 3s then stop for 2s
    delay(3000);
    LeftMotorBrake();
    delay(5000);

    /***RIGHT MOTOR TEST***/
    analogWrite(ENAright, 200);
    RightMotorForward(); // We turn to direction 1 for 3s then stop for 2s
    delay(3000);
    RightMotorBrake();
    delay(5000);
    RightMotorBackward(); // We turn to direction 2 for 3s then stop for 2s
    delay(3000);
    RightMotorBrake();
    delay(5000);
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

void LeftMotorBrake(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(ENAleft, HIGH);
}

/****Right Motor Functions****/
void RightMotorForward(){
 digitalWrite(motor2pin1, HIGH);
 digitalWrite(motor2pin2, LOW);
}

void RightMotorBackward(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void RightMotorOff(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void RightMotorBrake(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(ENAright, HIGH);
}
