#pragma once
#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Servo.h>


#define LEFT_FORWARD 20 
#define STOP 90 
#define LEFT_BACKWARD 160
#define RIGHT_FORWARD 160 
#define RIGHT_BACKWARD 20
#define LEFT_TURN 110 
#define RIGHT_TURN 110 
#define MOTORS 2
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1


extern Servo left_servo;  // create servo object to control a servo
extern Servo right_servo;  // create servo object to control a servo
extern int servoPin[];
extern float motor_signal[];

void MotorSetup();

void MotorStop();

void MotorStart();

#endif
