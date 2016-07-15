const int ledPin = 13;
const int buttonPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
}

void loop() {  
  digitalWrite(ledPin, digitalRead(buttonPin));
}
