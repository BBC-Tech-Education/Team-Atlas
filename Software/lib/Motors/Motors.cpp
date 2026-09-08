#include "Motors.h"


void Motors::init()
{
    br.init(BR_INA, BR_INB, BR_PWM);
    bl.init(BL_INA, BL_INB, BL_PWM);
    fr.init(FR_INA, FR_INB, FR_PWM);
    fl.init(FL_INA, FL_INB, FL_PWM);
}


void Motors::move(float direction, float speed, float correction)
{
    float motor_speeds[4] = {0.0f};

    for (int i = 0; i < 4; i++) {
        motor_speeds[i] = speed * cosf(DEG_TO_RAD * (45.0f + 90.0f * i - direction)) + correction;
    }

    float max = max(max(max(abs(motor_speeds[0]), abs(motor_speeds[1])), abs(motor_speeds[2])), abs(motor_speeds[3]));

    if (max > 255.0f) { // Checks if the highest speed value is higher than the limit
        float ratio = 255.0f / max;

        for (int i = 0; i < 4; i++){
            motor_speeds[i] *= ratio; // Scales each motor value down
        }
    }

    float min = min(min(min(abs(motor_speeds[0]), abs(motor_speeds[1])), abs(motor_speeds[2])), abs(motor_speeds[3]));

    if (min < 115.0f && min > 30.0f) {
        float ratio = 115.0f / min;
        for (int i = 0; i < 4; i++) {
            motor_speeds[i] *= ratio;
        }
    }

    // for (int i = 0; i < 4; i++){
        // Serial.print(motor_speeds[i]);
    //     Serial.print(" ");
    // }
        
    // Serial.println();

    fl.movement((int16_t)motor_speeds[0]);
    fr.movement((int16_t)motor_speeds[1]);
    br.movement((int16_t)motor_speeds[2]);
    bl.movement((int16_t)motor_speeds[3]);
}