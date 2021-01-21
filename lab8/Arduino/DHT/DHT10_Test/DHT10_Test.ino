#include "DHT.h"

#define DHTTYPE DHT10
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Free_Fonts.h"

#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
 

DHT dht(0, DHTTYPE); // The first parameter is pin, which is required for DHT11 and DHT22, but not required for DHT10 because it's i2c.

void setup() {
  Serial.begin(115200); 
  Serial.println("DHT10 test!");
  Wire.begin();

  dht.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}

void loop() {
  float temp_hum_val[2] = {0};
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  
  if(!dht.readTempAndHumidity(temp_hum_val)){
      Serial.print("Humidity: "); 
      Serial.print(temp_hum_val[0]);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(temp_hum_val[1]);
      Serial.println(" *C");
          // Update digital time
      int xpos = 0;
      int ypos = 25; // Top left corner ot clock text, about half way down
    
tft.setTextColor(TFT_YELLOW);
  tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen
  tft.drawCentreString("Humidity", 1, 120, 30, 8);
  tft.drawCentreString(String(temp_hum_val[0]), 1, 120, 60, 8);
  tft.drawCentreString("Temperature", 1, 120, 90, 8);
  tft.drawCentreString(String(temp_hum_val[1]), 1, 120, 120, 8);
  tft.println("C");
  
  }
  else{
     Serial.println("Failed to get temprature and humidity value.");
  }

 delay(1500);
}
