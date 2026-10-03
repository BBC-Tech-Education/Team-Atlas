#include <LightSensors.h>


///////////////////////////// PUBLIC /////////////////////////////

void LightSensors::init()
{
    for (uint8_t i = 0; i < LS_NUM; i++) { //Iterates through each light sensor
        pinMode(pins[i], INPUT); //Sets each pin to INPUT
    }
    calibrate();
}

void LightSensors::update()
{
    read();

    direction = -1.0f;

    for (uint8_t i = 0; i < LS_NUM; i++) {
        if (on_white[(i + LS_NUM - 1) % LS_NUM] && on_white[(i + 1) % LS_NUM]) {
            on_white[i] = true;
        }
    }

    uint8_t cluster_start[4] = {0};
    uint8_t cluster_end[4] = {0};
    uint8_t cluster_num = 0;

    bool in_cluster = false;

    for (uint8_t i = 0; i < LS_NUM; i++) {
        if (!in_cluster) {
            if (on_white[i]) {
                cluster_start[cluster_num] = i;
                in_cluster = true;
            }
        } else {
            if (!on_white[i]) {
                cluster_end[cluster_num] = i - 1;
                in_cluster = false;
                cluster_num++;
            }
        }
    }


    if (on_white[LS_NUM - 1]) {
        if (on_white[0]) {
            cluster_start[0] = cluster_start[cluster_num];
        } else {
            cluster_end[cluster_num] = 15;
            cluster_num++;
        }
    }


    if (cluster_num == 1) {
        direction = mid_angle_between(cluster_start[0] * 360.0f / (float)LS_NUM, cluster_end[0] * 360.0f / (float)LS_NUM);
    } else if (cluster_num == 2) {
        float cluster1 = mid_angle_between(cluster_start[0] * 360.0f / (float)LS_NUM, cluster_end[0] * 360.0f / (float)LS_NUM);
        float cluster2 = mid_angle_between(cluster_start[1] * 360.0f / (float)LS_NUM, cluster_end[1] * 360.0f / (float)LS_NUM);

        float angle = angle_between(cluster1, cluster2);

        if (angle > 180.0f) {
            direction = mid_angle_between(cluster2, cluster1);
        } else {
            direction = mid_angle_between(cluster1, cluster2);
        }
    }
}

float LightSensors::get_direction()
{
    return direction;
}


///////////////////////////// PRIVATE /////////////////////////////

void LightSensors::read()
{
    for (uint8_t i = 0; i < LS_NUM; i++) {
        value[i] = analogRead(pins[i]);
        on_white[i] = value[i] > green[i];
        // Serial.print(value[i]);
        // Serial.print(" ");
    }
    // Serial.println();

    /////////////// Use these on the robot with the blue arduino ///////////////
    // on_white[1] = 0;
    // on_white[5] = 0;
    // on_white[14] = 0;    
}

void LightSensors::calibrate()
{
    for (uint8_t i = 0; i < 10; i++) {
        read();
        for (uint8_t j = 0; j < LS_NUM; j++) {
            green[j] += value[j];
        }
    }

    for (uint8_t i = 0; i < LS_NUM; i++) {
        green[i] /= 10;
        green[i] += LS_BUFFER;
    }
}



float LightSensors::float_mod(float x, float m)
{
    float r = fmod(x, m);
    if (r < 0) {
        return r + m;
    } else {
        return r;
    }
}


float LightSensors::angle_between(float left, float right)
{
    return float_mod(right - left, 360.0f);
}

float LightSensors::smallest_angle_between(float left, float right)
{
    float angle = angle_between(left, right);
    return fmin(angle, 360 - angle);
}

float LightSensors::mid_angle_between(float left, float right)
{
    return float_mod(left + angle_between(left, right) / 2.0f, 360.0f);
}