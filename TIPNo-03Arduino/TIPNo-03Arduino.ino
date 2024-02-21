#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};

/*************************************************/
//PIN no A1 to A3 and 2 to 5 allocated for keypad//
/*************************************************/

byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

/***********************************/
//PIN no 9 to 13 allocated for RFID//
/***********************************/

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;
const int ir1 = 6;
const int ir2 = 7;

String rfidTag;
String pin;
char customKey;

boolean Auth(String rfidTag, String pin) {
  pin.toUpperCase();
  if (rfidTag.equals("43 21 26 AC")) {
    if (pin.equals("4321")) {
      Serial.println(1);
      Serial.write(1);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Authentication");
      lcd.setCursor(1, 1);
      lcd.print("Successfull!");
      delay(1000);
      return true;
    }
    else {
      Serial.println(0);
      Serial.write(0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Entered Pin");
      lcd.setCursor(1, 1);
      lcd.print("Doesn't Match!");
      delay(1000);
      return false;
    }
  }
  else if (rfidTag.equals("F3 76 54 A8")) {
    if (pin.equals("F376")) {
      Serial.println(1);
      Serial.write(1);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Authentication");
      lcd.setCursor(1, 1);
      lcd.print("Successfull!");
      delay(1000);
      return true;
    }
    else {
      Serial.println(0);
      Serial.write(0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Entered Pin");
      lcd.setCursor(1, 1);
      lcd.print("Doesn't Match!");
      delay(1000);
      return false;
    }
  }
  else if (rfidTag.equals("03 38 5E A8")) {
    if (pin.equals("0338")) {
      Serial.println(1);
      Serial.write(1);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Authentication");
      lcd.setCursor(1, 1);
      lcd.print("Successfull!");
      delay(1000);
      return true;
    }
    else {
      Serial.println(0);
      Serial.write(0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Entered Pin");
      lcd.setCursor(1, 1);
      lcd.print("Doesn't Match!");
      delay(1000);
      return false;
    }
  }
  else if (rfidTag.equals("89 CB B8 99")) {
    if (pin.equals("89CB")) {
      Serial.println(1);
      Serial.write(1);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Authentication");
      lcd.setCursor(1, 1);
      lcd.print("Successfull!");
      delay(1000);
      return true;
    }
    else {
      Serial.println(0);
      Serial.write(0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Entered Pin");
      lcd.setCursor(1, 1);
      lcd.print("Doesn't Match!");
      delay(1000);
      return false;
    }
  }
  else if (rfidTag.equals("19 80 B8 99")) {
    if (pin.equals("1980")) {
      Serial.println(1);
      Serial.write(1);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Authentication");
      lcd.setCursor(1, 1);
      lcd.print("Successfull!");
      delay(1000);
      return true;
    }
    else {
      Serial.println(0);
      Serial.write(0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Entered Pin");
      lcd.setCursor(1, 1);
      lcd.print("Doesn't Match!");
      delay(1000);
      return false;
    }
  }
  else {
    Serial.println("Scan the Tag again");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Please Scan the");
    lcd.setCursor(1, 1);
    lcd.print("Tag again!");
    delay(1000);
    return false;
  }
}

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  servo.attach(8);
  lcd.begin(16, 2);
  lcd.clear();
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("Welcome!");
  delay(1500);
}

void loop() {
//  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if(digitalRead(ir1)){
    rfidTag = "";
    pin = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Card Scanned");
    lcd.setCursor(1, 1);
    lcd.print("Successfully");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter your Pin");
    delay(1000);
    for (int i = 0; i < 4; i++) {
      customKey = customKeypad.getKey();
      pin += customKey;
    }
    Serial.println(customKey);
  }
//  bool key = Auth(rfidTag, pin);
  if (Auth(rfidTag, pin)) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Place your bag");
    lcd.setCursor(1, 1);
    lcd.print("near outlet!");
    delay(1000);
    if (digitalRead(ir2)) {
      servo.write(55);
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Place next bag");
      delay(1000);
      servo.write(110);
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Place next bag");
      delay(1000);
      servo.write(170);
      delay(5000);
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Place your bag");
      lcd.setCursor(1, 1);
      lcd.print("near outlet!");
    }
  }
  delay(500);
}
