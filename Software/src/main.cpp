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

    float direction;

    if (avoidance.get_direction() == -1.0f){
        direction = orbit(ir.get_direction(), ir.get_strength());
        // Serial.println("No avoidance");
    } else {
        direction = avoidance.get_direction() + 180.0f;

        if (direction > 360.0f) {
            direction -= 360.0f;
        }
        // Serial.println("Yes avoidance");
    }
    Serial.println(direction);


    // Serial.print("IR VALUES - dir: "); Serial.print(ir.get_direction());
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
        return direction + 80.0f;
    } else {
        return direction - 80.0f;
    }
}