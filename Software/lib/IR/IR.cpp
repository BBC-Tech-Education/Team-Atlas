#include <IR.h>


///////////////////////////// PUBLIC /////////////////////////////


/*
 * @brief Initialises the 12 IR sensors to the correct pin mode.
 */
void IRSensors::init()
{
    for (uint8_t i = 0; i < IR_NUM; i++) {
        pinMode(pin[i], INPUT);
    }
}

void IRSensors::update()
{
    read();
    calculate_ball_data();
}

float IRSensors::get_direction()
{
    return direction;
}

float IRSensors::get_strength()
{
    return strength;
}


///////////////////////////// PRIVATE /////////////////////////////

void IRSensors::read()
{
    for (uint8_t i = 0; i < IR_NUM; i++) {
        value[i] = 0;
    }

    for (uint8_t i = 0; i < SAMPLE_NUM; i++) {
        for (uint8_t j = 0; j < IR_NUM; j++) {
            value[j] += 1 - digitalRead(pin[j]);
        }
        delayMicroseconds(20);
    }

    // Broken sensors
    // value[8] = 0; // USE THIS ON THE ROBOT WITH THE TEAL ARDUINO
    // value[10] = 0; // USE THIS ON THE ROBOT WITH THE TEAL ARDUINO
    value[2] = 0; // USE THIS ON THE ROBOT WITH THE BLUE ARDUIONO
}

void IRSensors::calculate_ball_data()
{
    uint8_t max_val_location = 0; // Assumes that the front TSSP has the highest value
    for (uint8_t i = 0; i < IR_NUM; i++) {
        // Serial.print(value[i]);
        // Serial.print(" ");
        if (value[i] > value[max_val_location]) { // Checks if the current TSSP value is higher
            max_val_location = i; // Sets new location for highest TSSP value
        }
    }
    // Serial.println();

    direction = 360.0f / (float)IR_NUM * (float)max_val_location;
    strength = value[max_val_location];
}