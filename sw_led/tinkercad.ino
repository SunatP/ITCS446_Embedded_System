int led1 = 12; // กำหนดขาใช้งาน
int led2 = 8;
int led3 = 7;
int led4 = 4;
int buttonPin = 13;

int buttonState = 0;
void setup()
{
    pinMode(led1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา OUTPUT
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(buttonPin, INPUT); // กำหนดขาทำหน้าที่ให้ขา INPUT รับค่าจากสวิตช์
    digitalWrite(led1, LOW);
}
void loop()
{
    buttonState = digitalRead(buttonPin); // อ่านค่าจาก SW
    if (buttonState == LOW)
    {                             // ถ้าไม่ได้กดสวิตช์
        digitalWrite(led1, HIGH); // ไฟติด แบบ loop ด้วย 0.5 วิ
        delay(500);
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        delay(500);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        delay(500);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH);
        delay(500);
        digitalWrite(led4, LOW);
    }
    else
    {                             //ถ้ากดสวิตช์
        digitalWrite(led1, HIGH); // ไฟติดค้าง
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
    }
}