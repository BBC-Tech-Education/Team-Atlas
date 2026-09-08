#include <PID.h>


PID::PID(float p, float i, float d, float m)
{
    kp = p; // Proportional gain
    ki = i; // Integral gain
    kd = d; // Derivative gain
    max = m; // Output limit threshold

    last_time = micros(); // Saves the initial time in microseconds
    integral = 0.0f; // Sets the initial accumulated error to 0
}


float PID::update(float input, float setpoint)
{
    // Determine the current error (how far away the current value is from where we want it to be)
    float error = input - setpoint;

    // Determine the time since last update function was called
    unsigned long current_time = micros();
    float elapsed_time = (current_time - last_time) / 1000000.0f;
    last_time = current_time;

    // Derivative
    float derivative = (error - last_error) / elapsed_time;
    last_error = error;

    // Integral
    integral += error * elapsed_time;

    float sum = kp * error + ki * integral - kd * derivative;
    
    return constrain(sum, -max, max);
}