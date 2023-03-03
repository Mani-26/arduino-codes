Char data = 0;

Void setup()

{

Serial.begin(9600);

pinMode(8, OUTPUT);

pinMode(9, OUTPUT);

pinMode(10, OUTPUT);

pinMode(11, OUTPUT);

}

Void loop()

{

If(Serial.available() > 0)

{

Data = Serial.read();

Serial.print(data);

Serial.print(“\n”);

If(data == ‘A’)

digitalWrite(8, HIGH);

else if(data == ‘a’)

digitalWrite(8, LOW);

if(data == ‘B’)

digitalWrite(9, HIGH);

else if(data == ‘b’)

digitalWrite(9, LOW);

if(data == ‘C’)

digitalWrite(10, HIGH);

else if(data == ‘c’)

digitalWrite(10, LOW);
if(data == ‘D’)

digitalWrite(11, HIGH);

else if(data == ‘d’)

digitalWrite(11, LOW);

}

}
