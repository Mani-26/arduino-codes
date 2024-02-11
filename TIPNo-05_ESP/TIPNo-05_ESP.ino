#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
String rfidTag1="";
String rfidTag2="";
const char* ssid = "project";
const char* password = "nopassword";
const char* botToken = "6087121870:AAGxW7OmH2KjHmWwSEqWenbvj5wDXfuxJvQ";
#define chatId "-4105310420"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);
int dist=0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
   configTime(0, 0, "pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  bot.sendMessage(chatId, "Bot started up", "");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag1.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag1);
    if(rfidTag1!=rfidTag2){
      dist++;
      String msg="You have covered" +String(dist)+"km. \n Amount you should pay is ₹"+String(dist*50);
      bot.sendMessage(chatId, msg, "");
    }
  }
}
