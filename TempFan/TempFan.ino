#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
const char* ssid = "project";
const char* password = "no.password";
int threshold = 30;
const char* mqtt_server = "rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic = "TEMPERATURE";
const int dhtPin = D0;
const int buzzerPin = D2;
const int redLedPin = D3;
const int greenLedPin = D4;
const int motorPin = D5;
DHT dht(dhtPin, DHT11);
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  dht.begin();
}
void loop() {
  float temperature = dht.readTemperature();
  char temperatureStr[6];
  dtostrf(temperature, 4, 2, temperatureStr);
  client.publish(mqtt_topic, temperatureStr);
  if (temperature >= threshold) {
    digitalWrite(motorPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(motorPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
  }
  client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
}