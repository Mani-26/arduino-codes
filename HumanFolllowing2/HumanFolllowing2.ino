#include <NewPing.h> 

// Pin definitions
const int leftIRPin = 9;
const int rightIRPin = 2;
const int trigPin = 7;
const int echoPin = 8;
const int leftMotor1Pin = 3;
const int leftMotor2Pin = 4;
const int rightMotor1Pin = 5;
const int rightMotor2Pin = 6;
const int objectDistanceThreshold = 10;


NewPing sonar(trigPin, echoPin);

void setup() {
  pinMode(leftMotor1Pin, OUTPUT);
  pinMode(leftMotor2Pin, OUTPUT);
  pinMode(rightMotor1Pin, OUTPUT);
  pinMode(rightMotor2Pin, OUTPUT);
  digitalWrite(leftMotor1Pin, HIGH);
  digitalWrite(leftMotor2Pin, LOW);
  digitalWrite(rightMotor1Pin, HIGH);
  digitalWrite(rightMotor2Pin, LOW);
  Serial.println("forward setup");
  Serial.begin(9600);
}

void loop() {
  int distance = sonar.ping_cm();
  int leftSensorValue = digitalRead(leftIRPin);
  int rightSensorValue = digitalRead(rightIRPin);

  if (distance > 0 && distance <= objectDistanceThreshold) {
    avoidObject(distance);
  }
  else if (rightSensorValue == LOW) {
    right();
  }
  else if (leftSensorValue == LOW) {
    left();
  }
  else {
    followObject();
  }
  delay(1000);
}

void followObject() {

  digitalWrite(leftMotor1Pin, HIGH);
  digitalWrite(leftMotor2Pin, LOW);
  digitalWrite(rightMotor1Pin, HIGH);
  digitalWrite(rightMotor2Pin, LOW);
  Serial.println("forward");
}
void avoidObject(int distance) {
  stopMotors();
  delay(500);
  if ( distance >= objectDistanceThreshold) {
    followObject();
  }
}

void right() {

  digitalWrite(leftMotor1Pin, HIGH);
  digitalWrite(leftMotor2Pin, LOW);
  digitalWrite(rightMotor1Pin, LOW);
  digitalWrite(rightMotor2Pin, HIGH);
  Serial.println("right");
  delay(300);
}


void left() {
  digitalWrite(leftMotor1Pin, LOW);
  digitalWrite(leftMotor2Pin, HIGH);
  digitalWrite(rightMotor1Pin, HIGH);
  digitalWrite(rightMotor2Pin, LOW);
  Serial.println("left");
}
void stopMotors() {
  digitalWrite(leftMotor1Pin, LOW);
  digitalWrite(leftMotor2Pin, LOW);
  digitalWrite(rightMotor1Pin, LOW);
  digitalWrite(rightMotor2Pin, LOW);
  Serial.println("stop last");
}
