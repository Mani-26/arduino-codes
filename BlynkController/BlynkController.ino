#define BLYNK_TEMPLATE_ID "TMPL3-iPUaVXX"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "GkC7GYuJZORrJ76voOf71pOPKXFHOiqa"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include<UltraDistSensor.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Lilac";
char pass[] = "@22EC156@22122004";

Servo servo1;
Servo servo2;
BlynkTimer timer;
UltraDistSensor mysensor;

int buzzerPin1 = D0;
int buzzerPin2 = D1;
int ledPin1 = D2;
int ledPin2 = D3;
int servoPin1 = D6;
int servoPin1 = D7;
int dhtPin = A0;
int threshold = 15;

DHT dht(dhtPin, DHT11);

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(buzzerPin1, HIGH);
  } else {
    digitalWrite(buzzerPin1, LOW);
  }
}

BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(buzzerPin2, HIGH);
  } else {
    digitalWrite(buzzerPin2, LOW);
  }
}

BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }
}

//BLYNK_WRITE(V5) {
//  servo1.write(param.asInt());
//}

BLYNK_WRITE(V6) {
  servo2.write(param.asInt());
}

void setup()
{
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  dht.begin();
  mysensor.attach(D4, D5);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  float data = dht.readTemperature();
  Blynk.virtualWrite(V0, data);
  reading = mysensor.distanceInCm();
  if (reading <= threshold) {
    servo1.write(90);
    digitalWrite(buzzerPin1, HIGH);
    delay(800);
    servo1.write(0);
  }
  if (digitalRead(D8)) {
    digitalWrite(buzzerPin2, HIGH);
  }
  Blynk.run();
  timer.run();
}
