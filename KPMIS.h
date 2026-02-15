
#include <Arduino.h>

class KPMIS {
public:
  KPMIS() {
	  for (int i = 0; i < 6; i++) pinMode(led[i], OUTPUT);
  }
  void initMotors() {
    pinMode(motor[0][0], OUTPUT);
    pinMode(motor[1][0], OUTPUT);
    pinMode(motor[1][1], OUTPUT);
    pinMode(motor[0][1], OUTPUT);
    digitalWrite(motor[0][0], motor[0][2]);
    digitalWrite(motor[1][0], motor[1][2]);
	
  }
  void reverse() {
    for (int i = 0; i < 3; i++) {
      byte a = motor[0][i];
      motor[0][i] = motor[1][i];
      motor[1][i] = a;
    }
    reverseMotorNumber(0);
    reverseMotorNumber(1);
  }

  void reverseMotorNumber(bool motorNumber) {
    motor[motorNumber][2] = not motor[motorNumber][2];
    digitalWrite(motor[motorNumber][0], motor[motorNumber][2]);
  }
  
  void reverseLeftMotor() {
    reverseMotorNumber(0);
  }
  void reverseRightMotor() {
    reverseMotorNumber(1);
  }
  
  void stop() {
    digitalWrite(motor[0][1], 0);
    digitalWrite(motor[1][1], 0);
    delay(50);
  }

  void move(int pwrLeft, int pwrRight) {
    pwrLeft = constrain(pwrLeft, -255, 255);
    pwrRight = constrain(pwrRight, -255, 255);
    if (pwrLeft > 0) digitalWrite(motor[0][0], motor[0][2]);
    else digitalWrite(motor[0][0], not motor[0][2]);
    if (pwrRight > 0) digitalWrite(motor[1][0], motor[1][2]);
    else digitalWrite(motor[1][0], not motor[1][2]);
    analogWrite(motor[0][1], abs(pwrLeft));
    analogWrite(motor[1][1], abs(pwrRight));
  }
  void move(byte pwrLeft, byte pwrRight, int millsec) {
    move(pwrLeft, pwrRight);
    delay(millsec);
    stop();
  }

  bool readButton(byte buttonNumber) {
	int num = buttonNumber - 1;
    buttonNumber = constrain(num, 0, 5);
    return digitalRead(button[num]);
  }
  void waitButtonNumber(byte buttonNumber){
	  while (not readButton(buttonNumber)){}
  }

  int readPot(byte potNumber) {
    potNumber = constrain(potNumber, 0, 5);
    return analogRead(pot[potNumber]);
  }

  void ledValue(byte ledNumber, bool state) {
	int num = ledNumber - 1;
    digitalWrite(led[num], state);
  }
  
private:
  byte motor[2][3] = {
    { 45, 44, 0 },  // 0
    { 47, 46, 0 }   // 1
  };

  byte button[6] = {35, 34, 33, 32, 31, 30 };
  byte led[6] = {22, 23, 24, 25, 26, 27 };
  byte pot[6] = { A10, A11, A12, A13, A14, A15 };
};
