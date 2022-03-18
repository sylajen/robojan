 * General configuration for robojan.ino
 * Tested on an Arduino Mega
 */

// HARDWARE

#define MOTORDIR_L -1 // PIN1 AND PIN2
#define MOTORDIR_R 1  // PIN3 AND PIN4

// CONTROLLER THROTTLING AND STEERING
#define KP_POSITION 0.015
#define KP_STEERING 0.01

// BLUETOOTH CONTROL
#define contrAddress 13.20.3000; // the bluetooth address for the controller


// SCHEDULING
#define BLINK_INTERVAL 200
#define CONTROLLER_INTERVAL 10
#define ACTIVATION_INTERVAL 50

// SERIAL
#define BAUDRATE_ODRIVE 115200
#define BAUDRATE_PC 115200
