#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Free_Fonts.h"
#define TRIG_PIN 21
#define ECHO_PIN 5

int buzzer = 22 ;
long duration;
int distance;
#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
 
void setup() {
  Serial.begin(9600);
  pinMode (buzzer, OUTPUT) ; 
  pinMode(TRIG_PIN, OUTPUT); // Sets the TRIG_PIN as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the ECHO_PIN as an Input

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextFont(4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Sets the TRIG_PIN on HIGH state for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;


  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  tft.drawCentreString("Ultrasonic distance", 120, 30, 2);
  tft.drawCentreString(String(distance), 120, 60, 4);
   if(distance < 10)
  {
    digitalWrite (buzzer, HIGH) ;
  }
  else
  {
    digitalWrite (buzzer, LOW) ;
  }
 delay(200);
}
