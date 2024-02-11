#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String rfidTag;
String pin;
char customKey;

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfidTag = "";
    pin = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag);
    for (int i = 0; i < 4; i++) {
      customKey = customKeypad.getKey();
      pin += customKey;
    }
    Serial.println(customKey);
  }
  Auth();
}

void Auth(rfidTag, pin) {
  pin = pin.toUpperCase();
  switch (rfidTag) {
    case "43 21 26 AC": {
        if (pin == 4321) {
          Serial.println(1);
          Serial.write(1);
        }
        else {
          Serial.println(0);
          Serial.write(0);
        }
        break;
      }
    case "F3 76 54 A8": {
        if (pin == F376) {
          Serial.println(1);
          Serial.write(1);
        }
        else {
          Serial.println(0);
          Serial.write(0);
        }
        break;
      }
    case "03 38 5E A8": {
        if (pin == 0338) {
          Serial.println(1);
          Serial.write(1);
        }
        else {
          Serial.println(0);
          Serial.write(0);
        }
        break;
      }
    case "89 CB B8 99": {
        if (pin == 89CB) {
          Serial.println(1);
          Serial.write(1);
        }
        else {
          Serial.println(0);
          Serial.write(0);
        }
        break;
      }
    case "19 80 B8 99": {
        if (pin == 1980) {
          Serial.println(1);
          Serial.write(1);
        }
        else {
          Serial.println(0);
          Serial.write(0);
        }
        break;
      }
    default:
      Serial.println("Scan the Tag again");
      break;
  }
}
