// #include <Motors.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>
// #include <PID.h>
// #include <Common.h>
// #include <IR.h>
// #include <LightSensors.h>
#include <Arduino.h>


// Motors move;
// Adafruit_BNO055 bno;
// PID rotationPID(IMU_KP, IMU_KI, IMU_KD, IMU_MAX);
// IR_Sensors IR;
// Light_sensors avoidance;

// sensors_event_t event;



void setup()
{
    Serial.begin(9600);
    
    delay(50);

    pinMode(4, OUTPUT); digitalWrite(4, LOW);
    pinMode(6, OUTPUT); digitalWrite(6, LOW);
    pinMode(7, OUTPUT); digitalWrite(7, LOW);

    pinMode(8, OUTPUT); digitalWrite(8, LOW);
    pinMode(9, OUTPUT); digitalWrite(9, LOW);
    pinMode(10, OUTPUT); digitalWrite(10, LOW);

    pinMode(5, OUTPUT); digitalWrite(5, LOW);
    pinMode(3, OUTPUT); digitalWrite(3, LOW);
    pinMode(2, OUTPUT); digitalWrite(2, LOW);

    pinMode(13, OUTPUT); digitalWrite(13, LOW);
    pinMode(11, OUTPUT); digitalWrite(11, LOW);
    pinMode(12, OUTPUT); digitalWrite(12, LOW);
    
    delay(20);
    analogWrite(4, 100);
    analogWrite(8, 100);
    analogWrite(5, 100);
    analogWrite(13, 100);


    // while (!bno.begin()) { // While the compass hasn't started
    //     Serial.println("Compass isn't working"); // Prints "Compass isn't working"
    //     delay(1000);
    // }

    // move.init();
    // IR.init();
    // avoidance.init();
}




void loop()
{
    
digitalWrite(7, HIGH);
digitalWrite(6, LOW);
analogWrite(4, 100);

digitalWrite(10, HIGH);
digitalWrite(9, LOW);
analogWrite(8, 100);

digitalWrite(11, HIGH);
digitalWrite(12, LOW);
analogWrite(13, 100);

digitalWrite(3, HIGH);
digitalWrite(2, LOW);
analogWrite(5, 100);



    // static uint32_t lastDrive = 0;
    // static uint32_t lastDirection = 0;
    // static uint8_t driveClockwise = 0;

    // uint32_t now = millis();

    // if ((now - lastDrive) >= 20) {
    //     if ((now - lastDirection) >= 1000) {
    //         driveClockwise = 1 - driveClockwise;

    //         if (driveClockwise) {
    //             digitalWrite(7, HIGH);
    //             digitalWrite(6, LOW);
    //             analogWrite(4, 100);
                
    //             digitalWrite(10, HIGH);
    //             digitalWrite(9, LOW);
    //             analogWrite(8, 100);


    //         } else {
    //             digitalWrite(6, HIGH);
    //             digitalWrite(7, LOW);
    //             analogWrite(4, 100);

    //             digitalWrite(9, HIGH);
    //             digitalWrite(10, LOW);
    //             analogWrite(8, 100);

    //         }
    //         lastDirection = millis();
    //     }
    //     lastDrive = millis();
    // }




    // bno.getEvent(&event);
    // float heading = event.orientation.x; // Sets the current orientation to 'heading'

    // Serial.print("Raw Heading: ");
    // Serial.print(heading);
    // Serial.print("\t");

    // heading = heading > 180.0f ? heading - 360.0f : heading; // Checks if heading is over or under 180, changing so that rather than measuring from 0 - 360 degrees, it's -180 - 180 degrees

    // Serial.print("Adjusted heading: ");
    // Serial.print(heading);
    // Serial.print("\t");

    
    // float direction;
    // float avoidance_direction = avoidance.Line_avoidance(); //Finds the avoidance direction
    // if (avoidance_direction == 1000){ //Checks if the avoidance direction is 1000(no line)
        // direction = IR.orbit(); //If so, sets the direction to whatever the orbit is
    // }
    // else {
        // direction = avoidance_direction; //If not, sets the direction to whatever the avoidance direction is
    // }


    // float speed = 0.0f;

    // direction = -1;

    // float correction = -rotationPID.update(heading, 0.0f);
    
    // move.move(direction, speed, correction); //Moves based on the direction, speed and correction
}