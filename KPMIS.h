
#include <Arduino.h>

class KPMIS {
public:
  KPMIS() {
    for (int i = 0; i < 6; i++) pinMode(led[i], OUTPUT);
  }
  void initMotors() {
    _leftDirPin = 45;
    _leftPWMPin = 44;
    _rightDirPin = 47;
    _rightPWMPin = 46;
    _leftDir = 0;
    _rightDir = 0;
    pinMode(_leftDirPin, OUTPUT);
    pinMode(_leftPWMPin, OUTPUT);
    pinMode(_rightDirPin, OUTPUT);
    pinMode(_rightPWMPin, OUTPUT);
    digitalWrite(_leftDirPin, _leftDir);
    digitalWrite(_rightDirPin, _rightDir);
  }
  void reverse() {
    _leftDirPin = 47;
    _rightDirPin = 45;
    _leftPWMPin = 46;
    _rightPWMPin = 44;
    reverseLeftMotor();
    reverseRightMotor();
  }

  

  void reverseLeftMotor() {
    if (_leftDir == 1) _leftDir = 0;
    else _leftDir = 1;
    digitalWrite (_leftDirPin, _leftDir);
  }
  void reverseRightMotor() {
    if (_rightDir == 1) _rightDir = 0;
    else _rightDir = 1;
    digitalWrite (_rightDirPin, _rightDir);
  }

  void stop() {
    digitalWrite(_leftPWMPin, 0);
    digitalWrite(_rightPWMPin, 0);
    delay(50);
  }

  void move(int pwrLeft, int pwrRight) {
    pwrLeft = constrain(pwrLeft, -255, 255);
    pwrRight = constrain(pwrRight, -255, 255);

    if (pwrLeft > 0) digitalWrite(_leftDirPin, _leftDir);
    else digitalWrite(_leftDirPin, not _leftDir);
	
	
    if (pwrRight > 0) digitalWrite(_rightDirPin, _rightDir);
    else digitalWrite(_rightDirPin, not _rightDir);
	
    analogWrite(_leftPWMPin, abs(pwrLeft));
    analogWrite(_rightPWMPin, abs(pwrRight));
  }
  
  void move(int pwrLeft, int pwrRight, int millsec) {
    move(pwrLeft, pwrRight);
    delay(millsec);
    stop();
  }

  void pMove(int error, int pwr, float kp){
    int Psost = error * kp;
    move(pwr - Psost, pwr + Psost);
  }
  void pMove(int error, int pwr, float kp, int millsec){
	long currentMillis = millis();
	while (millis() - currentMillis < millsec) pMove(error, pwr, kp);
    stop();
  }

  int readButtons() {
    for (int num = 0; num < 6; num++) {
      if (digitalRead(button[num])) return num + 1;
    }
    return 0;
  }
  bool readButton(int buttonNumber) {
    buttonNumber = constrain(buttonNumber, 0, 5);
    return digitalRead(button[buttonNumber - 1]);
  }
  void waitButtons() {
    bool flag = true;
    while (flag) {
      for (int num = 0; num < 6; num++) {
        if (digitalRead(button[num])) flag = false;
      }
    }
  }
  void waitButton(int buttonNumber) {
    while (not readButton(buttonNumber)) {}
  }

  int readPot(int potNumber) {
    potNumber = constrain(potNumber, 0, 5);
    return analogRead(pot[potNumber]);
  }

  void ledValue(int ledNumber, bool state) {
    ledNumber = constrain(ledNumber, 0, 5);
    digitalWrite(led[ledNumber - 1], state);
  }

private:

  int _leftPWMPin, _leftDirPin,_rightPWMPin, _rightDirPin, _leftDir , _rightDir;

  int button[6] = { 35, 34, 33, 32, 31, 30 };
  int led[6] = { 22, 23, 24, 25, 26, 27 };
  int pot[6] = { A10, A11, A12, A13, A14, A15 };
};