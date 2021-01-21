#define LED1 A13 // Output to LED on GPIO32
#define LED2 A12 // Output to LED on GPIO33
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  //Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);
  delay(500);
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(LED1));
  Serial.println(digitalRead(LED2));
}
