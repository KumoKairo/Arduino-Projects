void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5); 
  int eightIn = digitalRead(8);
  Serial.println(eightIn);
}
