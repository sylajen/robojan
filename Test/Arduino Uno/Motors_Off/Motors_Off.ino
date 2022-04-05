#include "config.h"

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  analogWrite(ENAleft, 0);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  analogWrite(ENAright, 0);
}
