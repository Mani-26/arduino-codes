#include<MFRC522.h>
#include<LiquidCrystal.h>
#include<SPI.h>
#include<Servo.h>
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MFRC522 mfrc522(10, 9);
Servo myservo;
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME To ");
  lcd.setCursor(0, 1);
  lcd.print(" RFID DOOR LOCK");
  delay(2000);
  lcd.clear();
  myservo.attach(8);
  myservo.write(170);
  lcd.print("#ACCESS CONTROL#");
  lcd.setCursor(0, 1);
  lcd.print("    Scan Tag");
  mfrc522.PCD_Init();
  Serial.println("Scan Tag");
}
void loop()
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String uid = "";
  Serial.println();
  Serial.print("UID=");
  for (int i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    uid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  uid.toUpperCase();
  if (uid == "BC2A1A4A")
  {
    Serial.print("PERSON 1");
    lcd.clear();
    lcd.print(" ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print("PERSON 1");
    myservo.write(10);
  }
  else if (uid == "5347ED14")
  {
    Serial.print("PERSON 2");
    lcd.clear();
    lcd.print(" ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print("PERSON 2");
    myservo.write(5);
  }
  delay(5000);
  myservo.write(180);
  lcd.clear();
  lcd.print("    Scan Tag");
  return;
}
