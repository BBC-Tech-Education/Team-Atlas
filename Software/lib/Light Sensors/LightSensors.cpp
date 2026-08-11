#include <LightSensors.h>

float Light_sensors::Line_avoidance(){
    float line_direction_angle = Line_direction(); //Defines the line direction
    int avoidance_direction;
    if (line_direction_angle != 1000){ //Checks if the robot sees the line
            if (line_direction_angle != 0){ //If so, checks if the angle isn't in front
                if (line_direction_angle < 180){ //If so, checks if the line is to the right of the robot
                    avoidance_direction = line_direction_angle + 180; //If so, moves in the opposite direction of the line
                }
                if (line_direction_angle >= 180){ //If so, checks if the line is to the left of the robot
                    avoidance_direction = line_direction_angle - 180; //If so, moves in the opposite direction of the line
                }
            else {
                avoidance_direction = 0; //If not, moves forward
            }
        }
    }
    else {
        avoidance_direction = 1000; //If not, doesn't move
    }
    return avoidance_direction;
}


float Light_sensors::Line_direction(){
    int Light_sensor_values[16] = {0}; //Sets each light sensor value to 0
        for (int a = 0; a < 16; a++){ //Iterates through each light sensor value
            Light_sensor_values[a] += analogRead(LightSensor_pins[a]); //Adds the light sensors current reading to the list
    }
    int average_number = 0; //Sets the average number to 0
    float average_sum = 0; //Sets the average sum to 0
    for (int i = 0; i < 16; i++){ //Iterates through each light sensor value
        if (Light_sensor_values[i] > 0.8 * 1023){ //Checks if the light sensor is seeing white
            average_number += 1; //If so, adds one to the average number
            average_sum += 360/16 * i; //If so, adds the angle of the light sensor to the average sum
        }
    }
    float line_direction_angle = 0; //Sets the line direction to 0
    if (average_number == 0){ //Checks if zero light sensors saw the line
        line_direction_angle = 1000; //If so, sets the line direction to 1000
    }
    else {
        line_direction_angle = average_sum/average_number; //If not, finds where the average angle is for all the light sensors which see white
    }
    return line_direction_angle;
}

void Light_sensors::init(){
    for (int i = 0; i < 16; i++){ //Iterates through each light sensor
        pinMode(LightSensor_pins[i], INPUT); //Sets each pin to INPUT
    }
    
}