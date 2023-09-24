#include<UltraDistSensor.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define L1 2
#define R1 4
#define L2 3
#define R2 5
//#define EN1 A1
//#define EN2 A2
UltraDistSensor mysensor;
int distance;
int minDistance = 10;
String rfidTag;
//53235b0e  //a3ae8fa6
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  //  pinMode(EN1, OUTPUT);
  //  pinMode(EN2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R2, OUTPUT);
  mysensor.attach(7, 6);
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
    distance = mysensor.distanceInCm();
    Serial.println(distance);
    //    Serial.println(motorSpeed);
    //    analogWrite(EN1, motorSpeed);
    //    analogWrite(EN2, motorSpeed);
    if (distance < minDistance) {
      stopCar();
      delay(100);
      turnRight();
      delay(100);
      distance = mysensor.distanceInCm();
      //      if (distance < minDistance) {
      //        turnLeft();
      //        delay(200);
      //        moveForward();
      //        distance = mysensor.distanceInCm();
      if (distance < minDistance) {
        back();
        delay(100);
        turnLeft();
        delay(200);
        distance = mysensor.distanceInCm();
        if (distance < minDistance) {
          stopCar();
        }
        else {
          moveForward();
        }
      }
      else {
        moveForward();
      }
      //      }
      //      else {
      //        moveForward();
      //      }
    }
  
  else {
    moveForward();
  }
  delay(100);
}
}


void moveForward() {
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, HIGH);
  Serial.println("FORWARD");
}
void back() {
  digitalWrite(L2, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("BACK");
}
void turnRight() {
  digitalWrite(L2, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, HIGH);
  Serial.println("RIGHT");
}
void turnLeft() {
  digitalWrite(L2, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, LOW);
  Serial.println("LEFT");
}
void stopCar() {
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  Serial.println("STOP");
}
