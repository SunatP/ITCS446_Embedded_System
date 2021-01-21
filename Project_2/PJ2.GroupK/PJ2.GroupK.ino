#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <Arduino.h>
#include <analogWrite.h> // Use for RGB LED module

// Connection Zone
#define SSID "Galaxy Note 9"        // WiFi SSID
#define PASS "sunat1998"            // WiFi Password
#define MQTT_SERVER "192.168.43.65" // MQTT Broker IP Address from RPi

#define DHTTYPE DHT10

#define LED_PIN 32
/**
 * IN4  EEP 
 * IN3  OUT1
 * GND  OUT2
 * VCC  OUT3
 * IN2  OUT4
 * IN1  ULT
 * OUT1,OUT2:1-channel H-bridge controlled by IN1/IN2
 * Now we selected OUT1 and OUT2 for DC motor
 * OUT3,OUT4:2-channel H-bridge controlled by IN3/IN4
 * **/
// DHT 10 Pin : VDD(1) Pin 3v3, SDA(2) Pin 21, GND(3) Pin GND, SCL(4) Pin 22
// LED Zone
int Readvalue = 0;
int Led_Red = 18;
int Led_Green = 19;
int Led_Blue = 5;
// Motor Output Zone
int AIN_1 = 25;
int AIN_2 = 33;
// Input Zone
#define Threshold 40 // more value, more sensitvity
int Touch_Sensor = 4;

#define PWM_CH_1 0
#define PWM_CH_2 1
#define FREQ 5000
#define LED_CHANNEL_0 0
#define RES 10

#define PWM_FREQ 15000
#define PWM_RES 12 // Resolution in bits

const int PWM_MAX = pow(2, PWM_RES) - 1;
int dutyCycle = 50; // percents

DHT dht(0, DHTTYPE); // The first parameter is pin, which is required for DHT11 and DHT22, but not required for DHT10 because it's i2c.

WiFiClient espClient;
PubSubClient client(espClient);
// Attach virtual serial terminal to Virtual Pin V1
// WidgetTerminal terminal(V1);

long lastMsg = 0;
char msg[50];
int value = 0;
int status;

void setup_wifi();
void reconnect();
void callback(char *topic, byte *message, unsigned int length);
void setup()
{
  Serial.begin(115200);
  Serial.println("DHT10 test!");
  Wire.begin();

  dht.begin();
  ledcSetup(PWM_CH_1, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CH_2, PWM_FREQ, PWM_RES);
  pinMode(Led_Red, OUTPUT);
  pinMode(Led_Green, OUTPUT);
  pinMode(Led_Blue, OUTPUT);
  pinMode(Touch_Sensor, INPUT);
  ledcAttachPin(AIN_1, PWM_CH_1);
  ledcAttachPin(AIN_2, PWM_CH_2);
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
  pinMode(LED_PIN, OUTPUT);

  ledcSetup(LED_CHANNEL_0, FREQ, RES);
  ledcAttachPin(LED_PIN, LED_CHANNEL_0);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1); // Set Pin 4 for Switch button to wake up the ESP32
  Serial.println("ESP32 is booting up!!");
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  float temp_hum_val[2] = {0};

  long now = millis();
  // Serial.println("Status:");
  // Serial.print(status);
  if (now - lastMsg > 5000)
  {
    lastMsg = now;

    /* Reading temperature or humidity takes about 250 milliseconds!
       Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    */

    if (!dht.readTempAndHumidity(temp_hum_val))
    {

      // Convert the value to a char array
      char tempString[8];
      dtostrf(temp_hum_val[1], 1, 2, tempString);
      Serial.print("Temperature: ");
      Serial.println(tempString);
      client.publish("esp32/temperature", tempString);

      // Convert the value to a char array
      char humString[8];
      dtostrf(temp_hum_val[0], 1, 2, humString);
      Serial.print("Humidity: ");
      Serial.println(humString);
      client.publish("esp32/humidity", humString);
      Touch();
      if (status == 1)
      {
        if (temp_hum_val[1] > 31)
        {
          setColor(255, 0, 0); // set Red
          client.publish("esp32/climate", "VERY HOT");
          moveForward(PWM_CH_1, PWM_CH_2, 100); // power 4095
        }
        else if (temp_hum_val[1] > 28 && temp_hum_val[1] <= 31)
        {
          setColor(255, 128, 0); // set Orange
          client.publish("esp32/climate", "HOT");
          moveForward(PWM_CH_1, PWM_CH_2, 80); // power 3276
        }
        else if (temp_hum_val[1] > 26 && temp_hum_val[1] <= 28)
        {
          setColor(255, 255, 0); // set Yellow
          client.publish("esp32/climate", "WARM");
          moveForward(PWM_CH_1, PWM_CH_2, 60); // power 2457
        }
        else if (temp_hum_val[1] > 23 && temp_hum_val[1] <= 26)
        {
          setColor(159, 255, 64); // set Green
          char ratioString[8];
          client.publish("esp32/climate", "COLD");
          moveForward(PWM_CH_1, PWM_CH_2, 40); // power 1638
        }
        else if (temp_hum_val[1] <= 23)
        {
          setColor(32, 255, 255); // set Aqua
          client.publish("esp32/climate", "VERY COLD");
          moveForward(PWM_CH_1, PWM_CH_2, 20); // power 819
        }
        client.publish("esp32/status", "Auto Mode!");
      }
      if (status == 2)
      {
        client.publish("esp32/status", "Force Turn On Mode!");
        moveForward(PWM_CH_1, PWM_CH_2, 100);
        setColor(0, 0, 0);
        digitalWrite(LED_PIN,LOW);
      }
    }
    else
    {
      Serial.println("Failed to get temprature and humidity value.");
      stopMotor(PWM_CH_1, PWM_CH_2);
    }
  }
}

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output")
  {
    Serial.print("Changing output to ");
    if (messageTemp == "off")
    {
      Serial.println("off");
      ledcWrite(LED_CHANNEL_0, 0);
      client.publish("esp32/status", "GO TO SLEEP NOW!");
      Serial.println("ESP32 will go to sleep");
      delay(2500);
      esp_deep_sleep_start();
    }
    if (messageTemp == "on")
    {
      status = 1;
    }
    if (messageTemp == "force")
    {
      status = 2;
    }
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP Client"))
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
      client.publish("esp32/status", "BOOTING UP COMPLETED!");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(Led_Red, red);
  analogWrite(Led_Green, green);
  analogWrite(Led_Blue, blue);
}
void moveForward(int motorPositive, int motorNegative, int dutyCycle)
{
  int pwmValue = dutyCycle / 100.0 * PWM_MAX;
  char PWM[8];
  // 0 - 4095
  /* The current flows from positive to negative. */
  Serial.print("Set Fan Speed PWM = ");
  Serial.println(dutyCycle);
  ledcWrite(motorPositive, pwmValue);
  ledcWrite(motorNegative, 0);
  dtostrf(dutyCycle, 1, 2, PWM);
  client.publish("esp32/pwm", PWM);
}
void stopMotor(int motorPositive, int motorNegative)
{
  char PWM[8];
  ledcWrite(motorPositive, 0);
  ledcWrite(motorNegative, 0);
  dtostrf(0, 1, 2, PWM);
  client.publish("esp32/pwm", PWM);
}

void Touch()
{
  Readvalue = touchRead(T0);
  char touch[8];
  Serial.println(Readvalue);
  dtostrf(Readvalue, 1, 2, touch);
  client.publish("esp32/touch", touch);
}
