#ifndef IR_H
#define IR_H
#include <Arduino.h>
#include <Pins.h>

class IR_Sensors {
    public:
    IR_Sensors(){};
    void init();
    float orbit();

    private:
    float ball_direction();
    int IR_pins[12] = {IR0, IR1, IR2, IR3, IR4, IR5, IR6, IR7, IR8, IR9, IR10, IR11}; //Adds each IR pin


};

#endif