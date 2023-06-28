#include <Servo.h>
Servo servo;
int ir_in = 2;
int ir_out = 3;
int count = 0;
int total = 5;
void setup()
{
  Serial.begin(9600);
  pinMode(ir_in, INPUT);
  pinMode(ir_out, INPUT);
  servo.attach(5);
  servo.write(0);
}
void loop() {
  if (digitalRead (ir_in) == 0 && count != total )
  {
    servo.write(90);
    delay(3000);
    servo.write(0);
    count++;
  }
  else if (digitalRead (ir_out) == 0 && count != 0)
  {
    servo.write(90);
    delay(3000);
    servo.write(0);
    count--;
  }
  else
    servo.write(0);
  delay(1000);
}
