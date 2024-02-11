#include<UltraDistSensor.h>

#define L1 2
#define L2 3
#define R1 4
#define R2 7
#define EN1 5
#define EN2 6

UltraDistSensor mysensor;
int distance;
const int km = 100;
int minDistance = 25;
int r = 0;
char value;

void forward() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, HIGH);
  Serial.println("FORWARD");
}

void backward() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("BACK");
  delay(350);
}

void right() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, HIGH);
  Serial.println("RIGHT");
  delay(250);
}

void left() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, LOW);
  Serial.println("LEFT");
  delay(250);
}

void Stop() {
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("STOP");
  delay(500);
}

void obstacle() {
  distance = mysensor.distanceInCm();
  Serial.println(distance);
  if (distance < minDistance) {
    Stop();
    backward();
    Stop();
    if (r == 0) {
      right();
      r = 1;
    }
    else {
      left();
      r = 0;
    }
    obstacle();
  }
  else {
    forward();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R2, OUTPUT);
  mysensor.attach(A2, A3);
  Serial.println("Car Started!");
}

void loop() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == 'F') forward();
    else if (value == 'B') backward();
    else if (value == 'L') left();
    else if (value == 'R') right();
    else if (value == 'S') Stop();
  }
  else {
    obstacle();
  }
}
