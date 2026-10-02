#ifndef LIGHTSENSORS_H
#define LIGHTSENSORS_H


#include <Arduino.h>
#include <Pins.h>


#define LS_NUM 16
#define LS_BUFFER 200

class LightSensors {
public:
    LightSensors() {}
    void init();
    void update();
    float avoid();

private:
    void read();
    void calibrate();
    float direction();

    uint8_t pins[LS_NUM] = {LS_0, LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15};
    uint16_t value[LS_NUM] = {0};
    uint16_t green[LS_NUM] = {0};
};

#endif