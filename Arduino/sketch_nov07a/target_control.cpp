#include "target_control.h"

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif    
    ReadSpeakers();
    NormalLineControl();
    if(distance[FRONT_SPEAKER] <= 30 + CLAWS)
    {
        if(line_signal[LEFT_MOTOR] != STOP) line_signal[LEFT_MOTOR] = int(float(STOP)-float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
        if(line_signal[RIGHT_MOTOR] != STOP) line_signal[RIGHT_MOTOR] = int(float(STOP)+float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
    }

    if(Clicker()){
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}