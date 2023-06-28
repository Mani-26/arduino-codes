#include <SD.h>
#define SD_ChipSelectPin 4
#include <TMRpcm.h>
#include <SPI.h>
const int flex1 = A1;
const int flex2 = A2;
const int flex3 = A3;
const int flex4 = A4;
long rn;
const int flex5 = A5;
int thumb;
int index;
int middle;
int ring;
int pinky;
TMRpcm tmrpcm;

void setup() {
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(flex4, INPUT);
  pinMode(flex5, INPUT);
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}

void loop() {
    thumb = analogRead(flex1);
    index = analogRead(flex2);
    middle = analogRead(flex3);
    ring = analogRead(flex4);
    pinky = analogRead(flex5);
    //command1
    if (thumb < 50 && index > 50 && middle > 50 && ring > 50 && pinky > 50) {
      tmrpcm.play("Ok.wav");
    }
    //command2
    if (thumb < 50 && index < 50 && middle > 50 && ring > 50 && pinky > 50) {
      tmrpcm.play("Hi.wav");
    }
    //command3
    if (thumb < 50 && index < 50 && middle < 50 && ring > 50 && pinky > 50) {
      tmrpcm.play("HowAreYou.wav");
    }
    //command4
    if (thumb < 50 && index < 50 && middle < 50 && ring > 50 && pinky < 50) {
      tmrpcm.play("IAmFine.wav");
    }
    //command5
    if (thumb > 50 && index > 50 && middle > 50 && ring > 50 && pinky > 50) {
      tmrpcm.play("INeedHelp.wav");
    }
    //command6
    if (thumb > 50 && index < 50 && middle < 50 && ring < 50 && pinky < 50) {
      tmrpcm.play("IHaveAQuestion.wav");
    }
    //command7
    if (thumb > 50 && index < 50 && middle > 50 && ring > 50 && pinky < 50) {
      tmrpcm.play("IKnow.wav");
    }
    //command8
    if (thumb > 50 && index < 50 && middle < 50 && ring > 50 && pinky < 50) {
      tmrpcm.play("IDontKnow.wav");
    }
    //command9
    if (thumb > 50 && index > 50 && middle < 50 && ring < 50 && pinky < 50) {
      tmrpcm.play("Fantastic.wav");
    }
    //command10
    if (thumb < 50 && index > 50 && middle > 50 && ring > 50 && pinky < 50) {
      tmrpcm.play("WeRock.wav");
    }
    delay(1000);
    rn = random(1, 10);
    Serial.println(rn);
    
    //command1
    if (rn == 1) {
      tmrpcm.play("Ok.wav");
    }
    //command2
    if (rn == 2) {
      tmrpcm.play("Hi.wav");
    }
    //command3
    if (rn == 3) {
      tmrpcm.play("HowAreYou.wav");
    }
    //command4
    if (rn == 4) {
      tmrpcm.play("IAmFine.wav");
    }
    //command5
    if (rn == 5) {
      tmrpcm.play("INeedHelp.wav");
    }
    //command6
    if (rn == 6) {
      tmrpcm.play("IHaveAQuestion.wav");
    }
    //command7
    if (rn == 7) {
      tmrpcm.play("IKnow.wav");
    }
    //command8
    if (rn ==8) {
      tmrpcm.play("IDontKnow.wav");
    }
    //command9
    if (rn == 9) {
      tmrpcm.play("Fantastic.wav");
    }
    //command10
    if (rn == 10) {
      tmrpcm.play("WeRock.wav");
    }
    delay(1000);
  }
