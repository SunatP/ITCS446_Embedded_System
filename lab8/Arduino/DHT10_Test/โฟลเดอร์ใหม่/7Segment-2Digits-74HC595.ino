const int latchPin = 5; //Pin connected to latchPin of 74HC595
const int clockPin = 18; //Pin connected to clockPin of 74HC595
const int dataPin = 23; //Pin connected to dataPin of 74HC595 

const int ca_d1 = 32;
const int ca_d2 = 33;

int datArray[16] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};

void setup ()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(ca_d1,OUTPUT);
  pinMode(ca_d2,OUTPUT);
}
void loop()
{
  digitalWrite(ca_d1, HIGH);
  digitalWrite(ca_d2, HIGH);
  for (int i = 0; i < 16; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      for (int k = 0; k < 25; k++)
      {
        digitalWrite(ca_d2, HIGH);
        writeNumber(i);
        digitalWrite(ca_d1, LOW);
        delay(10);
        digitalWrite(ca_d1, HIGH);
        writeNumber(j);
        digitalWrite(ca_d2, LOW);
        delay(10);
      }
    }
  }
}

void writeNumber(int num)
{
  digitalWrite(latchPin, LOW); //ground latchPin and hold low for as long as you are transmitting
  shiftOut(dataPin, clockPin, LSBFIRST, datArray[num]); //SPI shift out
  digitalWrite(latchPin, HIGH); //pull the latchPin clockPin to save the data
}
