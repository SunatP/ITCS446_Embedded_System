int btn = 34;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Init");

  pinMode(btn, INPUT);
  // put your setup code here, to run once:

}

void loop() {
//  state = digitalRead(btn);
  if(digitalRead(btn) == HIGH){
    Serial.println("1");
  }
  else
  {
    Serial.println("0");
  }
  // put your main code here, to run repeatedly:

}
