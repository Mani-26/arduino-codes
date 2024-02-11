#include <pt.h>
#include<UltraDistSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servoB;
Servo servoT;

LiquidCrystal_I2C lcd(0x27, 16, 2);
UltraDistSensor ultrasonic;

float reading;
const int red = 7;
const int yellow = 6;
const int green = 8;
const int buzzer = 9;
int pos = 0;
static struct pt pt1, pt2, pt3;


void obstacle() {
  reading = ultrasonic.distanceInCm();
  delay(100);
  Serial.println(reading);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(reading);
  delay(1000);
  if (reading <= 20) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
  }
}





void setup() {
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  servoB.attach(5);
  servoT.attach(4);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome! ");
  delay(2000);
  ultrasonic.attach(2, 3);//Trigger pin , Echo pin
  servoT.write(10);
  servoB.write(10);
  
  digitalWrite(yellow, HIGH);
  for (pos = 10; pos <= 90; pos += 3) {
    servoB.write(pos);
    delay(100);
  }
  digitalWrite(yellow, LOW);
  delay(1000);
  
  digitalWrite(green, HIGH);
  for (pos = 10; pos <= 90; pos += 3) {
    servoT.write(pos);
    delay(100);
  }
  digitalWrite(green, LOW);
  delay(1000);

}

void loop() {
  
}
