const int ldr_pin = A0;
const int led_pin = 9;
int reading;
void setup() {
  pinMode(ldr_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  reading = analogRead(ldr_pin);
  analogWrite(led_pin, reading);
  Serial.println(reading);
  delay(500);
}
