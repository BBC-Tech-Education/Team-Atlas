#include "Motors.h"


void Motors::init()
{
    br.init(BR_INA, BR_INB, BR_EN);
    bl.init(BL_INA, BL_INB, BL_EN);
    fr.init(FR_INA, FR_INB, FR_EN);
    fl.init(FL_INA, FL_INB, FL_EN);
}


void Motors::move(float direction, float speed, float correction)
{
    float motor_speeds[4] = {0.0f};

    for (int i = 0; i < 4; i++) {
        motor_speeds[i] = speed * cosf(DEG_TO_RAD * (45.0f + 90.0f * i - direction)) + correction; // Sets the motor speeds based on the direction, correction and speed
    }

    float max = max(max(max(abs(motor_speeds[0]), abs(motor_speeds[1])), abs(motor_speeds[2])), abs(motor_speeds[3])); // Finds the maximum speed

    if (max > 255.0f) { // Checks if the highest speed value is higher than the limit
        float ratio = 255.0f / max; // Sets the ratio to change the values

        for (int i = 0; i < 4; i++){
            motor_speeds[i] *= ratio; // Scales each motor value down
        }
    }

    float min = min(min(min(abs(motor_speeds[0]), abs(motor_speeds[1])), abs(motor_speeds[2])), abs(motor_speeds[3])); // Finds the minimum speed

    if (min < 115.0f && min > 30.0f) { // Checks if the lowest speed is between 115 and 30
        float ratio = 115.0f / min; // Sets the ratio to change the values

        for (int i = 0; i < 4; i++) {
            motor_speeds[i] *= ratio; //Scales each motor value down
        }
    }

    for (int i = 0; i < 4; i++){
        Serial.print(motor_speeds[i]);
        Serial.print(" ");
    }
        
    Serial.println();

    fl.movement((int16_t)motor_speeds[0]);
    fr.movement((int16_t)motor_speeds[1]);
    br.movement((int16_t)motor_speeds[2]);
    bl.movement((int16_t)motor_speeds[3]);
}