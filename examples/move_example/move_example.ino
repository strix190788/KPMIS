#include <KPMIS.h>
KPMIS robot;
void setup() {
  robot.initMotors();
  robot.reverse();
  robot.reverseLeftMotor();
  robot.move(120, 80, 1000); 
}

void loop() {
}
