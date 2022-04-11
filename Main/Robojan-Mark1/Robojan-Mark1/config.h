/**PIN INITIALIZATION**/
//Receiver
const int chA = 5; //channel 1 pin STEERING
const int chB = 6; //channel 2 pin THROTTLING

//Left motor
const int motor1pin1 = 12; // N1 on LEFT motor controller
const int motor1pin2 = 13; // N2 on LEFT motor controller
const int ENAleft = 11; // PWM for LEFT motor

//Right motor
const int motor2pin1 = 7; // N1 on RIGHT motor controller
const int motor2pin2 = 8; // N2 on RIGHT motor controller
const int ENAright = 9; // PWM for RIGHT motor

/******************PID******************/
int mspeed = 10;
int turnspeed = 50;
int16_t Acc_rawX, Acc_rawY, Acc_rawZ, Gyr_rawX, Gyr_rawY, Gyr_rawZ;
float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];
float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;
float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;

//PID CONSTANTS
float kp = 180;
float kd = 160;
float ki = 80;
float desired_angle = 8;

//Input from receiver and output to motors
int ch1; //STEERING (900 - 2000 VALUE)
int ch2; //THROTTLING (900 - 2000 VALUE)
int strPWM = 0; //0-255 VALUE
int thrPWM = 0; //0-255 VALUE

/**BOUNDARIES**/
//Receiver channel inputs
const int thrMaxForward = 2100;
const int thrMinForward = 1550;
const int thrMaxBackward = 850;
const int thrMinBackward = 1370;

const int strMaxLeft= 2100;
const int strMinLeft = 1550;
const int strMaxRight = 850;
const int strMinRight = 1350;

//Boundaries for PWM outputs
const int maxPWM = 255;
const int minPWM = 75; //75 instead of 0 because of deadband
