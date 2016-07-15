int pin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT); 
  digitalWrite(pin, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(pin));
}
