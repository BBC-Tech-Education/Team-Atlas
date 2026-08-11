#ifndef PID_H
#define PID_H
#include <Arduino.h>

class PID{
public:
    PID(float p, float i, float d, float max);
    float update(float target, float current_degrees);
private:
    float p2;
    float i2;
    float d2;
    float max2;
    unsigned long last_run;
    float total_integral;
    float last_input;
};
#endif