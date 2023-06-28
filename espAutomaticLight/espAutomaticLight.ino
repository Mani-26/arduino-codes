#include <Servo.h>
#define TRIGGER_PIN1 D1
#define ECHO_PIN1 D0
#define TRIGGER_PIN2 D3
#define ECHO_PIN2 D2
#define SERVO_PIN D4

int lights = 8;
long dis_a = 0, dis_b = 0;
int flag1 = 0, flag2 = 0;
int person = 0;

Servo servo;

void ultra_read(int pin_t, int pin_e, long &ultra_time) {
  long time;
  pinMode(pin_t, OUTPUT);
  pinMode(pin_e, INPUT);
  digitalWrite(pin_t, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_t, HIGH);
  delayMicroseconds(10);
  time = pulseIn (pin_e, HIGH);
  ultra_time =  time / 29 / 2;
}

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(0);
  pinMode(lights, OUTPUT);
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
}

void loop() {
  ultra_read(TRIGGER_PIN1, ECHO_PIN1, dis_a); delay(40);
  ultra_read(TRIGGER_PIN2, ECHO_PIN2, dis_b); delay(40);
  Serial.print("da:"); Serial.println(dis_a);
  Serial.print("db:"); Serial.println(dis_b);
  if (dis_a < 90 && flag1 == 0) {
    flag1 = 1;
    if (flag2 == 0)
      person = person + 1;
  }
  if (dis_b < 90 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0)
      person = person - 1;
  }
  if (dis_a > 90 && dis_b > 90 && flag1 == 1 && flag2 == 1) {
    flag1 = 0, flag2 = 0;
    delay(1000);
  }

  if (person > 0) {
    digitalWrite(lights, HIGH);
    servo.write(90);
  }
  else {
    digitalWrite(lights, LOW);
    servo.write(0);
  }
}
