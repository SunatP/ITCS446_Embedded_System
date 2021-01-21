#include <WiFi.h>
#include <time.h>
#include <RTC.h>

const char* ssid = "Galaxy Note 9";
const char* password = "sunat1998";

const char* ntpServer = "ntp.ku.ac.th";
//const char* ntpServer = "clock.mahidol.ac.th";
const long  gmtOffset_sec = 3600 * 7; //UTC +7.00
const int   daylightOffset_sec = 0; //0 means no DST observed; otherwise, 3600.

struct tm timeinfo;

static DS1307 RTC;

void setup() {
  Serial.begin(9600);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  Serial.println("M:" + String(timeinfo.tm_mon) + ", Y:" + String(timeinfo.tm_year));

    RTC.setHourMode(CLOCK_H12);
  //RTC.setHourMode(CLOCK_H24);

  if (RTC.getHourMode() == CLOCK_H12)
  {
     RTC.setMeridiem(HOUR_PM);
  }
  
  RTC.setDay(timeinfo.tm_mday);
  RTC.setMonth(timeinfo.tm_mon);
  RTC.setYear(1900+timeinfo.tm_year);

  RTC.setHours(timeinfo.tm_hour);
  RTC.setMinutes(timeinfo.tm_min);
  RTC.setSeconds(timeinfo.tm_sec);

}

void loop() {
  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }
  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  Serial.print(" ");

  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem()) {
      case HOUR_AM :
        Serial.print(" AM");
        break;
      case HOUR_PM :
        Serial.print(" PM");
        break;
    }
  }
  Serial.println("");
  delay(1000);
}
