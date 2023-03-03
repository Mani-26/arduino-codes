#include<UltraDistSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
UltraDistSensor mysensor;
float reading;
void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print(" Welcome! ");
  delay(3000);
  lcd.clear();
  mysensor.attach(7, 8);//Trigger pin , Echo pin
}
void loop() {
  reading = mysensor.distanceInCm();
  lcd.setCursor(0, 0);
  lcd.print("Distance :- ");
  lcd.print(reading);
  lcd.print("CM");
  delay(500);
}
#include<UltraDistSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
UltraDistSensor mysensor;
float reading;
void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print(" Welcome! ");
  delay(3000);
  lcd.clear();
  mysensor.attach(7, 8);//Trigger pin , Echo pin
}
void loop() {
  reading = mysensor.distanceInCm();
  lcd.setCursor(0, 0);
  lcd.print("Distance :- ");
  lcd.print(reading);
  lcd.print("CM");
  delay(500);
}
