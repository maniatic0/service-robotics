#include "path_control.h"

Timer timer;

void NormalLineControl() {
#ifdef DEBUG
        Serial.println("Normal Line");
#endif
    if (OnLine(LEFT_LINE_SENSOR))
    {
        line_signal[LEFT_MOTOR] = STOP;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    }

    if (OnLine(RIGHT_LINE_SENSOR))
    {
        line_signal[RIGHT_MOTOR] = STOP;
    }
    else
    {
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
}

void Forward() {
#ifdef DEBUG
        Serial.println("Forward");
#endif
    line_signal[LEFT_MOTOR] = LEFT_FORWARD;
    line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;

    //After an intersection mark as a normal path again
    if (!on_intersection && entering_intersection && !exiting_intersection)
    {
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void LeftS() {
#ifdef DEBUG
        Serial.println("LeftS");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(LEFT_LEFT_LINE_SENSOR) && !white_corner) white_corner = true;
      
      line_signal[LEFT_MOTOR] = LEFT_BACKWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }

    //After an intersection mark as a normal path again
    if (OnLine(RIGHT_LINE_SENSOR) && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void RightS() {
#ifdef DEBUG
        Serial.println("RightS");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(RIGHT_RIGHT_LINE_SENSOR) && !white_corner) white_corner = true;
      
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_BACKWARD;
    }

    //After an intersection mark as a normal path again
    if (OnLine(LEFT_LINE_SENSOR) && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

void LeftSCross() {
#ifdef DEBUG
        Serial.println("LeftSCross");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(LEFT_LEFT_LINE_SENSOR) && !white_corner) white_corner = true;
      line_signal[LEFT_MOTOR] = LEFT_BACKWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(RIGHT_RIGHT_LINE_SENSOR) && white_corner && !black_corner) black_corner = true;
    else if(!OnLine(RIGHT_RIGHT_LINE_SENSOR) && white_corner && black_corner && !second_white_corner) second_white_corner = true;
    else if (OnLine(RIGHT_LINE_SENSOR) && white_corner && black_corner && second_white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}


void RightSCross() {
#ifdef DEBUG
        Serial.println("RightSCross");
#endif

    if((OnLine(RIGHT_RIGHT_LINE_SENSOR) || OnLine(LEFT_LEFT_LINE_SENSOR)) && !white_corner) {
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
    }
    else {
      if(!OnLine(RIGHT_RIGHT_LINE_SENSOR) && !white_corner) white_corner = true;
      line_signal[LEFT_MOTOR] = LEFT_FORWARD;
      line_signal[RIGHT_MOTOR] = RIGHT_BACKWARD;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(LEFT_LEFT_LINE_SENSOR) && white_corner && !black_corner) black_corner = true;
    else if(!OnLine(LEFT_LEFT_LINE_SENSOR) && white_corner && black_corner && !second_white_corner) second_white_corner = true;
    else if (OnLine(LEFT_LINE_SENSOR) && white_corner && black_corner && second_white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
}

//we want to turn 180 degrees for our left
void Turn() {
#ifdef DEBUG
        Serial.println("Turn");
#endif    
    /*Top corner is used just to say if it is the first time we are entering in the function.Just to be sure if the right line sensor
    is or not over the line*/
    if(!top_corner) {
      line_signal[LEFT_MOTOR] = STOP;
      line_signal[RIGHT_MOTOR] = STOP;
      top_corner = true;
    }
    else
    {
        line_signal[LEFT_MOTOR] = LEFT_TURN;
        line_signal[RIGHT_MOTOR] = RIGHT_TURN;
    }
    
    //After an intersection mark as a normal path again
    if(OnLine(RIGHT_LINE_SENSOR) && top_corner && !black_corner) black_corner = true;
    else if(!OnLine(RIGHT_LINE_SENSOR) && top_corner && black_corner && !white_corner) white_corner = true;
    else if (OnLine(LEFT_LINE_SENSOR) && top_corner && black_corner && white_corner && entering_intersection && !exiting_intersection)
    {
        line_signal[LEFT_MOTOR] = LEFT_FORWARD;
        line_signal[RIGHT_MOTOR] = RIGHT_FORWARD;
        white_corner = false;
        black_corner = false;
        top_corner = false;
        second_white_corner = false;
        exiting_intersection = true;
        entering_intersection = false;
        updatePath();
    }
} 

void DelayAfter() {
    updatePath();
    exiting_intersection = true;
    entering_intersection = false;
    top_corner = false;
}

void Delay() {
#ifdef DEBUG
        Serial.println("Delay");
#endif    

    NormalLineControl();
    if(!top_corner) {
        timer.after(TIMER_DELAY, DelayAfter);
    }
}
