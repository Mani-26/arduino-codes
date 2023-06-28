#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "project";
const char* password = "no.password";

const char* mqtt_server = "rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic_temperature = "TEMPERATURE";
const char* mqtt_topic_air = "AIR";

int threshold = 300;
int Tthreshold = 35;

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ6_PIN A0

#define RED_LED_PIN D4
#define GREEN_LED_PIN D5

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      mqttClient.subscribe(mqtt_topic_temperature);
      mqttClient.subscribe(mqtt_topic_air);
    }
    delay(1000);
  }

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();

  int airQuality = analogRead(MQ6_PIN);

  if (temperature >= Tthreshold || airQuality > threshold) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }

  mqttClient.publish(mqtt_topic_temperature, String(temperature).c_str());
  mqttClient.publish(mqtt_topic_air, String(airQuality).c_str());

  mqttClient.loop();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
}
