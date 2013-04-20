#include <Servo.h>

/***********************************************/

Servo left1, left2, left3, right1, right2, right3;
// Servo vs analogWrite(int). Consider switching later. For now Servo will be used since code is already written for it.

const int leftPin = 11, 
          rightPin = 10;

/////////////////////////////////////////////////////
// Initialization Code
/////////////////////////////////////////////////////

void setup() {
  Serial.println("Hai der");
  left1.attach(leftPin);
  left2.attach(leftPin);
  left3.attach(leftPin);
  right1.attach(rightPin);
  right2.attach(rightPin);
  right3.attach(rightPin);
}

/////////////////////////////////////////////////////
// Input Code
/////////////////////////////////////////////////////

int getY() {
  return 0;
}
int getX() {
  return 0;
}

/////////////////////////////////////////////////////
// Drive Code
/////////////////////////////////////////////////////

void driveArcade(int forward, int turn) {
  int left = forward - turn;
  int right = forward + turn;
  left1.write(left);
  left2.write(left);
  left3.write(left);
  right1.write(right);
  right2.write(right);
  right3.write(right);
}

void emergencyStop() {
  left1.write(0); 
  left2.write(0);
  left3.write(0);
  right1.write(0);
  right2.write(0);
  right3.write(0);
}

/////////////////////////////////////////////////////
// Execution Code
/////////////////////////////////////////////////////

int inputToOutputScale = 1;
void loop() {
  int yDir = getY() * inputToOutputScale;
  int xDir = getX() * inputToOutputScale;
  driveArcade(yDir, xDir);
}

