#include <IR.h>
float IR_Sensors::orbit(){
    float ball_direction_angle = ball_direction(); //Uses `ball_direction` to find where the ball is

    int movement_direction;
    if (ball_direction_angle == 0 || ball_direction_angle == 30 || ball_direction_angle == 330) { // If the ball is roughly in front of the robot
        movement_direction = ball_direction_angle; // If so, just move at the ball
    } else {
        if (ball_direction_angle < 180){ //Checks if the ball is to the right of the robot
            movement_direction = ball_direction_angle + 45; //Sets the movement direction 90 degrees more than the ball angle
        }
        if (ball_direction_angle >= 180){ //Checks if the ball is to the left of the robot
            movement_direction = ball_direction_angle - 45; //Sets the movement direction 90 degrees less than the ball angle
        }
    }
    if (ball_direction_angle == -1) {
        return -1;
    } else {
        return movement_direction;
    }
}
float IR_Sensors::ball_direction(){
    uint8_t IR_sensor_values[12] = {0}; //Sets each TSSP value to 0
    for (uint8_t i = 0; i < 100; i++){ //Repeats 255 times
        for (uint8_t j = 0; j < 12; j++){ //Repeats 12 times
            IR_sensor_values[j] += 1 - digitalRead(IR_pins[j]); //Adds 1 - the TSSPs value
        }
    }
    int IR_sensor_maxVal = IR_sensor_values[0]; //Assumes that the front TSSP has the highest value
    int maxVal_location = 0; //Assumes that the front TSSP has the highest value
    for (int i = 0; i < 12; i++){ //Iterates through each TSSP
        Serial.print(IR_sensor_values[i]);
        Serial.print(" ");
        if (IR_sensor_values[i] > IR_sensor_maxVal) { //Checks if the current TSSP value is higher
            IR_sensor_maxVal = IR_sensor_values[i]; //If so, sets the new TSSP value to the max
            maxVal_location = i; //If so, sets the new TSSP location to the max
        }
    }
    Serial.println();
    float direction_angle;
    
    if (IR_sensor_maxVal == 0) {
        return -1;
        // Serial.print(-1);
    } else {
        // Serial.println(maxVal_location);
        return 360/12 * maxVal_location; 
    }
}
void IR_Sensors::init(){
    for (int i = 0; i < 12; i++){ //Iterates through each TSSP
        pinMode(IR_pins[i], INPUT); //Sets each pin to INPUT
    }
    
}