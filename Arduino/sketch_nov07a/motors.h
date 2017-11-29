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

#define OPEN 135
#define OPEN_GRAB 95
#define CLOSE 45
#define CLOSE_GRAB 70
#define DOWN 135
#define UP 40

#define MOTORS 4
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define RISE_MOTOR 2
#define GRAB_MOTOR 3


extern Servo left_servo;  // create servo object to control a servo
extern Servo right_servo;  // create servo object to control a servo
extern Servo rise_servo;  // create servo object to control a servo
extern Servo grab_servo;  // create servo object to control a servo
extern int servoPin[];
extern float motor_signal[];

void MotorSetup();

void MotorStop();

void MotorStart();

void RiseAttach();

void RiseDettach();

void RiseMove(int);

void GrabAttach();

void GrabDettach();

void GrabMove(int);

#endif
