#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H
#include <Arduino.h>
#include <Pins.h>
class MotorController{public: MotorController(){};
void movement(int speed);
void init(int ina , int inb , int pwm);
    private: int INA ; int INB ; int PWM;};
#endif