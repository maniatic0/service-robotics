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
        TargetPick();
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void TargetPick() {
    MotorStop();

    RiseAttach();
    RiseMove(DOWN);
    delay(300);
    RiseDettach();

    GrabAttach();
    GrabMove(CLOSE);
    delay(1000);
    GrabMove(CLOSE_GRAB);

    RiseAttach();
    RiseMove(UP);
    while(!Stopper()){}
    RiseDettach();

    GrabMove(OPEN_GRAB);
    delay(2000);

    GrabMove(OPEN);
    delay(500);
    GrabDettach();

    MotorStart();
}
