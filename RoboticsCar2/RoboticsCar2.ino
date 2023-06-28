#include <Servo.h>
#include <NewPing.h>
#include <UltraDistSensor.h>




// Ultrasonic sensor pins
#define US_TRIG 7
#define US_ECHO 6

// Motor pins
#define MOTOR_LEFT_1 2
#define MOTOR_LEFT_2 3
#define MOTOR_RIGHT_1 4
#define MOTOR_RIGHT_2 5

// Servo pin
#define SERVO_PIN 8

// Bluetooth module pins
#define BT_RX 0
#define BT_TX 1


//MOTOR CONTROLS
#define FORWARD 1
#define BACKWARD -1

//ULTRASONIC VALUE
#define MAX_DISTANCE 200

NewPing sonar(US_TRIG, US_ECHO, MAX_DISTANCE);

Servo servo;

int distance = 100;
int distanceR = 0;
int distanceL =  0;

void stop() {
  digitalWrite(MOTOR_LEFT_1, LOW);
  digitalWrite(MOTOR_LEFT_2, LOW);
  digitalWrite(MOTOR_RIGHT_1, LOW);
  digitalWrite(MOTOR_RIGHT_2, LOW);
  Serial.println("STOP");
}

void forward() {
  digitalWrite(MOTOR_LEFT_1, HIGH);
  digitalWrite(MOTOR_LEFT_2, LOW);
  digitalWrite(MOTOR_RIGHT_1, HIGH);
  digitalWrite(MOTOR_RIGHT_2, LOW);
  Serial.println("FORWARD");
}

void backward() {
  digitalWrite(MOTOR_LEFT_1, LOW);
  digitalWrite(MOTOR_LEFT_2, HIGH);
  digitalWrite(MOTOR_RIGHT_1, LOW);
  digitalWrite(MOTOR_RIGHT_2, HIGH);
  Serial.println("BACKWARD");
}
void turn_right() {
  digitalWrite(MOTOR_LEFT_1, HIGH);
  digitalWrite(MOTOR_LEFT_2, LOW);
  digitalWrite(MOTOR_RIGHT_1, LOW);
  digitalWrite(MOTOR_RIGHT_2, HIGH);
  Serial.println("RIGHT");
}

void turn_left() {
  digitalWrite(MOTOR_LEFT_1, LOW);
  digitalWrite(MOTOR_LEFT_2, HIGH);
  digitalWrite(MOTOR_RIGHT_1, HIGH);
  digitalWrite(MOTOR_RIGHT_2, LOW);
  Serial.println("LEFT");
}

void obstacle() {
  if (distance <= 35) {
    stop();
    delay(100);
    backward();
    delay(500);
    stop();
    delay(100);
    distanceR = lookRight();
    delay(300);
    distanceL = lookLeft();
    delay(300);

    if (distanceR >= distanceL)
    {
      turn_right();
      delay(800);
      forward();
    } else
    {
      turn_left();
      delay(800);
      forward();
    }
  }
  distance = readPing();
  Serial.println(distance);
  delay(500);
}

int lookRight()
{
  servo.write(40);
  delay(200);
  int distance = readPing();
  delay(400);
  servo.write(90);
  return distance;
}

int lookLeft()
{
  servo.write(140);
  delay(200);
  int distance = readPing();
  delay(400);
  servo.write(90);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void setup() {
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);
  servo.attach(SERVO_PIN);
  Serial.begin(9600);
  distance = readPing();
  delay(100);

  forward();
}

void loop() {
  String readvoice = "";
  char c=' ';
  distanceR = 0;
  distanceL =  0;
  obstacle();
  distance = readPing();
  delay(100);

  // Bluetooth control
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    Serial.println(cmd);
    if (cmd == 'F') {
      forward();
    }
    else if (cmd == 'B') {
      backward();
    }
    else if (cmd == 'L') {
      turn_left();
    }
    else if (cmd == 'R') {
      turn_right();
    }
    else if (cmd == 'S') {
      stop();
    }
  }
  while (Serial.available()>0) {
    c = Serial.read();
    readvoice += c;
  }
  
    Serial.println(readvoice);
  if (readvoice.length() > 0) {

    if (readvoice == "orward")
    {
      forward();
    }
    else if (readvoice == "wkward") {
      backward();
    }
    else if (readvoice == "eft") {
      turn_left();
    }
    else if (readvoice == "ight") {
      turn_right();
    }
    else if (readvoice == "top") {
      stop();
    }
  }
  }
