#include <PID.h>
PID::PID(float p,float i,float d,float max){
    p2 = p; //Proportional gain
    i2 = i; //Integral gain
    d2 = d; //Derivative gain
    max2 = max; //Output limit threshold
    last_run = micros(); //Save sthe initial time in microseconds
    total_integral = 0; //Sets the initial accumulated error to 0
}
float PID::update(float target, float current_degrees){
    // derivative = rise/run
    unsigned long current_time = micros(); //Saves the current time in microseconds
    float elapsed_time = (current_time - last_run)/1000000.0; //Finds how long since the last update
    float derivative = (current_degrees - last_input)/elapsed_time; //Calculates the rate of change
    float error = target - current_degrees; //Finds how far off 0 degrees we are
    total_integral += error * elapsed_time;

    last_input = current_degrees; //Remembers what the current degree is for the next execution
    last_run = current_time; //Remembers what the current time is for the next execution

    float sum = error * p2 + total_integral * i2 - derivative * d2; //Calculates the weighted output
    if (abs(sum) > max2){ //checks if the output is too high
        return max2 * (sum/abs(sum));} //If so, returns the max as either positive or negative
    return sum;
}