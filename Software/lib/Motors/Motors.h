#ifndef MOTORS_H
#define MOTORS_H


#include <Motor.h>
#include <Pins.h>


class Motors
{
public:
    Motors() {}
    void init();
    void move(float direction, float speed, float correction);

private: 
    Motor br;
    Motor bl;
    Motor fr;
    Motor fl;
};
#endif