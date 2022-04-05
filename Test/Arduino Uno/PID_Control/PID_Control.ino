#include "config.h"
#include "I2Cdev.h"
#include "PID_v2.h"
#include "MPU6050.h"
#include <Wire.h>

//balancing
void Compute(float Pitch, float Roll, float Yaw) {
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;
  
   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
  
   /*Remember some variables for next time*/
   lastErr = error;
   lastTime = now;
}

void SetTunings(double Kp, double Ki, double Kd)
{
   kp = Kp;
   ki = Ki;
   kd = Kd;
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

double Kp = 2, Ki = 5, Kd = 1;
PID_v2 myPID(Kp, Ki, Kd, PID::Direct);

void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200); //setup for receiver

  //set pins as input
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);

  // load and configure the DMP
  devStatus = mpu.dmpInitialize();
    
  myPID.Start(analogRead(PIN_INPUT),  // input
              0,                      // current output
              100);                   // setpoint

}

void loop() {
  // put your main code here, to run repeatedly:
  timer = millis();
  
  ch1 = pulseIn(chA, HIGH, 25000); //steer
  ch2 = pulseIn(chB, HIGH, 25000); //throttle
 
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;


  /****************PRINT DATA****************/
  /*Print Receiver Information
  Serial.print("| ch1:"); //Prints channel readings on Serial Monitor
  Serial.print(ch1);
  Serial.print("  |  ");
  Serial.print("ch2 (throttling): "); //Prints channel readings on Serial Monitor
  Serial.print(ch2);
  Serial.println();*/
  //Output 
  Serial.print(" | Pitch = ");
  Serial.print(pitch);
  Serial.print(" | Roll = ");
  Serial.print(roll);  
  Serial.print(" | Yaw = ");
  Serial.println(yaw);

  
  balancing(ch2);
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}
