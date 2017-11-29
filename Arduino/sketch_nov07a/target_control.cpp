#include "target_control.h"

void Target() {
#ifdef DEBUG
        Serial.println("Target");
#endif
    if(!top_corner) {
      top_corner = true;
      RiseAttach();
      RiseMove(DOWN);
      delay(260);
      RiseDettach();
#ifdef DEBUG
  Serial.println("Claw Down");
#endif 
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
    delay(1000);
    GrabMove(CLOSE_GRAB);
#ifdef DEBUG
  Serial.println("Claw Closed");
#endif  

    RiseAttach();
    RiseMove(UP);
    delay(1800);
    RiseDettach();
#ifdef DEBUG
  Serial.println("Claw Up");
#endif 

    for(int i = 0; i < 100; i++) {
      GrabMove(95);
      delay(10);
      GrabMove(85);
      delay(10);
    }
    delay(2000);

    GrabMove(OPEN);
    delay(800);
    GrabDettach();
#ifdef DEBUG
  Serial.println("Claw Open");
#endif 

    MotorStart();
}
