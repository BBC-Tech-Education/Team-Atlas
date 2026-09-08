#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID {

public:
    PID(float p, float i, float d, float m);
    float update(float input, float setpoint);

private:
    float kp;
    float ki;
    float kd;
    float max;
    unsigned long last_time;

    float integral;
    float last_error;
};

#endif // PID_H