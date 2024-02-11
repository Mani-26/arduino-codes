#include<UltraDistSensor.h>
UltraDistSensor mysensor;
float reading;
void setup() {
  Serial.begin(9600);
  mysensor.attach(7, 8);//Trigger pin , Echo pin
}

void loop() {
  reading = mysensor.distanceInCm();
  Serial.println(reading); 
  delay(500);
} 
