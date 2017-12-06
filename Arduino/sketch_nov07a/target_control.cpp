#include "target_control.h"

int target_count = 1;

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif
    if(!top_corner) {
      top_corner = true;
      RiseAttach();
      RiseMove(DOWN);
      delay(300);
      RiseDettach();
#ifdef DEBUG
  Serial.println("Claw Down");
#endif 
    }    
    ReadSpeakers();
    NormalLineControl();
    if(distance[FRONT_SPEAKER] <= int(CLOSE_DISTANCE) + CLAWS)
    {
        if(line_signal[LEFT_MOTOR] != STOP) line_signal[LEFT_MOTOR] = int(float(STOP)-float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/CLOSE_DISTANCE);
        if(line_signal[RIGHT_MOTOR] != STOP) line_signal[RIGHT_MOTOR] = int(float(STOP)+float(STOP-LEFT_FORWARD)*float(distance[FRONT_SPEAKER]-CLAWS)/CLOSE_DISTANCE);
    }

    if(distance[FRONT_SPEAKER] <= CLAWS){
        GrabAttach();
        GrabMove(OPEN);
        TargetPick();
        top_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void TargetPick() {
    MotorStop();
    
    GrabMove(CLOSE);
    delay(1000);
    GrabMove(CLOSE_GRAB);
#ifdef DEBUG
  Serial.println("Claw Closed");
#endif  

    RiseAttach();
    RiseMove(UP);
    delay(1800);
#ifdef DEBUG
  Serial.println("Claw Up");
#endif 

    delay(800);
    
    RiseDettach();
    target_count++;

    GrabMove(OPEN);
    delay(1000);
    GrabDettach();
#ifdef DEBUG
  Serial.println("Claw Open");
#endif 

    MotorStart();
}
