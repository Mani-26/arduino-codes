int sensorPin = 2;
int ledPin = 3;
int reading;
void setup() {
  Serial.begin(9600);
  pinMode (sensorPin, INPUT);
  pinMode (ledPin, INPUT);
}

void loop() {
  reading = digitalRead(sensorPin);
  if(reading == HIGH){
     digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
  delay(500);
}
