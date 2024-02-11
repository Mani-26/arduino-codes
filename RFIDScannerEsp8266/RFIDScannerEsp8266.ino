#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define SS_PIN 11
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
String rfidTag1 = "";
const char* ssid = "project";
const char* password = "nopassword";


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfidTag1 = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag1.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag1);
  }
  delay(1000);
}
