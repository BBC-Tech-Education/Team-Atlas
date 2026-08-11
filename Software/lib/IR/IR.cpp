#include <IR.h>
float IR_Sensors::orbit(){
    float ball_direction_angle = ball_direction(); //Uses `ball_direction` to find where the ball is
    int movement_direction;
    if (ball_direction_angle != 0){ //Checks if the ball isn't infront of the robot
        if (ball_direction_angle < 180){ //Checks if the ball is to the right of the robot
            movement_direction = ball_direction_angle + 90; //Sets the movement direction 90 degrees more than the ball angle
        }
        if (ball_direction_angle >= 180){ //Checks if the ball is to the left of the robot
            movement_direction = ball_direction_angle - 90; //Sets the movement direction 90 degrees less than the ball angle
        }
    }
    else {
        movement_direction = 0; //Sets the movement direction to 0
    }
    return movement_direction;
}
float IR_Sensors::ball_direction(){
    int IR_sensor_values[12] = {0}; //Sets each TSSP value to 0
    for (int i = 0; i < 255; i++){ //Repeats 255 times
        for (int a = 0; a < 12; a++){ //Repeats 12 times
            IR_sensor_values[a] += 1 - digitalRead(IR_pins[a]); //Adds 1 - the TSSPs value
        }
    }
    int IR_sensor_maxVal = IR_sensor_values[0]; //Assumes that the front TSSP has the highest value
    int maxVal_location = 0; //Assumes that the front TSSP has the highest value
    for (int i = 0; i < 12; i++){ //Iterates through each TSSP
        if (IR_sensor_values[i] > IR_sensor_maxVal) { //Checks if the current TSSP value is higher
            IR_sensor_maxVal = IR_sensor_values[i]; //If so, sets the new TSSP value to the max
            maxVal_location = i; //If so, sets the new TSSP location to the max
        }
    }
    float direction_angle = 360/12 * maxVal_location; //Finds what angle the highest value is at
    return direction_angle;
}
void IR_Sensors::init(){
    for (int i = 0; i < 12; i++){ //Iterates through each TSSP
        pinMode(IR_pins[i], INPUT); //Sets each pin to INPUT
    }
    
}