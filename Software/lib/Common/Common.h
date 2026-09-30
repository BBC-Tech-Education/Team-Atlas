#ifndef COMMON_H
#define COMMON_H
#include <Arduino.h>

#define IMU_KP 1.8f  // Determines the P value and sets the speed proportionally to how far off the robot is from 0 degrees
#define IMU_KI 0.0f  // Determines the I value and prevents systematic error
#define IMU_KD 0.0f // Determines the D value and prevents overshooting
#define IMU_MAX 255 // Sets the max speed

#define MOVE_SPEED 255.0f

#endif