#include "DHT.h"
#define DHTTYPE DHT10
#define SegSource_Intlookup 0
#define SegSource_LEDInit 1
#define SegSource_LEDTempPre 2
#define SegSource_LEDHumPre 3
#define BUTTON_PIN_BITMASK 0x200000000                                // 2^33 in hex
int Digits[] = {15, 2, 4, 16, 17, 3, 23, 13, 12, 14, 27, 26, 25, 33}; // only define the number of pins for the number of digits to be displayed
int NumberDigits = sizeof(Digits) / sizeof(14);                       // automatically store number of defined pins for later use
DHT dht(0, DHTTYPE);                                                  // The first parameter is pin, which is required for DHT11 and DHT22, but not required for DHT10 because it's i2c.
/**
DHT 10 Pin : VDD(1) Pin 3v3, SDA(2) Pin 21, GND(3) Pin GND, SCL(4) Pin 22 
LED RGB Pin Define : Red Pin 5, Green Pin 18, Blue Pin 19
--------------------------------------------
HI -> Turn On
Digit 2 B C turn on
Digit 1 F E G B C turn on
LO -> Turn Off
Digit 2 A B C D E F turn on
Digit 1 F E D turn on
--------------------------------------------
  - Digit 2 -
  Anode A (11) -> D15
  Anode B (10) -> D2
  Anode C (8) -> D4 
  Anode D (6) -> RX2 (D16)
  Anode E (5) -> TX2 (D17)
  Anode F (12) -> RX0 (D3)
  Anode G (7) -> D23
  - Digit 1 -
  Anode A (16) -> D13
  Anode B (15) -> D12
  Anode C (3) -> D14
  Anode D (2) -> D27
  Anode E (1) -> D26
  Anode F (18) -> D25
  Anode G (17) -> D33
--------------------------------------------
**/
int buzzer = 32; /** init Buzzer **/
int SW = 35;     /** init SW **/
/** init LED RGB**/
int Led_Red = 5;
int Led_Green = 18;
int Led_Blue = 19;
/** Digit 2**/
int A_2 = 15;
int B_2 = 2;
int C_2 = 4;
int D_2 = 16;
int E_2 = 17;
int F_2 = 3;
int G_2 = 23;
/** Digit 1 **/
int A_1 = 13;
int B_1 = 12;
int C_1 = 14;
int D_1 = 27;
int E_1 = 26;
int F_1 = 25;
int G_1 = 33;
/** Init Array for send an I/O values **/
int arr[14] = {A_2, B_2, C_2, D_2, E_2, F_2, G_2, A_1, B_1, C_1, D_1, E_1, F_1, G_1};
int num_digit1;
int num_digit2;
void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 is ready");
  Serial.println("DHT10 is ready");
  Wire.begin();
  dht.begin();
  pinMode(SW, INPUT);
  pinMode(Led_Red, OUTPUT);
  pinMode(Led_Green, OUTPUT);
  pinMode(Led_Blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  int i;
  for (i = 0; i < 14; i++)
  {
    pinMode(arr[i], OUTPUT);
  }
  displayInit();
  ready();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 1); // Set Pin 35 for Switch button to wake up the ESP32
}
void ready(void)
{
  unsigned char j;
  for (j = 0; j < 14; j++) // Turn off remaining segments
    digitalWrite(arr[j], 0);
  /** Turn on **/
  digitalWrite(A_2, 1);
  digitalWrite(F_2, 1);
  digitalWrite(E_2, 1);
  digitalWrite(D_2, 1);
  digitalWrite(G_2, 1);
  digitalWrite(G_1, 1);
  digitalWrite(E_1, 1);
  delay(1500);
}
void digital_hi(void)
{
  unsigned char j;
  for (j = 0; j < 14; j++) // Turn off remaining segments
    digitalWrite(arr[j], 0);
  /** Turn on **/
  digitalWrite(B_2, 1);
  digitalWrite(C_2, 1);
  digitalWrite(B_1, 1);
  digitalWrite(C_1, 1);
  digitalWrite(E_1, 1);
  digitalWrite(F_1, 1);
  digitalWrite(G_1, 1);
}
void digital_lo(void)
{
  unsigned char j;
  for (j = 0; j < 14; j++) // Turn off remaining segments
    digitalWrite(arr[j], 0);
  /** Turn on **/
  digitalWrite(A_2, 1);
  digitalWrite(B_2, 1);
  digitalWrite(C_2, 1);
  digitalWrite(D_2, 1);
  digitalWrite(E_2, 1);
  digitalWrite(F_2, 1);
  digitalWrite(D_1, 1);
  digitalWrite(E_1, 1);
  digitalWrite(F_1, 1);
}
void beep_3times(void)
{
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(250);
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(250);
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(250);
}
void beep_5times(void)
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}
void digital_off(void)
{
  unsigned char j;
  for (j = 0; j < 14; j++) // Turn off remaining segments
    digitalWrite(arr[j], 0);
  /** Turn on **/
  digitalWrite(A_2, 1);
  digitalWrite(F_2, 1);
  digitalWrite(G_2, 1);
  digitalWrite(E_2, 1);
  digitalWrite(E_1, 1);
  digitalWrite(G_1, 1);
  digitalWrite(C_1, 1);
  digitalWrite(D_1, 1);
  delay(2000);
}
void digital_on(void)
{
  unsigned char j;
  for (j = 0; j < 14; j++) // Turn off remaining segments
    digitalWrite(arr[j], 0);
  /** Turn on **/
  digitalWrite(E_2, 1);
  digitalWrite(F_2, 1);
  digitalWrite(A_2, 1);
  digitalWrite(B_2, 1);
  digitalWrite(C_2, 1);
  digitalWrite(G_1, 1);
  digitalWrite(C_1, 1);
  digitalWrite(D_1, 1);
  digitalWrite(E_1, 1);
  delay(2000);
}
// Intlookup defines the active segments per number
int Intlookup[10] = {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111};
// LEDInit defines segments for init display
int LEDInit[8] = {B00000001, B00000010, B01000000, B00010000, B00001000, B00000100, B01000000, B00100000};
void displayInit()
{
  for (int r = 0; r < 4; r++) // Repeat. Number of times the Init animation is repeated
  {
    for (int n = 0; n < 8; n++) // Number of Segments. Number of elements in the init animation (8 for a full figure of 8)
    {
      for (int d = 0; d < 250; d++) // Multiplex. Multiplex repeat the display of the current lit segment in the Init animation.
      {
        showdigit(SegSource_LEDInit, 1, n); // SegSource_LEDInit is defined as 1. On the first run through, this will therefore call showdigit(1, 1, 0)
        showdigit(SegSource_LEDInit, 0, n);
      }
      delay(100); // Delay. Delay before moving on to light the next part of the Init animation
    }
  }
}
void showdigit(int source, int digit, int value)
{
  int seg = getsegs(source, value);
  for (int i = 0; i < 14; i++) // clear all segments to avoid background flickering
    digitalWrite(arr[i], 1);
  for (int i = 0; i < NumberDigits; i++) // address selected digit only
  {
    // Select the correct digit for this display. Each digit will be rapidly turned on and off through multiplexing to give the illusion that both digits are lit
    // This code controls which of the two Anodes on a two-digit 7 Segment LED is active.
    if (i == digit)
      digitalWrite(arr[i], 0); // Reversed as now using PNP transistors so need to set to low to activate the digit rather than high
    else
      digitalWrite(arr[i], 1); // Reversed - as above
  }
  // Select the correct segment for display. This code controls which of the eight Cathodes are active based on the segments to be displayed.
  for (int i = 0; i < 14; i++) // select correct segments
  {
    if (bitRead(seg, i) == 1)
      digitalWrite(arr[i], 0);
    else
      digitalWrite(arr[i], 1);
  }
}
int getsegs(int source, int value)
{
  switch (source) // source of segment switches
  {
  case SegSource_Intlookup:
    return Intlookup[value];
    break;
  case SegSource_LEDInit:
    return LEDInit[value];
    break;
  }
}
void loop()
{
  float temp_hum_val[2] = {0};
  float temp = dht.readTempAndHumidity(temp_hum_val); // Read Temperature
  int state;
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  state = digitalRead(SW);
  if (state == HIGH)
  {
    digital_on();
    delay(1000);
    if (!dht.readTempAndHumidity(temp_hum_val))
    {
      Serial.print("Humidity: ");
      Serial.print(temp_hum_val[0]);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(temp_hum_val[1]);
      Serial.println(" *C");
      // Serial.print(num_digit2);
      if (temp_hum_val[0] >= 75)
      {
        digitalWrite(Led_Red, LOW);    // LED will be switched off
        digitalWrite(Led_Green, HIGH); // LED will be switched on
        digitalWrite(Led_Blue, HIGH);  // LED will be switched on
        digital_hi();
        beep_5times();
        delay(1500);
      }
      else if (temp_hum_val[0] >= 70 && temp_hum_val[0] < 75)
      {
        // Red
        digitalWrite(Led_Red, LOW);    // LED will be switched off
        digitalWrite(Led_Green, HIGH); // LED will be switched on
        digitalWrite(Led_Blue, LOW);   // LED will be switched off
        digital_hi();
        beep_3times();
        delay(1500);
      }
      else if (temp_hum_val[0] >= 50 && temp_hum_val[0] < 70)
      {
        // Blue
        digitalWrite(Led_Red, LOW);   // LED will be switched off
        digitalWrite(Led_Green, LOW); // LED will be switched off
        digitalWrite(Led_Blue, HIGH); // LED will be switched on
        digital_hi();
        delay(1500);
      }
      else if (temp_hum_val[0] >= 30 && temp_hum_val[0] < 50)
      {
        // Green
        digitalWrite(Led_Red, HIGH);  // LED will be switched on
        digitalWrite(Led_Green, LOW); // LED will be switched off
        digitalWrite(Led_Blue, LOW);  // LED will be switched off
        digital_lo();
        delay(1500);
      }
      else if (temp_hum_val[0] >= 10 && temp_hum_val[0] < 30)
      {
        // White
        digitalWrite(Led_Red, HIGH);   // LED will be switched on
        digitalWrite(Led_Green, HIGH); // LED will be switched on
        digitalWrite(Led_Blue, HIGH);  // LED will be switched on
        digital_lo();
        delay(1500);
      }
      else
      {
        digitalWrite(Led_Red, LOW);   // LED will be switched off
        digitalWrite(Led_Green, LOW); // LED will be switched off
        digitalWrite(Led_Blue, LOW);  // LED will be switched off
        digital_lo();
        delay(1500);
        Serial.println("Failed to get temprature and humidity value.");
      }
      delay(1000);
    }
  }
  else
  {
    digitalWrite(Led_Red, LOW);   // LED will be switched off
    digitalWrite(Led_Green, LOW); // LED will be switched off
    digitalWrite(Led_Blue, LOW);  // LED will be switched off
    digital_off();
    Serial.println("Press the button to Init the DHT10.");
    Serial.println("Going to sleep now");
    Serial.println("ESP32 is now stand by");
    esp_deep_sleep_start();
  }
  delay(1500);
}
