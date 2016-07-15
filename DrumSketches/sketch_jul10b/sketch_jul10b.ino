//MIDI baud rate
#define SERIAL_RATE 38400
#define NOTE_THRESHOLD 50
#define AVERAGE_NEIGHBOURS 5

int averages[AVERAGE_NEIGHBOURS];

void setup() {
  Serial.begin(SERIAL_RATE);
}

bool isOnCooldown = false;
int prevSmoothedValue = 0;

void loop() {
  int val = analogRead(0);

  for(int i = 0; i < AVERAGE_NEIGHBOURS; i++)
  {
    averages[i] = averages[i + 1];
  }
  
  averages[AVERAGE_NEIGHBOURS - 1] = val;

  int sum = 0;

  for(int i = 0; i < AVERAGE_NEIGHBOURS; i++)
  {
    sum += averages[i];
  }

  int smoothedValue = sum / AVERAGE_NEIGHBOURS;
  
  if(smoothedValue > NOTE_THRESHOLD){

      if(smoothedValue - prevSmoothedValue < 0 && !isOnCooldown){
        isOnCooldown = true;
        midiNoteOn(70, smoothedValue / 8);
      }

      prevSmoothedValue = smoothedValue;
  }
  else if (smoothedValue == 0 && isOnCooldown){
    isOnCooldown = false;
  }
}

void midiNoteOn(byte note, byte midiVelocity)
{
  if(midiVelocity > 127){
    midiVelocity = 127;
  }
  Serial.write(0x90);
  Serial.write(note);
  Serial.write(midiVelocity);
}
