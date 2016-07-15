//MIDI baud rate
#define SERIAL_RATE 256000
#define NOTE_THRESHOLD 25
#define HARD_THRESHOLD 8
#define HARD_THRESHOLD_TOLERANCE 2
#define AVERAGE_NEIGHBOURS 20

int averages[AVERAGE_NEIGHBOURS];

int totalGradient = 0;
int numberOfTakes = 0;

void setup() {
  Serial.begin(SERIAL_RATE);
}

bool isOnCooldown = false;
int prevSmoothedValue = 0;

void loop() {
  int val = analogRead(0);
  
  if (val <= HARD_THRESHOLD) {
    return;
  }

  for (int i = 0; i < AVERAGE_NEIGHBOURS; i++)
  {
    averages[i] = averages[i + 1];
  }

  averages[AVERAGE_NEIGHBOURS - 1] = val;

  int sum = 0;

  for (int i = 0; i < AVERAGE_NEIGHBOURS; i++)
  {
    sum += averages[i];
  }

  int smoothedValue = sum / AVERAGE_NEIGHBOURS;

  int deltaSmoothVal = smoothedValue - prevSmoothedValue;

  totalGradient += deltaSmoothVal;

  if (deltaSmoothVal < 0 && totalGradient > NOTE_THRESHOLD && !isOnCooldown) {
    isOnCooldown = true;
    midiNoteOn(70, totalGradient);
  }
  
  if (deltaSmoothVal > 0 && totalGradient < NOTE_THRESHOLD) {
    isOnCooldown = false;
    totalGradient = 0;
    numberOfTakes = 0;
  } 

  prevSmoothedValue = smoothedValue;
}

void midiNoteOn(byte note, byte midiVelocity)
{
  if (midiVelocity > 127) {
    midiVelocity = 127;
  }
  Serial.write(0x90);
  Serial.write(note);
  Serial.write(midiVelocity);
  //delay(100);
}
