/**PIN INITIALIZATION**/
//Receiver
const int chA = 11; //channel 1 pin STEERING
const int chB = 12; //channel 2 pin THROTTLING

//Left motor
const int motor1pin1 = 4; // N1 on LEFT motor controller
const int motor1pin2 = 5; // N2 on LEFT motor controller
const int ENAleft = 9; // PWM for LEFT motor

//Right motor
const int motor2pin1 = 7; // N1 on RIGHT motor controller
const int motor2pin2 = 8; // N2 on RIGHT motor controller
const int ENAright = 10; // PWM for RIGHT motor

//Motor Shield
const int motorShield = 6; //turn on the motor shield

//Input from receiver and output to motors
int ch1; //STEERING (900 - 2000 VALUE)
int ch2; //THROTTLING (900 - 2000 VALUE)
int strPWM = 0; //0-255 VALUE
int thrPWM = 0; //0-255 VALUE

//MPU6050
#define scl A5;
#define sda A4;
const int gyroInt = 2; //gyro interrupt

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
