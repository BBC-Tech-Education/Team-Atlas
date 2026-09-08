#ifndef MOTOR_H
#define MOTOR_H


#include <Arduino.h>


class Motor {

public:
    Motor() {}
    void init(uint8_t a, uint8_t b, uint8_t p);
    void movement(int16_t speed);
   
private: 
    uint8_t ina;
    uint8_t inb;
    uint8_t pwm;
};


#endif // MOTOR_H