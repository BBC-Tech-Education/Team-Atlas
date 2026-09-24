#include <Motors.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <PID.h>
#include <Common.h>
#include <IR.h>
#include <LightSensors.h>


Motors move;
Adafruit_BNO055 bno;
PID rotationPID(IMU_KP, IMU_KI, IMU_KD, IMU_MAX);
IR_Sensors IR;
Light_sensors avoidance;

sensors_event_t event;



void setup()
{
    Serial.begin(9600);
    
    delay(50);
    while (!bno.begin()) { // While the compass hasn't started
        Serial.println("Compass isn't working"); // Prints "Compass isn't working"
        delay(1000);
    }

    move.init();
    IR.init();
    // avoidance.init();
}




void loop(){
    bno.getEvent(&event);
    float heading = event.orientation.x; // Sets the current orientation to 'heading'

    // Serial.print("Raw Heading: ");
    // Serial.print(heading);
    // Serial.print("\t");

    heading = heading > 180.0f ? heading - 360.0f : heading; // Checks if heading is over or under 180, changing so that rather than measuring from 0 - 360 degrees, it's -180 - 180 degrees

    // Serial.print("Adjusted heading: ");
    // Serial.print(heading);
    // Serial.print("\t");

    float direction;
    // float avoidance_direction = avoidance.Line_avoidance(); //Finds the avoidance direction
    // if (avoidance_direction == 1000){ //Checks if the avoidance direction is 1000(no line)
        direction = IR.orbit(); //If so, sets the direction to whatever the orbit is
    // }
    // else {
        // direction = avoidance_direction; //If not, sets the direction to whatever the avoidance direction is
    // }

    float speed = 100.0f;

    float correction = -rotationPID.update(heading, 0.0f);
    
    move.move(direction, speed, correction); //Moves based on the direction, speed and correction
    
    
    // Serial.print("Orientation ");
    // Serial.println(gyro.orientation.x); //Prints the current compass angle
    // Serial.print("Correction ");
    // Serial.print("Correction: ");
    // Serial.println(correction);
    // Serial.println(direction);
}