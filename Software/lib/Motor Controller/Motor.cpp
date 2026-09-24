#include "Motor.h"


void Motor::init(uint8_t a, uint8_t b , uint8_t e)
{
    ina = a;
    inb = b;
    en = e;
    pinMode(ina, OUTPUT);
    pinMode(inb, OUTPUT);
    pinMode(en, OUTPUT);
    digitalWrite(en, HIGH);
}


void Motor::movement(int16_t speed)
{
    analogWrite(ina, (speed > 0) ? abs(speed) : 0);
    analogWrite(inb, (speed < 0) ? abs(speed) : 0);
}