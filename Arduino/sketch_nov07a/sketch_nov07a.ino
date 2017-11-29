#include "Timer.h"

#include "configuration.h"
#include "lines.h"
#include "motors.h"
#include "leds.h"
#include "button.h"
#include "speakers.h"
#include "path.h"
#include "line_control.h"


void MotorControl(){
    ReadLineSensors();
    LineControl();

    motor_signal[LEFT_MOTOR] = line_signal[LEFT_MOTOR];
    motor_signal[RIGHT_MOTOR] = line_signal[RIGHT_MOTOR];

    left_servo.write(motor_signal[LEFT_MOTOR]);
    right_servo.write(motor_signal[RIGHT_MOTOR]);
}

void setup() {
    MotorSetup();
    LineSetup();
    SpeakerSetup();
    ButtonClickerSetup();
#ifdef DEBUG
    Serial.begin(9600);              //  setup serial
#endif
    PathSetup();
    //LEDsSetup();
}

void loop() {
    if(!Button()) {
      return;  
    }
    timer.update();
    MotorControl();
    //UpdateLEDs();
#ifdef DEBUG
  /*
    Serial.print("Left motor:");
    Serial.print(motor_signal[LEFT_MOTOR]);
    Serial.print(" Right motor:");
    Serial.println(motor_signal[RIGHT_MOTOR]);
    
    Serial.print("Line Sensors: ");
    Serial.print(OnLine(LEFT_LEFT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(LEFT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(RIGHT_LINE_SENSOR));
    Serial.print(" ");
    Serial.print(OnLine(RIGHT_RIGHT_LINE_SENSOR));
    Serial.println(" "); 
    */
    Serial.print("Speaker: ");
    Serial.print(distance[FRONT_SPEAKER]);
    Serial.println(" cm"); 
#endif
}
