#include <LiquidCrystal_I2C.h>

#include <Wire.h>
LiquidCrystal_I2C lcd(0x3f,16,2);
int value =0;
float voltage=0;
float temp=0;


void setup()
{
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Mini Project");
}
void loop()
{
value=analogRead(A0);
voltage=value*0.00400;
temp=voltage*100;
lcd.setCursor(0, 1);
lcd.print("Temp : ");
lcd.setCursor(8,1);
lcd.print(temp);
lcd.setCursor(14,1);
lcd.print("C");
delay(100);
}
