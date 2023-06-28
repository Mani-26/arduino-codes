#include <DHT.h>  
int threshold = 38;
const int dhtPin = 13;
const int relayPin = 4;
DHT dht(dhtPin, DHT11);
void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(dhtPin, OUTPUT);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  Serial.println(temperature);
  delay(1000);
  if(temperature>threshold)
    digitalWrite(relayPin, LOW);
  else
    digitalWrite(relayPin, HIGH);
}
