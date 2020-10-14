#define IN_1 33 // Pin attached to IN1 of DRV8833 module
#define IN_2 25 // Pin attached to IN2 of DRV8833 module
#define IN_3 26 // Pin attached to IN3 of DRV8833 module
#define IN_4 27 // Pin attached to IN4 of DRV8833 module

#define START_STOP 36
#define FWD_BWD 34
#define FWD 0
#define BWD 1

#define PWM_CH_1 0
#define PWM_CH_2 1
#define PWM_CH_3 2
#define PWM_CH_4 3

#define PWM_FREQ 15000
#define PWM_RES 12 // Resolution in bits

#define ADC 32
#define MAX_ADC 4095
#define MIN_CYCLE 60

const int PWM_MAX = pow(2, PWM_RES) - 1;
int dutyCycle = 100; // percents
int adc = 0;

void setup()
{
    ledcSetup(PWM_CH_1, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CH_2, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CH_3, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CH_4, PWM_FREQ, PWM_RES);

    ledcAttachPin(IN_1, PWM_CH_1);
    ledcAttachPin(IN_2, PWM_CH_2);
    ledcAttachPin(IN_3, PWM_CH_3);
    ledcAttachPin(IN_4, PWM_CH_4);

    pinMode(START_STOP, INPUT);
    pinMode(FWD_BWD, INPUT);
}

void loop()
{
    adc = analogRead(ADC);
    dutyCycle = 60 + ((40 * adc) / 4095);

    if (digitalRead(START_STOP))
    {
        if (digitalRead(FWD_BWD) == FWD)
        {
            moveForward(PWM_CH_1, PWM_CH_2, dutyCycle);
            moveForward(PWM_CH_3, PWM_CH_4, dutyCycle);
        }
        else
        {
            moveBackward(PWM_CH_1, PWM_CH_2, dutyCycle);
            moveBackward(PWM_CH_3, PWM_CH_4, dutyCycle);
        }
    }
    else
    {
        stopMotor(PWM_CH_1, PWM_CH_2);
        stopMotor(PWM_CH_3, PWM_CH_4);
    }
}
void moveForward(int motorPositive, int motorNegative, int dutyCycle)
{
    int pwmValue = dutyCycle / 100.0 * PWM_MAX;

    /* The current flows from positive to negative. */
    ledcWrite(motorPositive, pwmValue);
    ledcWrite(motorNegative, 0);
}

void moveBackward(int motorPositive, int motorNegative, int dutyCycle)
{
    int pwmValue = dutyCycle / 100.0 * PWM_MAX;

    /* The current flows from negative to positive. */
    ledcWrite(motorPositive, 0);
    ledcWrite(motorNegative, pwmValue);
}

void stopMotor(int motorPositive, int motorNegative)
{
    ledcWrite(motorPositive, 0);
    ledcWrite(motorNegative, 0);
}
