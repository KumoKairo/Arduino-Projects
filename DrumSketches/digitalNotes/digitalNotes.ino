const int velocity = 100;//velocity of MIDI notes, must be between 0 and 127

const int noteON = 144;//144 = 10010000 in binary, note on command
const int noteOFF = 128;//128 = 10000000 in binary, note off command

const int ledPin = 13;

int buttonPins[] = {2, 3, 4};
int prevButtonStates[] = {LOW, LOW, LOW};
int notes[] = {125, 81, 82};

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(38400);

  pinMode(ledPin, OUTPUT);

  for(int i = 0; i < 3; i++){
    pinMode(buttonPins[i], INPUT);
  }
}

void loop() {  
  for(int i = 0; i < 1; i++){
    int newState = digitalRead(buttonPins[i]);
    if(newState != prevButtonStates[i]){
      if(newState == HIGH)
      {
        midiMessage(noteON, notes[i], velocity);
      }
      else{
        midiMessage(noteOFF, notes[i], velocity);
      }
    }
    prevButtonStates[i] = newState;
    delay(20);
  }
}


//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiMessage(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
