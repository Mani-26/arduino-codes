#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "project";
const char* password = "no.password";

// Replace with your MQTT broker details
const char* mqtt_server = "rabbitmq.youngstorage.in";
const int mqtt_port = 1883;
const char* mqtt_user = "guest";
const char* mqtt_password = "guest";
const char* mqtt_topic = "PERCENTAGE";
const char* mqtt_topic1 = "VOLTAGE";

WiFiClient espClient;
PubSubClient client(espClient);

const int batteryPin = A0;
const float voltageDividerRatio = 2.0; // Adjust this value according to your voltage divider circuit

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected to the MQTT broker
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

float readBatteryVoltage() {
  int rawValue = analogRead(A0);
  Serial.print("raw ");
  Serial.println(rawValue);
  float voltage = rawValue * (3.3 / 1023.0) * voltageDividerRatio;
  return voltage;
}

int calculateBatteryPercentage(float voltage) {
  // Adjust these values based on your battery's discharge curve
  const float minVoltage = 3.0;
  const float maxVoltage = 4.2;
  
  int percentage = map(voltage, minVoltage, maxVoltage, 0, 100);
  percentage = constrain(percentage, 0, 100);
  
  return percentage;
}

void sendBatteryStatus(float voltage, int percentage) {
  char voltageString[10];
  char percentageString[4];
  
  dtostrf(voltage, 4, 2, voltageString);
  itoa(percentage, percentageString, 10);
  
  client.publish(mqtt_topic1, voltageString);
  client.publish(mqtt_topic, percentageString);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  float batteryVoltage = readBatteryVoltage();
  int batteryPercentage = calculateBatteryPercentage(batteryVoltage);
  Serial.print("volt ");
  Serial.println(batteryVoltage);
  Serial.print("percent ");
  Serial.println(batteryPercentage);
  sendBatteryStatus(batteryVoltage, batteryPercentage);
  
  delay(1000); // Send the battery status every minute
}
