#include <LightSensors.h>


///////////////////////////// PUBLIC /////////////////////////////

void LightSensors::init()
{
    for (uint8_t i = 0; i < LS_NUM; i++) { //Iterates through each light sensor
        pinMode(pins[i], INPUT); //Sets each pin to INPUT
    }
    calibrate();
}

void LightSensors::update()
{
    read();

    for (uint8_t i = 0; i < LS_NUM; i++) {
        Serial.print(value[i]);
        Serial.print(" ");
    }
    Serial.println();
}

float LightSensors::avoid()
{
    float line_direction = direction();

    int avoidance_direction;
    if (line_direction != 1000){ //Checks if the robot sees the line
            if (line_direction != 0){ //If so, checks if the angle isn't in front
                if (line_direction < 180){ //If so, checks if the line is to the right of the robot
                    avoidance_direction = line_direction + 180; //If so, moves in the opposite direction of the line
                }
                if (line_direction >= 180){ //If so, checks if the line is to the left of the robot
                    avoidance_direction = avoidance_direction - 180; //If so, moves in the opposite direction of the line
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


///////////////////////////// PRIVATE /////////////////////////////

void LightSensors::read()
{
    for (uint8_t i = 0; i < LS_NUM; i++) {
        value[i] = analogRead(pins[i]);
    }
}

void LightSensors::calibrate()
{
    for (uint8_t i = 0; i < 10; i++) {
        read();
        for (uint8_t j = 0; j < LS_NUM; j++) {
            green[j] += value[j];
        }
    }

    for (uint8_t i = 0; i < LS_NUM; i++) {
        green[i] /= 10;
        green[i] += LS_BUFFER;
    }
}

float LightSensors::direction()
{
    read();

    int average_number = 0;
    float average_sum = 0;

    for (int i = 0; i < 16; i++){ 
        if (value[i] > 0.2 * 1023){ //Checks if the light sensor is seeing white
            average_number += 1; //If so, adds one to the average number
            average_sum += 360/16 * i; //If so, adds the angle of the light sensor to the average sum
        }
    }

    float direction = 0; //Sets the line direction to 0

    if (average_number == 0){ //Checks if zero light sensors saw the line
        direction = 1000; //If so, sets the line direction to 1000
    }
    else {
        direction = average_sum/average_number; //If not, finds where the average angle is for all the light sensors which see white
    }
    
    return direction;
}