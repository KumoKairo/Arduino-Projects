int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
int noteON = 144;//144 = 10010000 in binary, note on command
int noteOFF = 128;//128 = 10000000 in binary, note off command

int piezoPin = 0;

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(38400);
}

void loop() {
  int analog0 = analogRead(piezoPin);

  int normalizedVelocity = analog0;
  if(normalizedVelocity > 127)
  {
    normalizedVelocity = 127;
  }
  
  if(analog0 > 30)
  {
    midiMessage(noteON, 125, normalizedVelocity);
    delay(50);
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiMessage(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
