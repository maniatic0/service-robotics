#include "motors.h"

Servo left_servo;  // create servo object to control a servo
Servo right_servo;  // create servo object to control a servo
int servoPin[] = {9, 10};
float motor_signal[MOTORS] = {0,0};

void MotorSetup() {
	MotorStop();
}

void MotorStop() {
	left_servo.detach();
	right_servo.detach();
}

void MotorStart() {
  left_servo.attach(servoPin[LEFT_MOTOR]);
  right_servo.attach(servoPin[RIGHT_MOTOR]);
}

