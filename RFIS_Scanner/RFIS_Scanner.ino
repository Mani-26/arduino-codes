#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
String rfidTag;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}
void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfidTag = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag);
  }
}