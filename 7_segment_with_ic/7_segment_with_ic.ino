const int latchPin = 5;  //Pin connected to latchPin of 74HC595
const int clockPin = 18; //Pin connected to clockPin of 74HC595
const int dataPin = 23;  //Pin connected to dataPin of 74HC595

//display 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
int datArray[16] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};

void setup()
{
    //set pins to output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}
void loop()
{
    //loop from 0 to 15 (0 to F)
    for (int num = 0; num < 16; num++)
    {
        digitalWrite(latchPin, LOW);                          //ground latchPin and hold low for as long as you are transmitting
        shiftOut(dataPin, clockPin, MSBFIRST, datArray[num]); //SPI shift out

        //return the latch pin high to signal chip that it
        //no longer need dataPin to listen for information
        digitalWrite(latchPin, HIGH); //pull the latchPin clockPin to save the data
        delay(1000);                  //wait for a second
    }
}