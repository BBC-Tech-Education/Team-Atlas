#include <Motors.h>
void motors::init(){
backright.init(INABackRight, INBBackRight, PWMBackRight);
backleft.init(INABackLeft, INBBackLeft, PWMBackLeft);
frontright.init(INAFrontRight, INBFrontRight, PWMFrontRight);
frontleft.init(INAFrontLeft, INBFrontLeft, PWMFrontLeft);
}
void motors::move(int direction, int speed, int correction){
    float motor_speeds[4] = {0}; //Sets each motor speed to 0
    for (int i = 0; i < 4; i++){ //Iterates through each motor speed
    motor_speeds[i] = speed * cos((M_PI/180)*(45 + 90 * i - direction)) + correction;} //Sets the current motor speed to 
    float AB_max = (max(abs(motor_speeds[0]), abs(motor_speeds[1])));
    float CD_max = (max(abs(motor_speeds[2]), abs(motor_speeds[3])));
    float max = (max(AB_max, CD_max)); //Finds the highest speed value
    if (max > 255){ //Checks if the highest speed value is higher than the limit
        float ratio = 255/max; //Finds the ratio of change
        for (int i = 0; i < 4; i++){ //Iterates through each motor value
            motor_speeds[i] *= ratio; //Scales each motor value down
        }}
    float AB_min = (min(abs(motor_speeds[0]), abs(motor_speeds[1])));
    float CD_min = (min(abs(motor_speeds[2]), abs(motor_speeds[3])));
    float min = (min(AB_min, CD_min)); //Finds the highest speed value
    if (min < 115){ //Checks if the highest speed value is higher than the limit
        float ratio = 115/min; //Finds the ratio of change
        for (int i = 0; i < 4; i++){ //Iterates through each motor value
            motor_speeds[i] *= ratio; //Scales each motor value down
        }}
    frontleft.movement(motor_speeds[0]);
    frontright.movement(motor_speeds[1]);
    backright.movement(motor_speeds[2]);
    backleft.movement(motor_speeds[3]);
}