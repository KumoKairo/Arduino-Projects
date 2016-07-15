#define WRITE_PINS_NUMBER 12
#define READ_PINS_NUMBER 5
#define MIDI_BAUD_RATE 256000

int writePins[WRITE_PINS_NUMBER] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int readPins[READ_PINS_NUMBER] = {0, 1, 2, 3, 4};
bool prevNotesState[WRITE_PINS_NUMBER][READ_PINS_NUMBER];

int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
int noteON = 144;//144 = 10010000 in binary, note on command
int noteOFF = 128;//128 = 10000000 in binary, note off command

// Reverse I and J
int notesLookup[READ_PINS_NUMBER][WRITE_PINS_NUMBER] = {
  {96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96},
  {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71},
  {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83},
  {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95}
  };

void setup() 
{
  Serial.begin(MIDI_BAUD_RATE);
  
  for(int i = 0; i < WRITE_PINS_NUMBER; i++)
  { 
    pinMode(writePins[i], OUTPUT);
    digitalWrite(writePins[i], HIGH);
  }

  for(int i = 0; i < WRITE_PINS_NUMBER; i++)
  {
    for(int j = 0; j < READ_PINS_NUMBER; j++)
    {
      prevNotesState[i][j] = false;
    }
  }
}

void loop() 
{
  for(int i = 0; i < WRITE_PINS_NUMBER; i++)
  {
    setAllWritesToLow();
    digitalWrite(writePins[i], HIGH);
    for(int j = 0; j < READ_PINS_NUMBER; j++)
    {
      int val = analogRead(readPins[j]);
      if(val > 500 && prevNotesState[i][j] == false)
      {
        prevNotesState[i][j] = true;
        midiMessage(noteON, notesLookup[j][i], velocity);
      }
      else if(val < 500 && prevNotesState[i][j] == true)
      {
        prevNotesState[i][j] = false;
        midiMessage(noteOFF, notesLookup[j][i], velocity);
      }
    }
  }
}

void setAllWritesToLow(){
  for(int i = 0; i < WRITE_PINS_NUMBER; i++)
  { 
    digitalWrite(writePins[i], LOW);
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiMessage(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

