#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define BLYNK_AUTH "HXRV1JgsVuOkYRZNI8hg1P6KRHtrWTor" //Blynk Authentication Token
#define SSID "Galaxy Note 9" //WiFi SSID
#define PASS "sunat1998" //WiFi Password

#define MQTT_SERVER "192.168.43.65" //MQTT Broker IP Address

#define DHTTYPE DHT10

#define LED_PIN 32

#define FREQ 5000
#define LED_CHANNEL_0 0
#define RES 10

DHT dht(0, DHTTYPE); // The first parameter is pin, which is required for DHT11 and DHT22, but not required for DHT10 because it's i2c.

WiFiClient espClient;
PubSubClient client(espClient);

// Attach virtual serial terminal to Virtual Pin V1
//WidgetTerminal terminal(V1);
BlynkTimer timer;

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi();
void reconnect();
void callback(char* topic, byte* message, unsigned int length);

void setup() {
  Serial.begin(115200); 
  Serial.println("DHT10 test!");
  Wire.begin();

  dht.begin();

  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
  Blynk.config(BLYNK_AUTH);

  pinMode(LED_PIN, OUTPUT);

  ledcSetup(LED_CHANNEL_0, FREQ, RES);
  ledcAttachPin(LED_PIN, LED_CHANNEL_0);
}

void loop() {
  Blynk.run();
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp_hum_val[2] = {0};
  
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    /* Reading temperature or humidity takes about 250 milliseconds!
       Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    */
    if(!dht.readTempAndHumidity(temp_hum_val)){
      // Convert the value to a char array
      char tempString[8];
      dtostrf(temp_hum_val[1], 1, 2, tempString);
      Serial.print("Temperature: ");
      Serial.println(tempString);
      client.publish("esp32/temperature", tempString);
      Blynk.virtualWrite(V5, temp_hum_val[1]);

      // Convert the value to a char array
      char humString[8];
      dtostrf(temp_hum_val[0], 1, 2, humString);
      Serial.print("Humidity: ");
      Serial.println(humString);
      client.publish("esp32/humidity", humString);
      Blynk.virtualWrite(V6, temp_hum_val[0]);
    }
    else{
       Serial.println("Failed to get temprature and humidity value.");
    }
  }
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);

  ledcWrite(LED_CHANNEL_0, pinValue);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      ledcWrite(LED_CHANNEL_0, 1023);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      ledcWrite(LED_CHANNEL_0, 0);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
