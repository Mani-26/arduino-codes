#include<UltraDistSensor.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define L1 2
#define R1 4
#define L2 3
#define R2 7
#define EN1 6
#define EN2 5

UltraDistSensor mysensor;
int distance;
const int km = 100;
int minDistance = 25;
String rfidTag;
int r = 0;
//53235b0e  //a3ae8fa6

void moveForward() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, HIGH);
  Serial.println("FORWARD");
}
void back() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("BACK");
  delay(350);
}
void turnRight() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, HIGH);
  Serial.println("RIGHT");
  delay(250);
}
void turnLeft() {
  analogWrite(EN1, km);
  analogWrite(EN2, km);
  digitalWrite(L2, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, LOW);
  Serial.println("LEFT");
  delay(250);
}
void stopCar() {
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("STOP");
  delay(500);
}
void obstacle() {
  distance = mysensor.distanceInCm();
  Serial.println(distance);
  if (distance < minDistance) {
    stopCar();
    back();
    stopCar();
    if (r == 0) {
      turnRight();
      r = 1;
    }
    else {
      turnLeft();
      r = 0;
    }
    obstacle();
  }
  else {
    moveForward();
  }
}
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R2, OUTPUT);
  mysensor.attach(A2, A3);
  Serial.println("Car Started!");
  Serial.println("Ready to Read");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfidTag = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(rfidTag);
  }
  rfidTag.toUpperCase();
  if (rfidTag == "A3AE8FA6") {
    obstacle();
  }
  else if("53235B0E"){
    stopCar();
  }
}
