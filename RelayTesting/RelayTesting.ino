int relay = 13; // Plug the relay into Digital Pin 13

void setup() {
  pinMode(relay, OUTPUT);
}

void loop() {
  digitalWrite(relay, HIGH); // Turn the relay on
  delay(1000); // Wait 1 second
  digitalWrite(relay, LOW); // Turn the relay Off
  delay(1000); // Wait 1 second
}
