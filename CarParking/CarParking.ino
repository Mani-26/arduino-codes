#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* ssid = "project";
const char* password = "no.password";

const char* mqtt_server = "rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic = "COUNT";

const int MAX_CARS = 3; // Maximum number of cars allowed inside

int carCount = 0; // Current count of cars inside

Servo servo;

const int ir_in = D3; // IR sensor pin 1
const int ir_out = D2; // IR sensor pin 2

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  pinMode(ir_in, INPUT);
  pinMode(ir_out, INPUT);
  servo.attach(D4);
  servo.write(0);
  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (digitalRead (ir_in) == 0 && carCount != MAX_CARS )
  {
    servo.write(180);
    delay(5000);
    servo.write(0);
    carCount++;
  }
  else if (digitalRead (ir_out) == 0 && carCount != 0)
  {
    servo.write(180);
    delay(5000);
    servo.write(0);
    carCount--;
  }
  else
    servo.write(0);
    
  // Publish car count to MQTT broker
  publishCount();
  delay(1000);
}

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void publishCount() {
  char msg[10];
  snprintf(msg, sizeof(msg), "%d", carCount);
  client.publish(mqtt_topic, msg);
}


void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages if needed
}
