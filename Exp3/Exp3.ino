int vib_pin=A0;
int reading;
void setup() {
  Serial.begin(9600);
  pinMode(vib_pin,INPUT);
}

void loop() {
  reading=analogRead(vib_pin);
  Serial.println(reading);
  delay(500);
}
