#include "Motor.h"


void Motor::init(uint8_t a, uint8_t b , uint8_t p)
{
    ina = a;
    inb = b;
    pwm = p;
    pinMode(ina, OUTPUT);
    pinMode(inb, OUTPUT);
    pinMode(pwm, OUTPUT);
}


void Motor::movement(int16_t speed)
{
    digitalWrite(ina, (speed > 0));
    digitalWrite(inb, (speed < 0));
    analogWrite(pwm, min(abs(speed), 255));
}