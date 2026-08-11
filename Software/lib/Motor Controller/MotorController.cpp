#include <MotorController.h>
void MotorController::init(int ina , int inb , int pwm){
    INA = ina ; INB = inb ; PWM = pwm; //INA and INB determine which way the wheel spins and PWM determines the speed (0-255)
    pinMode(INA, OUTPUT); //Sets INA to output
    pinMode(INB, OUTPUT); //Sets INB to output
    pinMode(PWM, OUTPUT);} //Sets PWM to output
void MotorController::movement(int speed){
    if (speed < 0){ //Checks if the speed is below 0
        digitalWrite(INA, LOW); //If so, sets INA to low
        digitalWrite(INB, HIGH); //If so, sets INB to high
        analogWrite(PWM, abs(speed));} //If so, sets PWM to whatever the speed is
    if (speed > 0){ //Checks if the speed is above 0
        digitalWrite(INA, HIGH); //If so, sets INA to high
        digitalWrite(INB, LOW); //If so, sets INB to low
        analogWrite(PWM, speed);} //If so, sets PWM to whatever the speed is
    if (speed == 0){ //Checks if the speed is 0
        digitalWrite(INA, HIGH); //If so, sets INA to high
        digitalWrite(INB, HIGH); //If so, sets INB to high
        analogWrite(PWM, 0);} //If so, sets PWM to 0
}