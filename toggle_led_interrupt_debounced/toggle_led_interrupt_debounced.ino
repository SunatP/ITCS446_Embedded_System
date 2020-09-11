#define LED 5
#define SW 35
#define DEBOUNCE_TIME 100

volatile bool ledState;
volatile bool intFlag;
int numberOfInterrupts;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR isr();

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW), isr, FALLING);

  ledState = true;
  intFlag = false;

  digitalWrite(LED, ledState);

  Serial.begin(9600);
}

void loop() {
  if(intFlag){
    portENTER_CRITICAL(&mux);
    intFlag = false;
    portEXIT_CRITICAL(&mux);

    numberOfInterrupts++;
    Serial.print("An interrupt has occurred. Total: ");
    Serial.println(numberOfInterrupts);
  }
  delay(1000);
}

void IRAM_ATTR isr() {
  static unsigned long lastInt = millis(); // Initialized only at start because it's declared as static
  unsigned long currInt = millis(); // Current timestamp

  /* Ignore when <= DEBOUNCE_TIME */
  if(currInt - lastInt > DEBOUNCE_TIME){ 
    portENTER_CRITICAL_ISR(&mux);
    intFlag = true;
  
    ledState = !ledState;
    digitalWrite(LED, ledState);
    portEXIT_CRITICAL_ISR(&mux);
  }
  lastInt = currInt;
}
