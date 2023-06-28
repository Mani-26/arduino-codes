#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "project";
const char* password = "no.password";

// MQTT broker details
const char* mqtt_server = "http://rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic_soil = "MOISTURE";

// Create an instance of WiFiClient
WiFiClient wifiClient;

// Create an instance of PubSubClient class
PubSubClient mqttClient(wifiClient);


// Create an instance of the soil moisture sensor
const int soil_moisture_pin = A0;
const int motor = D5;

void setup() {
  // Start Serial communication
  Serial.begin(9600);

  // Start the WiFi connection
  WiFi.begin(ssid, password);

  // Wait for the WiFi connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  IPAddress staticIP(192, 168, 43, 143);
  IPAddress gateway(192, 168, 43, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(staticIP, gateway, subnet);
  
  // Print WiFi connection details
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT broker
  mqttClient.setServer(mqtt_server, mqtt_port);

  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("MQTT broker connection failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
  pinMode(motor, OUTPUT);
}

void loop() {
  // Read soil moisture value
  int moisture = analogRead(soil_moisture_pin);
//  int moistureValue = (1-((moisture-1)/1024))*100;
  // Publish temperature and humidity values to MQTT broker
  if (mqttClient.connected()) {
    String moisture_string = String(moisture);
    mqttClient.publish(mqtt_topic_soil, moisture_string.c_str());
    Serial.print("Soil moisture value: ");
    Serial.print(moisture_string);
    Serial.println("%");
    Serial.println(moisture);
    if(moisture > 600 ){
      digitalWrite(motor, LOW);
      delay(500);
      Serial.println("Motor ON");
    }
    else{
      digitalWrite(motor, HIGH);
      delay(500);
      Serial.println("Motor OFF");
    }
  }

  // Handle incoming MQTT messages
  mqttClient.loop();

  // Wait for 2 seconds before sending the next MQTT message
  delay(2000);
}