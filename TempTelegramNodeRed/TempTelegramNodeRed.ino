#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN D8
#define DHTTYPE DHT11
#define buzzerPin D7
#define RED_LED D3
#define YELLOW_LED D6
#define GREEN_LED D4
#define MOTOR_PIN D5

const char* ssid = "IoT";
const char* password = "password";

const char* botToken = "6161536747:AAHOaSCa-1NfifG_mL5N01rMMw4T7Kh99Wo";
#define chatId "-4072800075"

const char* mqtt_server = "rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic1 = "TEMPERATURE";
const char* mqtt_topic2 = "HUMIDITY";
LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);

WiFiClient espClient;
PubSubClient client(espClient);

void publishTemperature(float temperature,float humidity) {
  if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    Serial.println("Connected to MQTT broker");
    String payload = String(temperature);
    client.publish(mqtt_topic1, payload.c_str());
    Serial.println("Published temperature to MQTT");
    client.disconnect();
  } else {
    Serial.println("MQTT connection failed");
  }
}

void displayTemperature(float temperature,float humidity) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
}

void sendTelegramAlert(float temperature,float humidity) {
  String message = "🛑High temperature alert!🛑 \n ⚡Temperature is " + String(temperature) + "°C♨"+"\n  ♨Humidity is " + String(humidity) + "⚡";
  bot.sendMessage(chatId, String(message), "");
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages if needed
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  dht.begin();
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  configTime(0, 0, "pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(2500);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  delay(500);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(MOTOR_PIN, HIGH);
  delay(500);
  digitalWrite(MOTOR_PIN, LOW);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.println(temperature);
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor");
    delay(2000);
    return;
  }
  publishTemperature(temperature,humidity);
  displayTemperature(temperature,humidity);

  if (temperature > 40.0) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(MOTOR_PIN, HIGH);
    sendTelegramAlert(temperature,humidity);
    delay(100);
  } else if (temperature >= 30.0 && temperature <= 40.0) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(MOTOR_PIN, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(MOTOR_PIN, LOW);
  }
  delay(1000);
}
