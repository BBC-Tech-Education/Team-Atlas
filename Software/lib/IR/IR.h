#ifndef IR_H
#define IR_H
#include <Arduino.h>
#include <Pins.h>


#define IR_NUM     12
#define SAMPLE_NUM 100


class IRSensors {
public:
    IRSensors() {}
    void init();
    void update();

    float get_direction();
    float get_strength();

private:
    void read();
    void calculate_ball_data();

    uint8_t value[IR_NUM] = {0};

    float direction;
    float strength;
    uint8_t pin[IR_NUM] = {IR0, IR1, IR2, IR3, IR4, IR5, IR6, IR7, IR8, IR9, IR10, IR11};
};

#endif