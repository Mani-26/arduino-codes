#include <DHT.h>
#define sensorPin 4
DHT dht(sensorPin, DHT11);
float reading;

void  setup()
{
  Serial.begin(9600);
  dht.begin();  
}

void loop()
{
  reading = dht.readTemperature();
  Serial.print("Temperature  (C): ");
  Serial.println(reading);
  delay(1000);
}
