#include <AFMotor.h>
const int ultrasonicTrigPin = 2;  
const int ultrasonicEchoPin = 3;  
const int irLeftPin = 4;        
const int irRightPin = 5;     
const int obstacleThreshold = 20;  
const int followThreshold = 50;    
AF_DCMotor motor1(1);  
AF_DCMotor motor2(2);  
AF_DCMotor motor3(3);  
AF_DCMotor motor4(4);  


int getUltrasonicDistance() {
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

int getObjectDistance() {
  int leftIR = digitalRead(irLeftPin);
  int rightIR = digitalRead(irRightPin);
  if (leftIR == LOW && rightIR == LOW) {
    return 0;  
  } else if (leftIR == HIGH && rightIR == LOW){
    return 1;  
  } else if (leftIR == LOW && rightIR == HIGH){
    return 2;  
  } else {
    return 3;   
  }
}
void moveForward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}
void turnRight() {
  motor1.setSpeed(200);
  motor1.run(BACKWARD);
  motor2.setSpeed(200);
  motor2.run(BACKWARD);
  motor3.setSpeed(200);
  motor3.run(FORWARD);
  motor4.setSpeed(200);
  motor4.run(FORWARD);
}
void turnLeft() {
  motor1.setSpeed(200);
  motor1.run(FORWARD);
  motor2.setSpeed(200);
  motor2.run(FORWARD);
  motor3.setSpeed(200);
  motor3.run(BACKWARD);
  motor4.setSpeed(200);
  motor4.run(BACKWARD);
}
void avoidObstacle() {
  motor1.setSpeed(200);
  motor1.run(BACKWARD);
  motor2.setSpeed(200);
  motor2.run(BACKWARD);
  motor3.setSpeed(200);
  motor3.run(BACKWARD);
  motor4.setSpeed(200);
  motor4.run(BACKWARD);
  delay(1000);
  motor1.setSpeed(200);
  motor1.run(FORWARD);
  motor2.setSpeed(200);
  motor2.run(FORWARD);
  motor3.setSpeed(200);
  motor3.run(BACKWARD);
  motor4.setSpeed(200);
  motor4.run(BACKWARD);
  delay(1000);
}
void followObject() {
  motor1.setSpeed(200);
  motor1.run(FORWARD);
  motor2.setSpeed(200);
  motor2.run(FORWARD);
  motor3.setSpeed(200);
  motor3.run(FORWARD);
  motor4.setSpeed(200);
  motor4.run(FORWARD);
}
void setup() {
  Serial.begin(9600);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(irLeftPin, INPUT);
  pinMode(irRightPin, INPUT);
}
void loop() {
  int obstacleDistance = getUltrasonicDistance();
  int objectDistance = getObjectDistance();
  if (obstacleDistance < obstacleThreshold){
    avoidObstacle();
  } else if (objectDistance < followThreshold){
    followObject();
  }else if (objectDistance == 1) {
    turnLeft();
  } else if (objectDistance == 2) {
    turnRight();
  } else if (objectDistance == 3) {
    moveForward();
  } else {
    moveForward();
  }
}
