#include <Stepper.h>
const int stepsPerRevolution = 2048;//full rotation
Stepper myStepper = Stepper(stepsPerRevolution, 11, 9, 10, 8);//in1 in2 in3 in4

void setup() {
}

void loop() {
  // 5 RPM forward
  myStepper.setSpeed(5);
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // 5 RPM reverse
  myStepper.setSpeed(10);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
