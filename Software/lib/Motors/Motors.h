#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>
#include <MotorController.h>
#include <Pins.h>
#include <math.h>
class motors{public: motors(){};
    void move(int direction, int speed, int correction);
    void init();
    private: 
    MotorController backright;
    MotorController backleft;
    MotorController frontright;
    MotorController frontleft;};
#endif