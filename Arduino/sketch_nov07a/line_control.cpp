#include "line_control.h"

void LineControl() {
    on_intersection = OnIntersection() || dir == TURN || dir == DELAY || dir == TARGET;
    
    //End of the intersection
    if (!on_intersection && !(entering_intersection && !exiting_intersection))
    {
        NormalLineControl();
        return;
    }

    //If we do not want to make the NormalLineControl and we are still on the Intersection. Just mark the entrance on the Intersection
    if (!entering_intersection)
    {
        left_servo.write(STOP);
        right_servo.write(STOP);
        entering_intersection = true;
        exiting_intersection = false;
        top_corner = false;
        white_corner = false;
        black_corner = false;
        second_white_corner = false;
#ifdef DEBUG
        Serial.println("Entering Intersection");
#endif
    }


    switch (dir) {
        case FORWARD:
          Forward();
          break;
        case LEFTS:
          LeftS();
          break;
        case RIGHTS:
          RightS();
          break;
        case LEFTS_CROSS:
          LeftSCross();
          break;
        case RIGHTS_CROSS:
          RightSCross();
          break;
        case TURN:
          Turn();
          break;
        case TARGET:
          Target();
          break;
        case DELAY:
          Delay();
          break;
        case FULL_STOP:
          MotorStop();
          updatePath();
          break;
        default:
          break;
    }
}