#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const char* mqttServer = "rabbitmq.youngstorage.in";
const int mqttPort = 1883;
const char* mqttUser = "guest";
const char* mqttPassword = "guest";
const char* mqttTopic = "GAS";

const int gasSensorPin = A0;
const int buzzerPin = D0;
const int redLedPin = D4;
const int greenLedPin = D3;

int threshold = 500;

const char* ssid = "project";
const char* password = "no.password";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

LiquidCrystal_I2C lcd(0x3f, 16, 2);
void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  lcd.init();
  lcd.clear(); 
  // Print a message to the LCD.
  lcd.backlight();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
      break;
    }
    delay(1000);
  }
  lcd.setCursor(3, 0);
  lcd.print("WELCOME");
  delay(1500);
}

void loop() {
  int gasValue = analogRead(gasSensorPin);

  char payload[10];
  sprintf(payload, "%d", gasValue);
  mqttClient.publish(mqttTopic, payload);

  if (gasValue > threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Value: ");
    lcd.setCursor(11, 0);
    lcd.print(gasValue);
    lcd.setCursor(0, 1);
    lcd.print("Alert Gas Leaked");
    delay(1000);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Value: ");
    lcd.setCursor(11, 0);
    lcd.print(gasValue);
    lcd.setCursor(0, 1);
    lcd.print("All Works Fine:)");
    delay(1000);
  }

  // Maintain MQTT connection
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

  delay(500);
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
      break;
    }
    delay(1000);
  }
}
