#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
char str[34], L = 2;
int temp = 0, i = 0;
int Pass = 0, p = 0;
int c, x, d;
int contrast = 0;
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial mySerial (0, 1); //(RX, TX);
String val = "No Data";
String oldval;
String newval = "No Data";
void setup()
{
  lcd.begin(16, 2);
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print(" Welcome! ");
  delay(3000);
  lcd.clear();
  
}
void loop()
{
  if (temp == 1)
  {
    check();
    temp = 0;
    i = 0;
    delay(1000);
  }
  val = mySerial.readString();
  val.trim();
  Serial.println(val);
  if (val != oldval)
  {
    newval = val;
  }
  lcd.clear();
  lcd.setCursor(i, 0);
  lcd.print(newval);
  i++;
  if (i >= 15)
  {
    i = 0;
  }
  val = oldval;
}
void serialEvent()
{
 if (Serial.available() > 0)
  {
    char inChar = Serial.read();
    str[i++] = inChar;
    delay(10);
  }
  for (p = i + 1; p < 34; p++)
  {
    str[i++] = 32;
  }
  temp = 1;
  Serial.write(str);
  lcd.setCursor(0, 0);
  lcd.print(str);
  if (i > 16)
  {
    d = 16;
    for (x = 0; x <= 17; x++)
    {
      lcd.setCursor(x, 2);
      lcd.print(str[d]);
      d++;
    }
  }
}
void check()
{
  if (!(strncmp(str, "1", 1)))
  {
    digitalWrite(A1, 50);
    lcd.clear();
  }
  else if (!(strncmp(str, "2", 1)))
  {
    digitalWrite(A1, LOW);
    lcd.clear();
  }
}
