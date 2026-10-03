#include "Common.h"

float float_mod(float x, float m)
{
    float r = fmod(x, m);
    if (r < 0) {
        return r + m;
    } else {
        return r;
    }
}


float angle_between(float left, float right)
{
    return float_mod(right - left, 360.0f);
}

float smallest_angle_between(float left, float right)
{
    float angle = angle_between(left, right);
    return fmin(angle, 360 - angle);
}

float mid_angle_between(float left, float right)
{
    return float_mod(left + angle_between(left, right) / 2.0f, 360.0f);
}