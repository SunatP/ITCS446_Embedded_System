#define LED1 33 // Output to LED on Digital
#define LED2 32 // Output to LED on Analog
void setup() {
  pinMode(LED1, OUTPUT);
  Serial.setTimeout(100);
  Serial.begin(115200);
  //Serial.begin(9600);
  ledcSetup(0,5000,11);
  ledcAttachPin(LED2,0);
  // put your setup code here, to run once:
}

void loop() {
 if(Serial.available() > 0)
 {
  String message = Serial.readString();
  String text = message.substring(0,1);
  int value = message.substring(1).toInt();
  if(text.equalsIgnoreCase("d"))
  {
    digitalWrite(LED1, value);

  }
  else if (text.equalsIgnoreCase("a"))
  {
    ledcWrite(0,value);
   
  }
 }
}