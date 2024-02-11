
#include <Scheduler.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servoB;
Servo servoT;
Servo servoB2;
Servo servoT2;

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int red = 7;
const int yellow = 6;
const int green = 8;
const int buzzer = 9;
int posT;
int posB;

void setup() {
  Serial.begin(9600);
  servoB.attach(5);
  servoT.attach(4);
  //  servoB2.attach(10);
  //  servoT2.attach(11);
  lcd.init();
  lcd.backlight();
  Serial.println("Main setup: started");
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome! ");
  digitalWrite(red, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(500);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(green, LOW);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  
  servoT.write(10);
  servoB.write(90);
  servoT2.write(80);
  servoB2.write(90);
  digitalWrite(yellow, HIGH);
  for (posB = 90; posB >= 15; posB -= 3) {
    servoB.write(posB);
    delay(100);
  }
  digitalWrite(yellow, LOW);
  delay(500);

  digitalWrite(green, HIGH);
  for (posT = 10; posT <= 80; posT += 3) {
    servoT.write(posT);
    delay(100);
  }
  digitalWrite(green, LOW);
  delay(500);
  Scheduler.start(setup2, loop2);
  Scheduler.start(setup3, loop3);
}

void loop() {
  Serial.println("Main loop started");
  int distance = Serial.read();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(distance);
  delay(500);
  //  String msg=String(distance);
  //  espSerial.write(String(distance));
  if (distance <= 20) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
  }
}

void setup2() {
  Serial.println("setup2 started");
}

void loop2() {
  Serial.println("loop2 started");
  digitalWrite(yellow, HIGH);
  for (posB = 15; posB <= 165; posB += 3) {
    servoB.write(posB);
    delay(100);
  }
  digitalWrite(yellow, LOW);
  delay(500);
  digitalWrite(yellow, HIGH);
  for (posB = 165; posB >= 15; posB -= 3) {
    servoB.write(posB);
    delay(100);
  }
  digitalWrite(yellow, LOW);
  delay(500);
}


void setup3() {
  Serial.println("setup3 started");
}

void loop3() {
  Serial.println("loop3 started");
  digitalWrite(green, HIGH);
  for (posT = 80; posT <= 135; posT += 3) {
    servoT.write(posT);
    delay(100);
  }
  digitalWrite(green, LOW);
  delay(500);

  digitalWrite(green, HIGH);
  for (posT = 135; posT >= 80; posT -= 3) {
    servoT.write(posT);
    delay(100);
  }
  digitalWrite(green, LOW);
  delay(500);
}
