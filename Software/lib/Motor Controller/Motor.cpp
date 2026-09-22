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
    digitalWrite(ina, (speed > 0)); // If speed is positive, ina is high
    digitalWrite(inb, (speed < 0)); // If speed is negative, inb is high
    analogWrite(pwm, min(abs(speed), 255)); // pwm is the absolute, minimum of speed, with a max of 255
}