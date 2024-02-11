#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define SS_PIN D4  // Define the SS_PIN for the RFID module
#define RST_PIN D3 // Define the RST_PIN for the RFID module
#define IR_SENSOR_PIN D2 // Define the pin for the IR sensor
#define RELAY_PIN D1 // Define the pin for the relay (assuming NodeMCU pin numbers)

MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ration Dispenser");
  delay(2000);
  connectToWiFi();
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.print("Card ID:");
    printCardID();
    if (digitalRead(IR_SENSOR_PIN) == HIGH) {
      activateRelay();
    }
    delay(2000);
    lcd.clear();
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay if no RFID card is present
  }
}

void printCardID() {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    lcd.setCursor(i % 16, i / 16);
    lcd.print(String(mfrc522.uid.uidByte[i], HEX));
  }
}

void connectToWiFi() {
  const char* ssid = "project";
  const char* password = "nopassword";

  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void activateRelay() {
  digitalWrite(RELAY_PIN, HIGH); // Turn on the relay when both RFID and IR are detected
}
