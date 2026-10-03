#include <Motors.h>
#include <Adafruit_BNO055.h>
#include <PID.h>
#include <Common.h>
#include <IR.h>
#include <LightSensors.h>
#include <Arduino.h>


Motors motors;
Adafruit_BNO055 bno;
PID rotationPID(IMU_KP, IMU_KI, IMU_KD, IMU_MAX);
IRSensors ir;
LightSensors avoidance;

sensors_event_t event;
float heading;
float line_direction = -1.0f;
float line_location = 0.0f;




void update_line_direction()
{
    float raw_line_direction = avoidance.get_direction();

    if (line_location == 0.0f) {
        if (raw_line_direction != -1) {
            line_location = 1.0f;
            line_direction = raw_line_direction;
        }
    } else if (line_location == 1.0f) {
        if (raw_line_direction == -1) {
            line_location = 0.0f;
            line_direction = -1;
        } else if (smallest_angle_between(raw_line_direction, line_direction) > 90.0f) {
            line_location = 2.0f;
            line_direction = float_mod(raw_line_direction + 180.0f, 360.0f);
        } else {
            line_direction = raw_line_direction;
        }
    } else if (line_location == 2.0f) {
        if (raw_line_direction == -1) {
            line_location = 3.0f;
        } else if (smallest_angle_between(raw_line_direction, line_direction) < 90.0f) {
            line_location = 1.0f;
            line_direction = raw_line_direction;
        } else {
            line_direction = float_mod(raw_line_direction + 180.0f, 360.0f);
        }
    } else {
        if (raw_line_direction != -1) {
            line_location = 2.0f;
            line_direction = float_mod(raw_line_direction + 180.0f, 360.0f);
        }
    }
}

float orbit(float direction, float strength);




void setup()
{
    Serial.begin(9600);

    while (!bno.begin(OPERATION_MODE_IMUPLUS)) {
        Serial.println("Compass isn't working");
        delay(1000);
    }

    motors.init();
    ir.init();
    avoidance.init();
}




void loop()
{
    bno.getEvent(&event);
    float heading = event.orientation.x;
    heading = heading > 180.0f ? heading - 360.0f : heading; // changes heading from 0 - 360 -> -180 - +180
    
    ir.update();
    avoidance.update();
    update_line_direction();

    float direction;

    if (line_direction == -1.0f) {
        direction = orbit(ir.get_direction(), ir.get_strength());
    } else {
        direction = float_mod(line_direction + 180.0f, 360.0f);
        // Serial.println("Yes avoidance");
    }
    Serial.print(avoidance.get_direction()); Serial.print("\t");
    Serial.println(line_direction);


    // Serial.print("IR VALUES - dir: "); Serial.print(ir.[get_direction());
    // Serial.print("\tstr: "); Serial.println(ir.get_strength());


    float speed;
    if (ir.get_strength() != 0.0f || avoidance.get_direction() != -1.0f) {
        speed = MOVE_SPEED;
    } else {
        speed = 0.0f;
    }

    float correction = -rotationPID.update(heading, 0.0f);
    
    motors.move(direction, speed, correction);
}



float orbit(float direction, float strength)
{
    if (direction == 0.0f) {
        return direction;
    }

    if (direction == 30.0f) {
        return direction + 20;
    }

    if (direction == 330.0f) {
        return direction - 20;
    }
    

    if (direction < 180.0f) { // Checks if the ball is to the right of the robot
        return direction + fmin(1.5 * strength, 90.0f);
    } else {
        return direction - fmin(1.5 * strength, 90.0f);
    }


    // if (direction < 180.0f) { // Checks if the ball is to the right of the robot
    //     return direction + 80.0f;
    // } else {
    //     return direction - 80.0f;
    // }
}