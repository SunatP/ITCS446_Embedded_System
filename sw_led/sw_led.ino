#define SW 36 // Input from a switch on GPIO36
#define LED1 32 // Output to LED on GPIO32
#define LED2 33 // Output to LED on GPIO33
#define LED3 25 // Output to LED on GPIO25
#define LED4 26 // Output to LED on GPIO26

int state;

void setup() {
  pinMode(SW, INPUT); 
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(SW);
  if(state == HIGH){
    digitalWrite(LED1, HIGH);
    delay(500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(500);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    delay(500);
    digitalWrite(LED4, LOW);
  }
  else{
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
  Serial.println(state);
}
