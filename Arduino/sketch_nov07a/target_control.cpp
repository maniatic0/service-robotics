#include "target_control.h"

int target_count = 1;

void WaitToLower() {
  top_corner = true;
}

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif
    if (!white_corner) {
      timer.after(100, WaitToLower);
      white_corner = true;
    }
    if(white_corner && top_corner && distance[FRONT_SPEAKER] <= int(CLOSE_DISTANCE) + CLAWS) {
      RiseAttach();
      RiseMove(DOWN);
      delay(200);
      RiseDettach();
      GrabAttach();
      GrabMove(OPEN);
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
        TargetPick();
        top_corner = false;
        white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void TargetPick() {
    MotorStop();
    
    GrabMove(CLOSE);
    delay(500);
    GrabMove(CLOSE_GRAB);
#ifdef DEBUG
  Serial.println("Claw Closed");
#endif  

    RiseAttach();
    RiseMove(UP);
    delay(1500);
#ifdef DEBUG
  Serial.println("Claw Up");
#endif 

    delay(400);
    
    RiseDettach();
    target_count++;

    GrabMove(OPEN);
    delay(400);
    GrabDettach();
#ifdef DEBUG
  Serial.println("Claw Open");
#endif 

    MotorStart();
}
