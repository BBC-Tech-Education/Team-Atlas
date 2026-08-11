#ifndef LIGHTSENSORS_H
#define LIGHTSENSORS_H
#include <Arduino.h>
#include <Pins.h>

class Light_sensors {
    public:
    Light_sensors(){};
    void init();
    float Line_avoidance();
    float Light_sensor_intensity();

    private:
    float Line_direction();
    int LightSensor_pins[16] = {LightSensor0, LightSensor1, LightSensor2, LightSensor3, LightSensor4, LightSensor5, LightSensor6, LightSensor7, LightSensor8, LightSensor9, LightSensor10, LightSensor11, LightSensor12, LightSensor13, LightSensor14, LightSensor15}; //Adds each light sensor pin

};

#endif