#define L1 2
#define R1 4
#define L2 3
#define R2 5
void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(L2, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R1, HIGH);
}
