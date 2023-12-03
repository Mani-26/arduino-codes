#define BLYNK_TEMPLATE_ID "TMPL3OPv_R-Rb"
#define BLYNK_TEMPLATE_NAME "GasDetection"
#define BLYNK_AUTH_TOKEN "GuXObShqMzKk9yhX1YFuZWNX53YRUFM9"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "project";
char pass[] = "nopassword";
int GasSensor = A0;
int data = 0;
int sensorThres = 100;
BlynkTimer timer;
void sendSensor() {
  int data = analogRead(GasSensor);
  Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);
  if (data > 90) {
    Blynk.logEvent("gasleakagealert", "Alert! Gas Leakage Detected..!");
  }
}
void setup() {
  pinMode(GasSensor, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2500L, sendSensor);
}
void loop() {
  Blynk.run();
  timer.run();
}
