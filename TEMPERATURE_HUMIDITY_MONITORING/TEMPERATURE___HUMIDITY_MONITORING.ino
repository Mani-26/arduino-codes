#include <LiquidCrystal.h>
#include "dht.h"
#define dataPin A0
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht DHT;
int temp;
int hum;
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME To ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity ");
  lcd.setCursor(0, 1);
  lcd.print("  MONITORING");
  delay(2000);
  lcd.clear();
}
void loop()
{
  int readData = DHT.read11(dataPin);
  hum = DHT.humidity;
  temp = DHT.temperature;
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); //degree symbol
  lcd.print("C ");
  delay(1000);
}
