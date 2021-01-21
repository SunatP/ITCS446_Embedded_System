#include <WiFi.h>
#include <WiFiClientSecure.h>

#define SSID "Galaxy Note 9"
#define PASS "sunat1998"

#define SW 12

#define LINE_TOKEN "P6X56u4LCcsiV921wfCFxNs3utazOqMLQm7hXzLpnT2"

String txt = "Line notified!!!";

void notifyLine(String t);

void setup() {
  pinMode(SW, INPUT_PULLUP);
  
  Serial.begin(115200);

  WiFi.begin(SSID, PASS);
  Serial.print("WiFi Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  byte state = digitalRead(SW);

  if(state == LOW){
    Serial.println("Notification sent.");
    notifyLine(txt);
  }
}

void notifyLine(String t){
  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("Connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP32\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + t).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + t;
  Serial.println(req);
  client.print(req);
  delay(20);
  Serial.println("-------------");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
    break;
    }
  }
}
