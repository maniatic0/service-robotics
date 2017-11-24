#include "target_control.h"

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif
    if(!top_corner) {
      top_corner = true;
      RiseAttach();
      RiseMove(DOWN);
      delay(220);
      RiseDettach();
      Serial.println("Claw down");
    }    
    ReadSpeakers();
    NormalLineControl();
    if(distance[FRONT_SPEAKER] <= 30 + CLAWS)
    {
        if(line_signal[LEFT_MOTOR] != STOP) line_signal[LEFT_MOTOR] = int(float(STOP)-float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
        if(line_signal[RIGHT_MOTOR] != STOP) line_signal[RIGHT_MOTOR] = int(float(STOP)+float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/30.0);
    }

    if(distance[FRONT_SPEAKER] <= CLAWS){
        TargetPick();
        top_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void TargetPick() {
    MotorStop();

    GrabAttach();
    GrabMove(CLOSE);
    delay(2000);
    GrabMove(CLOSE_GRAB);
    Serial.println("Claw closed");

    RiseAttach();
    RiseMove(UP);
    delay(1500);
    RiseDettach();
    Serial.println("Claw up");

    GrabMove(OPEN_GRAB);
    delay(5000);

    GrabMove(OPEN);
    delay(600);
    GrabDettach();
    Serial.println("Claw open");

    MotorStart();
}
