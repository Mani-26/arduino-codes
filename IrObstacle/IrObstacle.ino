#define sensor_l 2 
#define sensor_c 3 
#define sensor_r 4 
#define lf 5
#define lb 6
#define rf 7
#define rb 8

void front() {
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
}
void left() {
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
}
void right() {
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
}
void back() {
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(sensor_l, INPUT);
  pinMode(sensor_c, INPUT);
  pinMode(sensor_r, INPUT);
}

void loop() {
  int sl = digitalRead(sensor_l);
  int sc = digitalRead(sensor_c);
  int sr = digitalRead(sensor_r);
  
  if (sl == 1 && sc == 1 && sr == 1)
    front();
  if(sc == 1)
    front();
  if(sc == 0)
    back();
  if (sl == 0 && sc == 0 && sr == 0)
    back();
  if (sl == 0 && (sc == 1 || sc == 0) && sr == 1)
    left();
  if (sl == 1 && (sc == 1 || sc == 0) && sr == 0)
    right();
}
