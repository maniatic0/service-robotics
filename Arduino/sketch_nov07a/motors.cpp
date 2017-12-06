#include "motors.h"

Servo left_servo;  // create servo object to control a servo
Servo right_servo;  // create servo object to control a servo
Servo rise_servo;  // create servo object to control a servo
Servo grab_servo;  // create servo object to control a servo
int servoPin[] = {7, 8, 9, 10};
float motor_signal[MOTORS] = {0,0,0,0};

void MotorSetup() { 
	MotorStop();
  RiseAttach();
  RiseMove(UP);
  delay(350);
  RiseDettach();
#ifdef DEBUG
  Serial.println("Claw up");
#endif  
  GrabAttach();
  GrabMove(OPEN);
  delay(1000);
  GrabDettach();
#ifdef DEBUG
  Serial.println("Claw Open");
#endif  
}

void MotorStop() {
	left_servo.detach();
	right_servo.detach();
}

void MotorStart() {
  left_servo.attach(servoPin[LEFT_MOTOR]);
  right_servo.attach(servoPin[RIGHT_MOTOR]);
}

void RiseAttach() {
	rise_servo.attach(servoPin[RISE_MOTOR]);
}

void RiseDettach() {
	rise_servo.detach();
}

void RiseMove(int speed) {
	rise_servo.write(speed);
}

void GrabAttach() {
	grab_servo.attach(servoPin[GRAB_MOTOR]);
}

void GrabDettach() {
	grab_servo.detach();
}

void GrabMove(int speed) {
	grab_servo.write(speed);
}
