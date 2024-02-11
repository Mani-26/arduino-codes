#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include<UltraDistSensor.h>
UltraDistSensor ultrasonic;
const char* ssid = "project";
const char* password = "nopassword";
const char* botToken = "6162858218:AAE_x-8bXZWFIhcacngS-8KP-brlT8anvVs";
#define chatId "-4031245892"
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);
String msg = "";
SoftwareSerial espSerial(1, 3);

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  ultrasonic.attach(4, 5);//Trigger pin , Echo pin
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
  int distance = ultrasonic.distanceInCm();
  delay(400);
  Serial.println(distance);
  if (Serial.available()) {
    Serial.write(distance);
  }
  if (distance < 20) {
    bot.sendMessage(chatId, "Intruder detected", "");
  }
  delay(1000);
}
