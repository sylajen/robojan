#include <Wire.h>
#include "config.h"

void setup(){
  //TO BEGIN I2C COMMUNICATIONS
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  /*****Setup Pin Modes*****/
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  Serial.begin(9600);
  time = millis(); //TIME IN MILLISECONDS
}

void loop(){
  /*******************WARNING******************/
  /*********NO DELAYS,NO SERIAL PRINTS*********/
  timePrev = time;
  time = millis();
  elapsedTime = (time - timePrev) / 1000;
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  //RAW ACCELEROMETER DATA FROM IMU
  Acc_rawX = Wire.read() << 8 | Wire.read();
  Acc_rawY = Wire.read() << 8 | Wire.read();
  Acc_rawZ = Wire.read() << 8 | Wire.read();

  //CONVERTING RAW DATA TO ANGLES
  Acceleration_angle[0] = atan((Acc_rawY / 16384.0) / sqrt(pow((Acc_rawX / 16384.0), 2) + pow((Acc_rawZ / 16384.0), 2))) * rad_to_deg;
  Acceleration_angle[1] = atan(-1 * (Acc_rawX / 16384.0) / sqrt(pow((Acc_rawY / 16384.0), 2) + pow((Acc_rawZ / 16384.0), 2))) * rad_to_deg;
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 4, true);

  //PULLING RAW GYRO DATA FROM IMU
  Gyr_rawX = Wire.read() << 8 | Wire.read();
  Gyr_rawY = Wire.read() << 8 | Wire.read();

  //CONVERTING RAW DATA TO ANGLES
  Gyro_angle[0] = Gyr_rawX / 131.0;
  Gyro_angle[1] = Gyr_rawY / 131.0;

  //COMBINING BOTH ANGLES USING A COMPLIMENTARY FILTER
  Total_angle[0] = 0.98 * (Total_angle[0] + Gyro_angle[0] * elapsedTime) + 0.02 * Acceleration_angle[0]; //PITCH
  Total_angle[1] = 0.98 * (Total_angle[1] + Gyro_angle[1] * elapsedTime) + 0.02 * Acceleration_angle[1]; //ROLL

  //ERROR CALCULATION
  error = Total_angle[0] - desired_angle;

  //PROPORTIONAL ERROR
  pid_p = kp * error;

  //INTERGRAL ERROR
  pid_i = pid_i + (ki * error);

  //DIFFERENTIAL ERROR
  pid_d = kd * ((error - previous_error) / elapsedTime);

  //TOTAL PID VALUE
  PID = pid_p + pid_i + pid_d;

  //UPDATING THE ERROR VALUE
  previous_error = error;
  //Serial.println(PID);                     //UNCOMMENT FOR DEBUGGING
  //delay(60);                               //UNCOMMENT FOR DEBUGGING
  //Serial.println(Total_angle[0]);          //UNCOMMENT FOR DEBUGGING

  //CONVERTING PID VALUES TO ABSOLUTE VALUES
  mspeed = abs(PID);                        
  //Serial.print(mspeed);                           //UNCOMMENT FOR DEBUGGING
  //Serial.print(" | ");                            //UNCOMMENT FOR DEBUGGING
  //mspeed = map(mspeed, 0, 10000, minPWM, maxPWM); //UNCOMMENT FOR DEBUGGING
  //Serial.print(mspeed);                           //UNCOMMENT FOR DEBUGGING
  //Serial.print(" | ");                            //UNCOMMENT FOR DEBUGGING
  //Serial.println(error);                          //UNCOMMENT FOR DEBUGGING

  //Self Balancing
  if (Total_angle[0] < desired_angle){
    ccw();
    if (Total_angle[0] > maxAngle){
      motorOff();
    }
    if (Total_angle[0] < -maxAngle){
      motorOff();
    }
  }
  else if (Total_angle[0] > desired_angle)
  {
    cw();
    if (Total_angle[0] > maxAngle){
      motorOff();
    }
    if (Total_angle[0] < -maxAngle){
      motorOff();
    }
  }
  else {
    motorOff();
  }
  
}

/******************MOVEMENT FUNCTIONS******************/
void cw() {
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  analogWrite(ENAleft, mspeed);
  analogWrite(ENAright, mspeed);
}
void ccw() {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(ENAleft, mspeed);
  analogWrite(ENAright, mspeed);
}
void motorOff() {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  analogWrite(ENAleft, 0);
  analogWrite(ENAright, 0);
}
