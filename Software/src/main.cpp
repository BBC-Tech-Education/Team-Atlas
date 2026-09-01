#include <Motors.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <PID.h>
#include <Common.h>
#include <IR.h>
#include <LightSensors.h>
motors move;
Adafruit_BNO055 compass;
sensors_event_t gyro;
PID compass_correction(P, I, D, MAX);
IR_Sensors IR;
Light_sensors avoidance;
void setup(){
    Serial.begin(9600);
    move.init();
    while (! compass.begin()){ //While the compass hasn't started
        Serial.println("Compass isn't working"); //Prints "Compass isn't working"
    }
    compass.setExtCrystalUse(true);
    IR.init();
    avoidance.init();
}
void loop(){
    float direction;
    compass.getEvent(&gyro); //Gets the compass value(degrees)
    float avoidance_direction = avoidance.Line_avoidance(); //Finds the avoidance direction
    if (avoidance_direction == 1000){ //Checks if the avoidance direction is 1000(no line)
        direction = IR.orbit(); //If so, sets the direction to whatever the orbit is
    }
    else {
        direction = avoidance_direction; //If not, sets the direction to whatever the avoidance direction is
    }
    float speed = 100;
    float correction = compass_correction.update(0.0f, gyro.orientation.x > 180.0f? gyro.orientation.x - 360.0f: gyro.orientation.x); //Updates the correction value, checking if the value is above 180. Ff so, it subtracts 180 degrees from the value. If not, it leaves the value.
    move.move(direction, speed, correction); //Moves based on the direction, speed and correction
    // Serial.print("Orientation ");
    // Serial.println(gyro.orientation.x); //Prints the current compass angle
    // Serial.print("Correction ");
    // Serial.println(correction);
}